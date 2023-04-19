#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

#if MODE == DEBUG

#include "core/document.hpp"

#endif

int main(int argc, char** argv) {

#if MODE == DEBUG
    std::cout << "MODE: DEBUG" << std::endl;
    
    if(SDL_Init(SDL_INIT_EVENTS) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("cww", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    bool quit = false;

    const size_t KEYS_COUNT = 128;
    bool KEYS[KEYS_COUNT];
    for (size_t key = 0; key < KEYS_COUNT; ++key) {
        KEYS[key] = false;
    }

    document d{ };

    while (!quit) {
        while(SDL_PollEvent(&event)) {
            switch( event.type ) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    d.remove();
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    d.cursor_move_up(1);
                }
                if (event.key.keysym.sym == SDLK_LEFT) {
                    d.cursor_move_left(1);
                }
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    d.cursor_move_right(1);
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    d.cursor_move_down(1);
                }
                if (event.key.keysym.sym <= 127) {
                    KEYS[event.key.keysym.sym] = true;
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym <= 127) {
                    KEYS[event.key.keysym.sym] = false;
                }
                break;
            case SDL_TEXTINPUT:
                d.input(event.text.text);
                break;
            default:
                break;
            }
        }
        
        std::cout << "_cursor: " << d._cursor.y << ' ' << d._cursor.x << std::endl;

        for (size_t line = 0; line < d._size; ++line) {
            std::cout << line << '\t';
            for (size_t index = 0; index < d._data[line]->size(); ++index) {
                std::cout << d._data[line]->c_str()[index];
                if (d._cursor.y == line && d._cursor.x == index) {
                    std::cout << '|';
                }
            }
            if (d._cursor.y == line && d._cursor.x == d._data[line]->size()) {
                std::cout << '|';
            }
            std::cout << std::endl;
        }
        system("clear");
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

#endif
    return 0;
}