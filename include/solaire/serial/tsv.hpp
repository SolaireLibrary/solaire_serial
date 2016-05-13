#ifndef SOLAIRE_SERIAL_TSV_HPP
#define SOLAIRE_SERIAL_TSV_HPP

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

#include "solaire/serial/delimited.hpp"

namespace solaire { namespace serial {
	inline value read_tsv(interfaces::istream& aStream) {
		return read_delimited(aStream, '\t');
	}

	inline void write_tsv(const value& aValue, interfaces::ostream& aStream) {
		return write_delimited(aValue, aStream, '\t');
	}
}}

#endif