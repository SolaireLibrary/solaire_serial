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
#include "solaire/serial/delimited.hpp"


extern "C" SOLAIRE_EXPORT_API bool SOLAIRE_EXPORT_CALL solaire_read_delimited(solaire::serial::value*, solaire::interfaces::istream*, char aDelimiter) {
	//! \todo Implement ini read
	return false;
}

extern "C" SOLAIRE_EXPORT_API bool SOLAIRE_EXPORT_CALL solaire_write_delimited(const solaire::serial::value* aValue, solaire::interfaces::ostream* aStream, char aDelimiter) {
	using namespace solaire;
	try {
		const serial::value& value = *aValue;
		interfaces::ostream& stream = *aStream;

		if (value.get_type() != serial::ARRAY_T) return false;
		const auto& list = value.get_array();
		const auto size = list.size();

		for(uint32_t i = 0; i < size; ++i) {
			const serial::value& vi = list[i];
			//! \todo Handle delimited arrays and objects
			switch(vi.get_type())
			{
			case serial::VOID_T:
				stream << "null";
				break;
			case serial::CHAR_T:
				stream << '"' << vi.get_char() << '"';
				break;
			case serial::BOOL_T:
				stream << (vi.get_bool() ? "true" : "false");
				break;
			case serial::UNSIGNED_T:
				stream << std::to_string(vi.get_unsigned()).c_str();
				break;
			case serial::SIGNED_T:
				stream << std::to_string(vi.get_signed()).c_str();
				break;
			case serial::FLOAT_T:
				stream << std::to_string(vi.get_float()).c_str();
				break;
			case serial::POINTER_T:
				stream << std::to_string(reinterpret_cast<uint64_t>(vi.get_pointer())).c_str();
				break;
			case serial::STRING_T:
				stream << '"' << vi.get_string() << '"';
				break;
			default:
				return false;
			}
			if(i + 1 < size) stream << aDelimiter;
		}

	}catch (...) {
		return false;
	}
	return true;
}
