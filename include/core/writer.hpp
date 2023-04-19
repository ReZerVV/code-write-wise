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
    bool remove(const size_t pix, const size_t length);
    bool insert(const size_t pix, const char* syms);
    bool insert(const size_t pix, const char* syms, const size_t length);
    bool input(const char* syms);
    // void find();
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    char* c_str();
    char& at(const size_t pix);
    char& operator[](const size_t pix);
private:
    void memory_relocate();
    void memory_delete();
private:
    size_t _capacity;
    size_t _size;
    char* _buffer;
};

#endif