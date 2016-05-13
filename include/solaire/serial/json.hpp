#ifndef SOLAIRE_SERIAL_JSON_HPP
#define SOLAIRE_SERIAL_JSON_HPP

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

#include "solaire/core/interfaces/istream.hpp"
#include "solaire/core/interfaces/ostream.hpp"
#include "solaire/serial/value.hpp"

extern "C" SOLAIRE_EXPORT_API bool SOLAIRE_EXPORT_CALL solaire_read_json(solaire::serial::value*, solaire::interfaces::istream*);
extern "C" SOLAIRE_EXPORT_API bool SOLAIRE_EXPORT_CALL solaire_write_json(const solaire::serial::value*, solaire::interfaces::ostream*);

namespace solaire { namespace serial {
	value read_json(interfaces::istream& aStream) {
		value tmp;
		runtime_assert(solaire_read_json(&tmp, &aStream), "solaire::serial::read_json : Failed to read json");
		return tmp;
	}

	void write_json(const value& aValue, interfaces::ostream& aStream) {
		runtime_assert(solaire_write_json(&aValue, &aStream), "solaire::serial::write_json : Failed to write json");
	}
}}

#endif