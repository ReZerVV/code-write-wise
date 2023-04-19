#include "core/writer.hpp"
#include <cstring>

#include <iostream>

#define BUFFER_CAPACITY 1
writer::writer()
    :
    _capacity(BUFFER_CAPACITY),
    _size(0),
    _buffer(nullptr) {
    memory_relocate();
}

writer::~writer() {
    memory_delete();
}

void writer::memory_relocate() {
    _capacity *= 2;
    char* new_buffer = new char[_capacity];
    std::memcpy(new_buffer, _buffer, _size);
    memory_delete();
    _buffer = new_buffer;
}

void writer::memory_delete() {
    delete _buffer;
}

bool writer::empty() const {
    return _size == 0;
}

size_t writer::size() const {
    return _size;
}

size_t writer::capacity() const {
    return _capacity;
}

char* writer::c_str() {
    return _buffer;
}


char& writer::operator[](const size_t pix) {
    if (0 > pix || pix > _size) {
        throw "index out of range";
    }
    return _buffer[pix];
}

bool writer::insert(const size_t pix, const char* syms) {
    if (0 > pix || pix > _size) {
        return false;
    }

    if (_size + strlen(syms) < _capacity) {
        std::memmove(&_buffer[pix + strlen(syms)], &_buffer[pix], _size - pix);
        std::memcpy(&_buffer[pix], syms, strlen(syms));
        _size += strlen(syms);
        return true;
    } else {
        memory_relocate();
        return insert(pix, syms);
    }
    return false;
}

bool writer::input(const char* syms) {
    if (_size + strlen(syms) < _capacity) {
        std::memcpy(&_buffer[_size], syms, strlen(syms));
        _size += strlen(syms);
        return true;
    } else {
        memory_relocate();
        return input(syms);
    }
    return false;
}

bool writer::remove(const size_t pix, const size_t length) {
    if (0 > pix || pix > _size) {
        return false;
    }

    if (0 <= pix - length && pix - length < _size) {
        if (pix < _size - 1) {
            std::memcpy(&_buffer[pix], &_buffer[pix + length], _size - pix);
        }
        _size -= length;
        return true;
    }
    return false;
}
