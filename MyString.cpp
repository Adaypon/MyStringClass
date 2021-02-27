#include "MyString.h"

#include <cassert>
#include <cstdlib>
#include <cstring>

MyString::MyString(const char* rawString) 
	: _size(strlen(rawString)), _data(new char[_size]) {
	//| TODO try memcpy()
    for (size_t i = 0; i < _size; ++i) {
		this->_data[i] = rawString[i];		
	}
}

MyString::MyString(const MyString& other) {
	this->_size = other._size;
	this->_data = new char[_size];
	for (size_t i = 0; i < this->_size; ++i) {
		this->_data[i] = copy._data[i];
	}
}

MyString::MyString(MyString&& other) noexcept {
	this->_size = other._size;
	this->_data = ohter._data;
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
	char* tmpString = new char[this->_size + appendedString._size];
	for (size_t i = 0; i < this->_size; ++i) {
		tmpString[i] = this->_data;
	}
	for (size_t j = 0; j < appendedString._size; ++j) {
		tmpString[j] = appendedString._data[j];		
	}
	delete[] this->_data;
	this->_data = tmpString;
	this->_size += appendedString;
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
	if (pos >= this->_size) {
		// non-valid pos
		return;
	}
	size_t i = 0, j = 0;
	unsigned int tmpSize = this->_size + insertedString._size;
	char* tmpString = new char[tmpSize];
	
	
	for (; i < pos; ++i) {
		tmpString[i] = this->_data[i];
	}
	for (j = i; j < insertedString._size; ++j) {
		tmpString[j] = insertedString._data[j];
	}
	for (; j < tmpSize; j++, i++) {
		tmpString[j] = this->_data[i];
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