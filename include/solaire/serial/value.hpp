#ifndef SOLAIRE_SERIAL_VALUE_HPP
#define SOLAIRE_SERIAL_VALUE_HPP

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

#include <map>
#include "solaire/serial/serial.hpp"
#include "solaire/core/containers/array_list.hpp"

//! \todo Use exportable classes instead of STL

namespace solaire { namespace serial {
	enum serial_type : uint8_t {
		VOID_T,
		CHAR_T,
		BOOL_T,
		UNSIGNED_T,
		SIGNED_T,
		FLOAT_T,
		POINTER_T,
		STRING_T,
		ARRAY_T,
		OBJECT_T
	};

	class value {
	protected:
		union {
			char mChar;
			bool mBool;
			uint64_t mUnsigned;
			int64_t mSigned;
			double mFloat;
			void* mPointer;
		};
		serial_type mType;
	public:
		value();
		value(value&&);
		value(const value&);
		value(char);
		value(bool);
		value(uint8_t);
		value(uint16_t);
		value(uint32_t);
		value(uint64_t);
		value(int8_t);
		value(int16_t);
		value(int32_t);
		value(int64_t);
		value(float);
		value(double);
		value(const std::string&);
		value(const container<value>&);
		value(const std::map<std::string, value>&);
		~value();

		value& operator=(value&&);
		value& operator=(const value&);

		serial_type get_type() const throw();

		bool is_void() const throw();
		bool is_char() const throw();
		bool is_bool() const throw();
		bool is_unsigned() const throw();
		bool is_signed() const throw();
		bool is_float() const throw();
		bool is_pointer() const throw();
		bool is_string() const throw();
		bool is_array() const throw();
		bool is_object() const throw();

		char get_char() const;
		bool get_bool() const;
		uint64_t get_unsigned() const;
		int64_t get_signed() const;
		double get_float() const;
		void* get_pointer() const;
		std::string get_string() const;
		array_list<value> get_array() const;
		std::map<std::string, value> get_object() const;

		char& get_char();
		bool& get_bool();
		uint64_t& get_unsigned();
		int64_t& get_signed();
		double& get_float();
		void*& get_pointer();
		std::string& get_string();
		stack<value>& get_array();
		std::map<std::string, value>& get_object();

		void set_void();
		void set_char(char);
		void set_bool(bool);
		void set_unsigned(uint64_t);
		void set_signed(int64_t);
		void set_float(double);
		void set_pointer(void*);
		void set_string(const std::string&);
		void set_array(const container<value>&);
		void set_object(const std::map<std::string, value>&);
	};
}}

#endif