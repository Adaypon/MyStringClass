#pragma once

#include <exception>
#include <cstdio>
#include "MyString.h"

class MyString;

class MyStringException : public std::exception {
public:
	MyStringException(const MyString& str, const unsigned int idx);
protected:
	unsigned int _size;
	unsigned int _idx;
};


class AtException : public MyStringException {
public:
	AtException(const MyString& str, const unsigned int idx);
	const char* what() const noexcept override;
};

class InsertException : public MyStringException {
public:
	InsertException(const MyString& str, const unsigned int idx);
	const char* what() const noexcept override;
};


class EraseException : public MyStringException {
public:
	EraseException(const MyString& str, const unsigned int idx);
	const char* what() const noexcept override;
};