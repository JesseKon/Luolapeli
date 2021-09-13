/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <cstdint>


// Window properties
inline constexpr std::int32_t SCREEN_WIDTH = 800;
inline constexpr std::int32_t SCREEN_HEIGHT = 640;
inline constexpr std::int32_t SCREEN_FPS = 24;      // FPS limit

// Tile width and height in pixels
inline constexpr std::int32_t TILE_WIDTH = 16;
inline constexpr std::int32_t TILE_HEIGHT = 16;

// Total number of unique graphical and information tiles
inline constexpr std::int32_t NUM_OF_TILES = 10;
inline constexpr std::int32_t NUM_OF_INFO_TILES = 4;


#endif  // _CONSTANTS_H_