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
#endif

}