#ifndef CORE_DOCUMENT_H
#define CORE_DOCUMENT_H

#include "core/writer.hpp"

class document {
public:
    document();
    ~document();
// Not movable constructos.
    document(const document&) = default;
// Movable constructos.
    document(document&&) = default;
public:
    void remove();
    void input(const char* syms);

    void cursor_move_up(const size_t step);
    void cursor_move_left(const size_t step);
    void cursor_move_right(const size_t step);
    void cursor_move_down(const size_t step);
private:
    void memory_relocate();
    void memory_delete();
private:
    struct cursor {
        size_t x;
        size_t y;
    };
public:
    size_t      _capacity;
    size_t      _size;
    writer**    _data;
    cursor      _cursor;
};

#endif