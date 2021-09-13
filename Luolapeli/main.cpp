/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#include <iostream>
#include <string>
#include <stdexcept>

#include <SDL.h>
#include <SDL_mixer.h>

#include "Luolapeli.h"


auto SDL_main(int argc, char** argv) -> int try {
    Luolapeli luolapeli(SCREEN_WIDTH, SCREEN_HEIGHT, "Luolapeli");
    return EXIT_SUCCESS;
}

catch (const std::runtime_error& e) {
    std::cerr << e.what();
    return EXIT_FAILURE;
}

catch (...) {
    std::cerr << "Unknown fatal error\n";
    return EXIT_FAILURE;
}