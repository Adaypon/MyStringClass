#include "MyStringException.h"

MyStringException::MyStringException(const MyString& str, const unsigned int idx) {
	_size = str.size();
	_idx = idx;
}

AtException::AtException(const MyString& str, const unsigned int idx) : MyStringException(str, idx) {}

const char* AtException::what() const noexcept {
	char* s = new char[256];
	sprintf(s, "Called at(%d) on string of size %d\n", _idx, _size);
	return s;
}

InsertException::InsertException(const MyString& str, const unsigned int idx) : MyStringException(str, idx) {}

const char* InsertException::what() const noexcept {
	char* s = new char[256];
	sprintf(s, "Called insert(%d) on string of size %d\n", _idx, _size);
	return s;
}

EraseException::EraseException(const MyString& str, const unsigned int idx) : MyStringException(str, idx) {}

const char* EraseException::what() const noexcept {
	char* s = new char[256];
	sprintf(s, "Called erase(%d) on string of size %d\n", _idx, _size);
	return s;
}