//Copyright 2016 Adam G. Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http ://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#include <string>
#include "solaire/serial/json.hpp"


extern "C" SOLAIRE_EXPORT_API bool SOLAIRE_EXPORT_CALL solaire_read_json(solaire::serial::value*, solaire::interfaces::istream*) {
	//! \todo Implement ini read
	return false;
}

extern "C" SOLAIRE_EXPORT_API bool SOLAIRE_EXPORT_CALL solaire_write_json(const solaire::serial::value* aValue, solaire::interfaces::ostream* aStream) {
	using namespace solaire;
	try{
		const serial::value& value = *aValue;
		interfaces::ostream& stream = *aStream;

		switch(value.get_type())
		{
		case serial::VOID_T:
			stream << "null";
			break;
		case serial::CHAR_T:
			stream << '"' << value.get_char() << '"';
			break;
		case serial::BOOL_T:
			stream << (value.get_bool() ? "true" : "false");
			break;
		case serial::UNSIGNED_T:
			stream << std::to_string(value.get_unsigned()).c_str();
			break;
		case serial::SIGNED_T:
			stream << std::to_string(value.get_signed()).c_str();
			break;
		case serial::FLOAT_T:
			stream << std::to_string(value.get_float()).c_str();
			break;
		case serial::POINTER_T:
			stream << std::to_string(reinterpret_cast<uint64_t>(value.get_pointer())).c_str();
			break;
		case serial::STRING_T:
			stream << '"' << value.get_string() << '"';
			break;
		case serial::ARRAY_T:
			stream << '[';
			{
				const auto& list = value.get_array();
				const uint32_t size = list.size();
				for(uint32_t i = 0; i < size; ++i) {
					solaire_write_json(&list[i], aStream);
					if(i + 1 < size) stream << ',';
				}
			}
			stream << ']';
			break;
		case serial::OBJECT_T:
			stream << '{';
			{
				const auto& object = value.get_object();
				const uint32_t size = object.size();
				auto j = object.begin();
				for(uint32_t i = 0; i < size; ++i, ++j) {
					stream << '"' << j->first << '"' << ':';
					solaire_write_json(&j->second, aStream);
					if (i + 1 < size) stream << ',';
				}
			}
			stream << '}';
			break;
		default:
			return false;
		}
	} catch(...) {
		return false;
	}
	return true;
}