#ifndef SOLAIRE_SERIAL_DELIMITED_HPP
#define SOLAIRE_SERIAL_DELIMITED_HPP

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

extern "C" SOLAIRE_EXPORT_API bool SOLAIRE_EXPORT_CALL solaire_read_delimited(solaire::serial::value*, solaire::interfaces::istream*, char);
extern "C" SOLAIRE_EXPORT_API bool SOLAIRE_EXPORT_CALL solaire_write_delimited(const solaire::serial::value*, solaire::interfaces::ostream*, char);

namespace solaire { namespace serial {
	value read_delimited(interfaces::istream& aStream, char aDelimiter) {
		value tmp;
		runtime_assert(solaire_read_delimited(&tmp, &aStream, aDelimiter), "solaire::serial::read_delimited : Failed to read delimited");
		return tmp;
	}

	void write_delimited(const value& aValue, interfaces::ostream& aStream, char aDelimiter) {
		runtime_assert(solaire_write_delimited(&aValue, &aStream, aDelimiter),"solaire::serial::write_delimited : Failed to write delimited");
	}
}}

#endif