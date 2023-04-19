#include "core/document.hpp"
#include <cstring>
#include <fstream>

#include <iostream>
#include <string>

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
    delete _data;
}

void document::remove() {
    if (_data[_cursor.y]->empty() && _size > 1 && _cursor.y > 0) {
        if (_cursor.y < _size - 1) {
            for (size_t line = _cursor.y; line < _size; ++line) {
                std::swap(_data[line], _data[line+1]);
            }
        }
        delete _data[_size];
        _size -= 1;
        cursor_move_up(1);
    } else if (_data[_cursor.y]->remove(_cursor.x, 1)) {
        cursor_move_left(1);
    }
}

void document::input(const char* syms) {
    if (_data[_cursor.y]->insert(_cursor.x, syms)) {
        cursor_move_right(strlen(syms));
    }
}

void document::new_line() {
    if (_size < _capacity) {
        _data[_size] = new writer{ };
        if (! _data[_cursor.y]->empty() && _cursor.x < _data[_cursor.y]->size() - 1) {
            /*
            for (size_t index = _cursor.x; index < _data[_cursor.y]->size(); ++index) {
                _data[_size]->insert(_data[_cursor.y]->at(index), 1);
            }
            */
            _data[_size]->insert(0, &_data[_cursor.y]->c_str()[_cursor.x], _data[_cursor.y]->size() - _cursor.x);

            _data[_cursor.y]->remove(_data[_cursor.y]->size() - 1, _data[_cursor.y]->size() - _cursor.x);
        }
        if (_cursor.y < _size - 1) {
            for (size_t line = _size; line > _cursor.y; --line) {
                std::swap(_data[line], _data[line-1]);
            }
        }
        _size += 1;
        cursor_move_down(1);
    } else {
        memory_relocate();
        new_line();
    }
}

bool document::cursor_move_up(const size_t step) {
    if (_cursor.y - step >= 0 && _cursor.y - step < _size) {
        _cursor.y -= step; 
        if (_cursor.x >= _data[_cursor.y]->size()) {
            _cursor.x = _data[_cursor.y]->size();
        }
        return true;
    }
    return false;
}

bool document::cursor_move_left(const size_t step) {
    if (_cursor.x - step >= 0 && _cursor.x - step <= _data[_cursor.y]->size()) {
        _cursor.x -= step;
        return true;
    }
    return false;
}

bool document::cursor_move_right(const size_t step) {
    if (_cursor.x + step <= _data[_cursor.y]->size()) {
        _cursor.x += step;
        return true;
    }
    return false;
}

bool document::cursor_move_down(const size_t step) {
    if (_cursor.y + step < _size) {
        _cursor.y += step;
        if (_cursor.x >= _data[_cursor.y]->size()) {
            _cursor.x = _data[_cursor.y]->size();
        }
        return true;
    }
    return false;
}

void document::clear() {
    memory_delete();
    _size = 1;
    _cursor = {0, 0};
    _data[0] = new writer{ };
}


bool document::load(const char* file_path) {
    std::ifstream file;
    file.open(file_path);
    if (!file.is_open()) {
        return false;
    } else {
        char ch;
        while(file.get(ch)) {
            if (ch == '\n') {
                new_line();
            } else {
                char str[2] = {ch, '\0'};
                input(str);
            }
        }
    }

    file.close();
    return true;
}

bool document::save(const char* file_path) {
    std::ofstream file;
    file.open(file_path);
    if (!file.is_open()) {
        return false;
    } else {
        for (size_t line = 0; line < _size; ++line) {
            for (size_t index = 0; index < _data[line]->size(); ++index) {
                file << _data[line]->at(index);
            }
            file << std::endl;
        }
    }
    file.close();
    return true;
}