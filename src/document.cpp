#include "core/document.hpp"
#include <cstring>

#include <iostream>

#define BUFFER_CAPACITY 1
document::document()
    :
    _capacity(BUFFER_CAPACITY),
    _size(1),
    _data(new writer*[_capacity]),
    _cursor({0, 0}) {
    _data[0] = new writer{ };
    memory_relocate();
}

document::~document() {
    memory_delete();
}

void document::memory_relocate() {
    size_t old_capacity = _capacity;
    _capacity *= 2;
    writer** new_data = new writer*[_capacity];
    for (size_t index = 0; index < old_capacity; ++index) {
        new_data[index] = _data[index];
    }
    delete _data;
    _data = new_data;
}

void document::memory_delete() {
    //for (size_t index = 0; index < _capacity; ++index) {
    //    delete _data[index];
    //}
    delete _data;
}

void document::remove() {
    _data[_cursor.y]->remove(_cursor.x, 1);
    cursor_move_left(1);
}

void document::input(const char* syms) {
    _data[_cursor.y]->insert(_cursor.x, syms);
    cursor_move_right(strlen(syms));
}

void document::cursor_move_up(const size_t step) {
    if (_cursor.y - step >= 0 && _cursor.y - step <= _size) {
        _cursor.y -= step; 
    }
}

void document::cursor_move_left(const size_t step) {
    if (_cursor.x - step >= 0 && _cursor.x - step <= _data[_cursor.y]->size()) {
        _cursor.x -= step;
    }
}

void document::cursor_move_right(const size_t step) {
    if (_cursor.x + step <= _data[_cursor.y]->size()) {
        _cursor.x += step;
    }
}

void document::cursor_move_down(const size_t step) {
    if (_cursor.y + step <= _size) {
        _cursor.y += step;
    }
}