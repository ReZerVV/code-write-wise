#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

#if MODE == DEBUG

#include "core/writer.hpp"

#endif

int main(int argc, char** argv) {

#if MODE == DEBUG
    std::cout << "MODE: DEBUG" << std::endl;

    writer w{ };
    std::cout << "w._input" << std::endl;
    for (int index = 0; index < 10; ++index) {
        w.input("|\0");
    }
    
    std::cout << "w._remove" << std::endl;
    w.remove(10, 10);

    std::cout << "w._insert" << std::endl;
    w.insert(0, "h\0");
    w.insert(0, "e\0");
    w.insert(0, "l\0");
    w.insert(0, "l\0");
    w.insert(0, "o\0");

    std::cout << "w._data" << std::endl;
    if (w._size == 0) {
        std::cout << "w._size: EMPTY." << std::endl;
    } else {
        for (int index = 0; index < w._size; ++index) {
            std::cout << w._data[index];
        }
        std::cout << std::endl;
    }

#endif

}