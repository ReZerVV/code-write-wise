#ifndef CORE_WRITER_H
#define CORE_WRITER_H

#include <cstddef>

class writer {
public:
    writer();
    ~writer();
// Not movable constructor.
    writer(const writer&) = default;
// Movable constructor.
    writer(writer&&) = default;
public:
    void remove(const size_t pix, const size_t count);
    void insert(const size_t pix, const char* syms);
    void input(const char* syms);
    // void find();
private:
    void memory_relocate();
    void memory_delete();
public:
    size_t _capacity;
    size_t _size;
    char* _buffer;
};

#endif