#pragma once
#include <cstdlib>


class StringData {
private:
    struct StringRepresentation {
        union {
            struct {
                char* _data;
                size_t _size;
            } longString;

            struct {
                char _data[sizeof(longString) - sizeof(char)];
                unsigned char _size;
            } shortString;
        } _unionData;
        bool flag; // true - longString, false - shortString 
    };
    StringRepresentation _data;

public:
    StringData();
    ~StringData();

    unsigned int size() const;
    char& at(unsigned int idx);
    const char& at(unsigned int idx) const;
    void resize(const unsigned int length);
};