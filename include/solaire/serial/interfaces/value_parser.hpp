#ifndef SOLAIRE_SERIAL_VALUE_PARSER_HPP
#define SOLAIRE_SERIAL_VALUE_PARSER_HPP

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

#include "solaire/serial/value.hpp"

//! \todo Use exportable classes instead of STL

namespace solaire { namespace serial {
	SOLAIRE_EXPORT_INTERFACE value_parser {
		virtual SOLAIRE_INTERFACE_CALL ~value_parser(){}

		virtual bool SOLAIRE_INTERFACE_CALL begin_object() throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL end_object() throw() = 0;

		virtual bool SOLAIRE_INTERFACE_CALL begin_array() throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL end_array() throw() = 0;

		virtual bool SOLAIRE_INTERFACE_CALL set_key(const char*) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL set_index(uint32_t) throw() = 0;

		virtual bool SOLAIRE_INTERFACE_CALL set_void_value() throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL set_char_value(char) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL set_bool_value(bool) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL set_unsigned_value(uint64_t) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL set_signed_value(int64_t) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL set_float_value(double) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL set_pointer_value(void*) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL set_set_string_value(const std::string&) throw() = 0;
	};
}}

#endif