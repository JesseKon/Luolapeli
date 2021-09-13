/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#ifndef _LEVEL_EDITOR_H_
#define _LEVEL_EDITOR_H_

#include <iostream>
#include <fstream>
#include <filesystem>

#include <SDL.h>

#include "Constants.h"
#include "Game.h"
#include "LevelData.h"
#include "Resources.h"


class LevelEditor : public Resources
{
public:

    /**
     * 
     */
    LevelEditor(
        SDL_Window* const window,
        SDL_Renderer* const renderer
    );


    /**
     * 
     */
    ~LevelEditor(
    );


    /**
     * Starts the editor after resources are loaded.
     */
    auto StartEditor(
    ) -> void;


private:

    /**
     * Initializes an empty level.
     */
    auto InitEmptyLevel(
    ) -> void;


    /**
     * Save the current level.
     */
    auto SaveLevel(
    ) -> void;


    /**
     * Load level.
     */
    auto LoadLevel(
    ) -> void;


    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    std::string m_LevelName;

    // The active and currently editable tile
    struct Cursor {
        std::int32_t x;
        std::int32_t y;
        std::int32_t color;      // 0 - 255
        std::int32_t dir;        // color direction: 1 to increase, -1 to decrease
    } m_Cursor;

    std::vector<std::vector<std::uint8_t>> m_LevelGraphicalData;
    std::vector<std::vector<std::uint8_t>> m_LevelInformationData;

};

#endif  // _LEVEL_EDITOR_H_