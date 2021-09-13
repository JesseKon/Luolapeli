/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#ifndef _MENU_H_
#define _MENU_H_

#include <string>
#include <stdexcept>
#include <memory>

#include "SDL.h"
#include "Font.h"
#include "Game.h"
#include "LevelEditor.h"


class Menu
{
public:

    /**
     * 
     */
    Menu(
        SDL_Window* const window,
        SDL_Renderer* const renderer
    );


    /**
     * 
     */
    ~Menu(
    );


    /**
     * Starts menu.
     */
    auto StartMenu(
    ) -> void;


    /**
     * Activates menu item based on choice. Param quit is returned if quit game was requested.
     */
    auto ActivateMenuItem(
        const std::int32_t choice, 
        bool& quit
    ) -> void;


    /**
     * Menu item that lists and allows to play build in levels.
     */
    auto Menu_Play(
    ) -> void;


    /**
     * Menu item that lists and allows to play custom levels.
     */
    auto Menu_PlayCustom(
    ) -> void;


    /**
     * Menu item that takes to level editor.
     */
    auto Menu_LevelEditor(
    ) -> void;


    /**
     * Menu item that shows credits.
     */
    auto Menu_Credits(
    ) noexcept -> void;


    /**
     * Menu item that shows game options.
     */
    auto Menu_Options(
    ) noexcept -> void;


    /**
     * Starts given level number. If level number on 0, it starts a custom map thats specified in
     * the filename.
     */
    auto StartLevel(
        std::int32_t levelNum, 
        const std::string& filename
    ) -> void;


private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    Font* m_Font;
    std::unique_ptr<LevelData> levelData;

};

#endif  // _MENU_H_