#include "MyString.h"

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <exception>

MyString::MyString(const char* rawString) {
	if (rawString != nullptr) {
		_size = std::strlen(rawString);
		_data = new char[_size];
		for (size_t i = 0; i < this->_size; ++i) {
			this->_data[i] = rawString[i];
		}
	}
}

MyString::MyString(const MyString& other)
	: _size(other._size), _data(new char[_size]) 
{
	for (size_t i = 0; i < this->_size; ++i) {
		this->_data[i] = other._data[i];
	}
}

MyString::MyString(MyString&& other) noexcept 
	: _size(other._size), _data(other._data) 
{
	other._data = nullptr;
	other._size = 0;
}

MyString& MyString::operator=(const MyString& other) 
{
	this->_size = other._size;

	if (this->_data != nullptr) {
		delete[] this->_data;
	}

	this->_data = new char[_size];
	for (size_t i = 0; i < this->_size; ++i) {
		this->_data[i] = other._data[i];
	}
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept 
{
	if (this != &other) {
		this->_size = other._size;
		if (this->_data != nullptr) {
			delete[] this->_data;
		}
		this->_data = other._data;
		other._data = nullptr;
		other._size = 0;
	}
	return *this;
}

MyString::~MyString() {
	delete[] _data;
}

void MyString::append(const MyString& appendedString) {
	this->insert(_size, appendedString);
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
	/*
	if (pos > this->_size) {
		// non-valid pos
		return;
	}
	*/
	if (pos <= size()) {
		size_t i = 0, j = 0;
		unsigned int tmpSize = this->_size + insertedString._size;
		char* tmpString = new char[tmpSize];
		
		memcpy(tmpString, this->_data, pos);
		for (i = pos; j < insertedString._size; ++i, ++j) {
			tmpString[i] = insertedString._data[j];
		}
		for (j = pos; i < tmpSize; ++i, ++j) {
			tmpString[i] = this->_data[j];
		}

		delete[] this->_data;
		this->_data = tmpString;
		this->_size = tmpSize;
	}
	else throw std::out_of_range("pos > size");
}

void MyString::clear() {
	delete[] _data;
	_size = 0;
}

void MyString::erase(unsigned int pos, unsigned int count) {
	/*
	if (pos >= this->_size) {
		// non-valid pos
		return;
	}
	*/
	if (pos < size()) {
		if (count > this->_size - pos) {
			count = this->_size - pos;
		}

		size_t i = 0, j = 0;
		unsigned int tmpSize = this->_size - count;
		char* tmpString = new char[tmpSize];
		
		memcpy(tmpString, this->_data, pos);
		for (i = pos, j = pos + count; j < this->_size; ++i, ++j) {
			tmpString[i] = this->_data[j];
		}

		delete[] this->_data;
		this->_data = tmpString;
		this->_size = tmpSize;
	}
	else throw std::out_of_range("pos >= size");
}

char& MyString::at(const unsigned int idx) {
    //assert(idx < size());
	if (idx < size()) {
    	return _data[idx];
	}
	throw std::out_of_range("idx >= size");
}

const char& MyString::at(const unsigned int idx) const {
    //assert(idx < size());
	if (idx < size()) {
    	return _data[idx];
	}
	throw std::out_of_range("idx >= size");
}

unsigned int MyString::size() const {
	return _size;
}

bool MyString::isEmpty() const {
	return size() == 0;
}

const char* MyString::rawString() const {
	char* resString = new char[this->_size + 1];
	for (size_t i = 0; i < this->_size; ++i) {
		resString[i] = this->_data[i];
	}
	resString[this->_size] = '\0';
	return resString;
}

unsigned int MyString::find(const MyString& substring, unsigned int pos) {
	size_t i = 0, j = 0;
	for (i = pos; i < this->_size + substring._size; ++i) {
		for (j = 0; j < substring._size && this->_data[i+j] == substring._data[j]; j++);
		if (j == substring._size) {
			return i;
		}
	}
	return -1;
}

int MyString::compare(const MyString& comparableString) const {
	if (this->_size > comparableString._size) {
		return 1;
	}
	else if (this->_size < comparableString._size) {
		return -1;
	}

	for (size_t i = 0; i < this->_size; ++i) {
		if (this->_data[i] > comparableString._data[i]) {
			return 1;
		}
		else if (this->_data[i] < comparableString._data[i]) {
			return -1;
		}
	}
	return 0;
}

char& MyString::operator[](const unsigned int idx) {
    return at(idx);
}

const char& MyString::operator[](const unsigned int idx) const {
    return at(idx);
}

MyString& MyString::operator+(const MyString& appendedString) {
    this->append(appendedString);
    return *this;
}

bool MyString::operator==(const MyString& comparableString) const {
	return (this->compare(comparableString) == 0);
}

bool MyString::operator!=(const MyString& comparableString) const {
	return (this->compare(comparableString) != 0);
}

bool MyString::operator>(const MyString& comparableString) const {
	return (this->compare(comparableString) > 0);
}

bool MyString::operator<(const MyString& comparableString) const {
	return (this->compare(comparableString) < 0);
}

bool MyString::operator>=(const MyString& comparableString) const {
	return (this->compare(comparableString) >= 0);
}

bool MyString::operator<=(const MyString& comparableString) const {
	return (this->compare(comparableString) <= 0);
}