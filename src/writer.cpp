#include "core/writer.hpp"
#include <cstring>

#include <iostream>

#define DATA_CAPACITY 1
writer::writer()
    :
    _capacity(DATA_CAPACITY),
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

void writer::insert(const size_t pix, const char* syms) {
    if (0 > pix || pix > _size) {
        return;
    }

    if (_size + strlen(syms) < _capacity) {
        std::memmove(&_buffer[pix + strlen(syms)], &_buffer[pix], _size - pix);
        std::memcpy(&_buffer[pix], syms, strlen(syms));
        _size += strlen(syms);
    } else {
        memory_relocate();
        insert(pix, syms);
    }
}

void writer::input(const char* syms) {
    if (_size + strlen(syms) < _capacity) {
        std::memcpy(&_buffer[_size], syms, strlen(syms));
        _size += strlen(syms);
    } else {
        memory_relocate();
        input(syms);
    }
}

void writer::remove(const size_t pix, const size_t remove_count) {
    if (0 > pix || pix > _size) {
        return;
    }

    if (0 <= pix - remove_count && pix - remove_count < _size) {
        std::memcpy(&_buffer[pix - remove_count], &_buffer[pix], remove_count);
        _size -= remove_count;
    }
}
