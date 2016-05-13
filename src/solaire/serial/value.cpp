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

#include "solaire/core/interfaces/allocator.hpp"
#include "solaire/serial/value.hpp"

namespace solaire { namespace serial {
	// value
	value::value() :
		mPointer(nullptr),
		mType(VOID_T)
	{}

	value::value(value&& aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		operator=(std::move(aValue));
	}

	value::value(const value& aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		operator=(aValue);
	}

	value::value(char aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_char(aValue);
	}

	value::value(bool aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_char(aValue);
	}

	value::value(uint8_t aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_unsigned(aValue);
	}

	value::value(uint16_t aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_unsigned(aValue);
	}

	value::value(uint32_t aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_unsigned(aValue);
	}

	value::value(uint64_t aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_unsigned(aValue);
	}

	value::value(int8_t aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_signed(aValue);
	}

	value::value(int16_t aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_signed(aValue);
	}

	value::value(int32_t aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_signed(aValue);
	}

	value::value(int64_t aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_signed(aValue);
	}

	value::value(float aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_float(aValue);
	}

	value::value(double aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_float(aValue);
	}

	value::value(const std::string& aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_string(aValue);
	}

	value::value(const std::vector<value>& aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_array(aValue);
	}

	value::value(const std::map<std::string, value>& aValue) :
		mPointer(nullptr),
		mType(VOID_T)
	{
		set_object(aValue);
	}

	value::~value() {
		set_void();
	}

	value& value::operator=(value&& aOther) {
		set_void();
		switch(aOther.mType)
		{
		case CHAR_T:
			mChar = aOther.mChar;
			break;
		case BOOL_T:
			mBool = aOther.mBool;
			break;
		case UNSIGNED_T:
			mUnsigned = aOther.mUnsigned;
			break;
		case SIGNED_T:
			mSigned = aOther.mSigned;
			break;
		case FLOAT_T:
			mFloat = aOther.mFloat;
			break;
		case POINTER_T:
		case STRING_T:
		case ARRAY_T:
		case OBJECT_T:
			mPointer = aOther.mPointer;
			break;
		default:
			break;
		}
		mType = aOther.mType;
		aOther.mPointer = nullptr;
		aOther.mType = VOID_T;
		return *this;
	}

	value& value::operator=(const value& aOther) {
		switch (aOther.mType)
		{
		case CHAR_T:
			set_char(aOther.mChar);
			break;
		case BOOL_T:
			set_bool(aOther.mBool);
			break;
		case UNSIGNED_T:
			set_unsigned(aOther.mUnsigned);
			break;
		case SIGNED_T:
			set_signed(aOther.mSigned);
			break;
		case FLOAT_T:
			set_float(aOther.mFloat);
			break;
		case POINTER_T:
			set_pointer(aOther.mPointer);
			break;
		case STRING_T:
			set_string(*static_cast<const std::string*>(aOther.mPointer));
			break;
		case ARRAY_T:
			set_array(*static_cast<const std::vector<value>*>(aOther.mPointer));
			break;
		case OBJECT_T:
			set_object(*static_cast<const std::map<std::string, value>*>(aOther.mPointer));
			break;
		default:
			break;
		}
		return *this;
	}

	serial_type value::get_type() const throw() {
		return mType;
	}

	bool value::is_void() const throw() {
		return mType == VOID_T;
	}

	bool value::is_char() const throw() {
		return mType == CHAR_T || (mType == STRING_T && static_cast<const std::string*>(mPointer)->size() == 1);
	}

	bool value::is_bool() const throw() {
		return false; //! \todo implement
	}

	bool value::is_unsigned() const throw() {
		return false; //! \todo implement
	}

	bool value::is_signed() const throw() {
		return false; //! \todo implement
	}

	bool value::is_float() const throw() {
		return false; //! \todo implement
	}

	bool value::is_pointer() const throw() {
		return false; //! \todo implement
	}

	bool value::is_string() const throw() {
		return false; //! \todo implement
	}

	bool value::is_array() const throw() {
		return false; //! \todo implement
	}

	bool value::is_object() const throw() {
		return false; //! \todo implement
	}

	char value::get_char() const {
		switch(mType)
		{
		case CHAR_T:
			return mChar;
		case STRING_T:
			{
				const std::string& ref = *static_cast<const std::string*>(mPointer);
				if(ref.size() == 1) return ref[0];
			}
			break;
		}
		throw std::runtime_error("solaire::serial::value::get_char : Value is not convertable to char");
	}

	bool value::get_bool() const {
		switch(mType)
		{
		case CHAR_T:
			switch(mChar)
			{
			case '0':
			case 'n':
			case 'N':
				return false;
			case '1':
			case 'y':
			case 'Y':
				return true;
			}
		case UNSIGNED_T:
			return mUnsigned >= 1;
		case SIGNED_T:
			return mSigned >= 1;
		case FLOAT_T:
			return mFloat >= 1.f;
		case POINTER_T:
			return mPointer != nullptr;
		case STRING_T:
			{
				{
					const std::string& ref = *static_cast<const std::string*>(mPointer);
					if(ref == "0") return false;
					else if (ref == "n") return false;
					else if (ref == "N") return false;
					else if (ref == "no") return false;
					else if (ref == "NO") return false;
					else if (ref == "No") return false;
					else if (ref == "false") return false;
					else if (ref == "FALSE") return false;
					else if (ref == "False") return false;
					else if (ref == "1") return true;
					else if (ref == "y") return true;
					else if (ref == "Y") return true;
					else if (ref == "yes") return true;
					else if (ref == "YES") return true;
					else if (ref == "Yes") return true;
					else if (ref == "true") return true;
					else if (ref == "TRUE") return true;
					else if (ref == "True") return true;
				}
			}
			break;
		}
		throw std::runtime_error("solaire::serial::value::get_bool : Value is not convertable to bool"); //! \todo implement
	}

	uint64_t value::get_unsigned() const {
		throw std::runtime_error("solaire::serial::value::get_unsigned : Value is not convertable to unsigned"); //! \todo implement
	}

	int64_t value::get_signed() const {
		throw std::runtime_error("solaire::serial::value::get_signed : Value is not convertable to signed"); //! \todo implement
	}

	double value::get_float() const {
		throw std::runtime_error("solaire::serial::value::get_float : Value is not convertable to float"); //! \todo implement
	}

	void* value::get_pointer() const {
		throw std::runtime_error("solaire::serial::value::get_pointer : Value is not convertable to pointer"); //! \todo implement
	}

	std::string value::get_string() const {
		throw std::runtime_error("solaire::serial::value::get_string : Value is not convertable to string"); //! \todo implement
	}

	std::vector<value> value::get_array() const {
		throw std::runtime_error("solaire::serial::value::get_array : Value is not convertable to array"); //! \todo implement
	}

	std::map<std::string, value> value::get_object() const {
		throw std::runtime_error("solaire::serial::value::get_object : Value is not convertable to object"); //! \todo implement
	}

	char& value::get_char() {
		if(mType != CHAR_T) operator=(std::move(value(const_cast<const value*>(this)->get_char())));
		return mChar;
	}

	bool& value::get_bool() {
		if (mType != BOOL_T) operator=(std::move(value(const_cast<const value*>(this)->get_bool())));
		return mBool;
	}

	uint64_t& value::get_unsigned() {
		if (mType != UNSIGNED_T) operator=(std::move(value(const_cast<const value*>(this)->get_unsigned())));
		return mUnsigned;
	}

	int64_t& value::get_signed() {
		if (mType != SIGNED_T) operator=(std::move(value(const_cast<const value*>(this)->get_signed())));
		return mSigned;
	}

	double& value::get_float() {
		if (mType != FLOAT_T) operator=(std::move(value(const_cast<const value*>(this)->get_float())));
		return mFloat;
	}

	void*& value::get_pointer() {
		if (mType != POINTER_T) operator=(std::move(value(const_cast<const value*>(this)->get_pointer())));
		return mPointer;
	}

	std::string& value::get_string() {
		if (mType != STRING_T) operator=(std::move(value(const_cast<const value*>(this)->get_string())));
		return *static_cast<std::string*>(mPointer);
	}

	std::vector<value>& value::get_array() {
		if (mType != ARRAY_T) operator=(std::move(value(const_cast<const value*>(this)->get_array())));
		return *static_cast<std::vector<value>*>(mPointer);
	}

	std::map<std::string, value>& value::get_object() {
		if (mType != OBJECT_T) operator=(std::move(value(const_cast<const value*>(this)->get_object())));
		return *static_cast<std::map<std::string, value>*>(mPointer);
	}

	void value::set_void() {
		switch(mType)
		{
		case STRING_T:
			{
				std::string* const tmp = static_cast<std::string*>(mPointer);
				tmp->~basic_string();
				get_allocator().deallocate(tmp);
			}
			break;
		case ARRAY_T:
			{
				std::vector<value>* const tmp = static_cast<std::vector<value>*>(mPointer);
				tmp->~vector();
				get_allocator().deallocate(tmp);
			}
			break;
		case OBJECT_T:
			{
				std::map<std::string, value>* const tmp = static_cast<std::map<std::string, value>*>(mPointer);
				tmp->~map();
				get_allocator().deallocate(tmp);
			}
			break;
		default:
			mPointer = nullptr;
			break;
		}
		mType = VOID_T;
	}

	void value::set_char(char aValue) {
		set_void();
		mChar = aValue;
		mType = CHAR_T;
	}

	void value::set_bool(bool aValue) {
		set_void();
		mBool = aValue;
		mType = BOOL_T;
	}

	void value::set_unsigned(uint64_t aValue) {
		set_void();
		mUnsigned = aValue;
		mType = UNSIGNED_T;
	}

	void value::set_signed(int64_t aValue) {
		set_void();
		mSigned = aValue;
		mType = SIGNED_T;
	}

	void value::set_float(double aValue) {
		set_void();
		mFloat = aValue;
		mType = FLOAT_T;
	}

	void value::set_pointer(void* aValue) {
		set_void();
		mPointer = aValue;
		mType = POINTER_T;
	}

	void value::set_string(const std::string& aValue) {
		if(mType == STRING_T) {
			*static_cast<std::string*>(mPointer) = aValue;
		}else {
			set_void();
			mPointer = new(get_allocator().allocate(sizeof(std::string))) std::string(aValue);
			mType = STRING_T;
		}
	}

	void value::set_array(const std::vector<value>& aValue) {
		if(mType == ARRAY_T) {
			*static_cast<std::vector<value>*>(mPointer) = aValue;
		}else {
			set_void();
			mPointer = new(get_allocator().allocate(sizeof(std::vector<value>))) std::vector<value>(aValue);
			mType = ARRAY_T;
		}
	}

	void value::set_object(const std::map<std::string, value>& aValue) {
		if(mType == OBJECT_T) {
			*static_cast<std::map<std::string, value>*>(mPointer) = aValue;
		}else {
			set_void();
			mPointer = new(get_allocator().allocate(sizeof(std::map<std::string, value>))) std::map<std::string, value>(aValue);
			mType = OBJECT_T;
		}
	}

}}