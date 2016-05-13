#ifndef SOLAIRE_SERIAL_SERIALISER_HPP
#define SOLAIRE_SERIAL_SERIALISER_HPP

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
	template<class T, typename ENABLE = void>
	struct serialiser {
		typedef T input_t;
		typedef T output_t;

		static value serialise(input_t);
		static output_t deserialise(const value&);
	};

	template<class T>
	inline value serialise(typename serialiser<T>::input_t aValue) {
		return serialiser<T>::serialise(aValue);
	}

	template<class T>
	inline typename serialiser<T>::output_t deserialise(const value& aValue) {
		return serialiser<T>::deserialise(aValue);
	}
}}

#endif