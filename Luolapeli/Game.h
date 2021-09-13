/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#ifndef _GAME_H_
#define _GAME_H_

#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <memory>

#include <SDL.h>
#include <SDL_mixer.h>

#include "Constants.h"
#include "Font.h"
#include "LevelData.h"
#include "Resources.h"


class Game : public Resources
{
public:

    /**
     * Creates new game area.
     * -> The window in which the game renderer is.
     * -> The renderer.
     * -> The level number which to play. Number 0 represents custom maps and from 1 onwards
     *    represent the build in maps.
     * -> The name of the level, which is shown in splash screen before game starts. Only
     *    custom maps show it.
     */
    Game(
        SDL_Window* const window,
        SDL_Renderer* const renderer, 
        const int levelNum, 
        const std::string& levelName
    );


    /**
     *
     */
    ~Game(
    );


    /**
     * Returns true if level restart was requested by player.
     */
    auto RestartLevel(
    ) const noexcept -> bool;


    /**
     * Returns current level number or 0 if it's a custom level.
     */
    auto LevelNum(
    ) const noexcept -> std::int32_t;

private:

    // Possible moving directions for player
    enum class MoveDirection { 
        UP, DOWN, LEFT, RIGHT 
    };

    /**
     * Starts level.
     * Build in levels start from 1, and level 0 is reserved for any custom level.
     */
    auto PlayLevel(
        const int levelNum,
        const std::string& levelName
    ) -> void;


    /**
     * Moves player by one tile to given direction. Checks for collisions and item pick-ups.
     */
    auto MovePlayer(
        const MoveDirection moveDirection
    ) -> void;


    /**
     * Called when player reaches the exit tile.
     */
    auto ReachedExit(
    ) noexcept -> void;


    /**
     * TODO: 
     */
    auto SetLevelDescriptions(
    ) noexcept -> void;


private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    // Indicator for whether restart is requested
    bool m_RestartLevel;

    // The level number that's being played, from 1 onwards
    // If custom level is beign played, this will be 0
    std::int32_t m_LevelNum;

    // Number of keys the player is holding
    std::int32_t m_NumOfKeys;

    // Number of steps player has taken
    std::int32_t m_StepsTaken;

    // Player position
    struct PlayerPos {
        std::int32_t x;
        std::int32_t y;
    } m_PlayerPos;

    // Key positions
    struct KeyPos {
        std::int32_t x;
        std::int32_t y;
    };
    std::vector<KeyPos> m_KeyPos;

    // Stone positions
    struct StonePos {
        std::int32_t x;
        std::int32_t y;
    };
    std::vector<StonePos> m_StonePos;

    std::unique_ptr<LevelData> m_LevelData;
};

#endif  // _GAME_H_