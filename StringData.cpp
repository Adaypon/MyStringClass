#include "StringData.h"

StringData::StringData() {
	_data.flag = false;
	_data._unionData.shortString._size = 0;
}

StringData::~StringData() {
    if (_data.flag) {
        delete[] _data._unionData.longString._data;
        _data._unionData.longString._data = nullptr;
        _data._unionData.longString._size = 0;
        _data.flag = false;
    }
    else {
        _data._unionData.shortString._size = 0;
    }
}

unsigned int StringData::size() const {
    if (_data.flag) {
        return _data._unionData.longString._size;
    }
    else {
        return _data._unionData.shortString._size;
    }
}

char& StringData::at(const unsigned int idx) {
    if (_data.flag) {
        return _data._unionData.longString._data[idx];
    }
    else {
        return _data._unionData.shortString._data[idx];
    }
}

const char& StringData::at(const unsigned int idx) const {
    if (_data.flag) {
        return _data._unionData.longString._data[idx];
    }
    else {
        return _data._unionData.shortString._data[idx];
    }
}

void StringData::resize(const unsigned int length) {
    if (_data.flag) {
        delete[] _data._unionData.longString._data;
        _data._unionData.longString._data = nullptr;
        _data._unionData.longString._size = 0;
    }

    _data.flag = (length > sizeof(_data._unionData.longString) - sizeof(char));
    if (_data.flag) {
        _data._unionData.longString._size = length;
        _data._unionData.longString._data = new char[length];
    }
    else {
        _data._unionData.shortString._size = length;
    }
}