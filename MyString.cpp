#include "MyString.h"

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>

MyString::MyString(const char* rawString) 
	: _size(strlen(rawString)), _data(new char[_size]) {
	memcpy(this->_data, rawString, _size);
}

MyString::MyString(const MyString& other) {
	this->_size = other._size;
	this->_data = new char[_size];
	for (size_t i = 0; i < this->_size; ++i) {
		this->_data[i] = other._data[i];
	}
}

MyString::MyString(MyString&& other) noexcept {
	this->_size = other._size;
	this->_data = other._data;
	other._size = 0;
	other._data = nullptr;
}

MyString& MyString::operator=(const MyString& other) {
	MyString copy(other);
	std::swap(this->_data, copy._data);
	std::swap(this->_size, copy._size);
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    // TODO
	
    return *this;
}

MyString::~MyString() {
	delete[] _data;
}

void MyString::append(const MyString& appendedString) {
	size_t i = 0, j = 0;
	unsigned int tmpSize = this->_size + appendedString._size;
	char* tmpString = new char[tmpSize];
	
	memcpy(tmpString, this->_data, this->_size);
	for (i = this->_size; j < tmpSize; ++i, ++j) {
		tmpString[i] = appendedString._data[j];		
	}
		
	delete[] this->_data;
	this->_data = tmpString;
	this->_size = tmpSize;
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
	if (pos >= this->_size) {
		// non-valid pos
		return;
	}
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

void MyString::clear() {
	_data = nullptr;
	_size = 0;
}

void MyString::erase(unsigned int pos, unsigned int count) {
	if (pos >= this->_size) {
		// non-valid pos
		return;
	}
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

char& MyString::at(const unsigned int idx) {
    assert(idx < size());
    return _data[idx];
}

const char& MyString::at(const unsigned int idx) const {
    assert(idx < size());
    return _data[idx];
}

unsigned int MyString::size() const {
	return _size;
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

void MyString::print() {
	for (int i = 0; i < _size; ++i) {
		std::cout << _data[i];
	}
}

int main() {
	
	MyString str("Hello");
	MyString str2("Hi");
	MyString str3("TEST");
	str.append(str2);
	str.print();
	std::cout << std::endl;
	str.insert(3, str3);
	str.print();
	std::cout << std::endl;
	str.erase(3, 4);
	str.print();
	std::cout << std::endl;
	return 0;
}