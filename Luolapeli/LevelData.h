/**
 * *** This file is part of Luolapeli ***
 *
 * 
 */

#ifndef _LEVEL_DATA_H_
#define _LEVEL_DATA_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class LevelData
{
public:

    /**
     *
     */
    LevelData(
    );


    /**
     * 
     */
    ~LevelData(
    );


    static constexpr std::int32_t s_NumOfLevels = 25; // Total number of levels including index 0 for custom levels
    static constexpr std::int32_t s_LevelWidth = 25;  // Level width in tiles
    static constexpr std::int32_t s_LevelHeight = 16; // Level height in tiles

public:

    /**
     * Creates descriptions for build in levels.
     */
    auto CreateLevelDescriptions(
    ) -> void;


    /**
     * Creates build in levels.
     */
    auto CreateLevelData(
    ) -> void;


    /**
     * Returns the amount of build in levels player has beaten. If 'data.dat' file can't be found, it
     * creates a new file and unlocks the first level.
     */
    auto GetLevelsBeaten(
    ) -> std::int32_t;


    /**
     * Sets the number of levels beaten. Use this to unlock new level after previous is beaten.
     */
    auto SetLevelsBeaten(
        const std::int32_t levelNum
    ) -> void;


    /**
     * Returns build in level description of given index.
     */
    auto GetLevelDescription(
        const std::size_t index
    ) -> const char*;


    /**
     * Sets graphical tile info to given level number and coordinates.
     */
    auto SetLevelGraphicalData(
        const std::size_t levelNum,
        const std::int32_t coordX,
        const std::int32_t coordY
    ) -> std::uint8_t&;


    /**
     * Returns graphical tile info from given level number and coordinates.
     */
    auto GetLevelGraphicalData(
        const std::size_t levelNum,
        const std::int32_t coordX,
        const std::int32_t coordY
    ) const -> std::uint8_t;


    /**
     * Sets information tile info to given level number and coordinates.
     */
    auto SetLevelInformationData(
        const std::size_t levelNum,
        const std::int32_t coordX,
        const std::int32_t coordY
    ) -> std::uint8_t&;


    /**
     * Returns information info tile from given level number and coordinates.
     */
    auto GetLevelInformationData(
        const std::size_t levelNum,
        const std::int32_t coordX,
        const std::int32_t coordY
    ) const -> std::uint8_t;


private:

    /**
     * Build in levels up to this number can be accessed. Levels beyond this will be
     * greyed out.
     */
    std::int32_t m_LevelsBeaten;

    // Contains level descriptions which are visible in main menu level list
    std::vector<std::string> m_LevelDescription;

    /**
     * 3 dimensions: [level_number], [level_width], [level_height], and every tile is
     * type of uint8_t.
     */
    using LevelStructureType = std::vector<std::vector<std::vector<std::uint8_t>>>;

    /**
     * Contains all levels graphical layer. Tile id's are:
     * 0 -> Floor
     * 1 -> Wall
     * 2 -> Door upwards
     * 3 -> Door rightwards
     * 4 -> Locked door upwards
     * 5 -> Locked door rightwards
     * 6 -> Door leftwards
     * 7 -> Door downwards
     * 8 -> Locked door leftwards
     * 9 -> Locked door downwards
     */
    LevelStructureType m_LevelGraphicalData;

    /**
     * Contains all levels information layer. Tile id's are:
     * -> 0 = Nothing
     * -> 1 = Enter tile / Player spawn
     * -> 2 = Key
     * -> 3 = Stone
     * -> 4 = Exit tile
     */
    LevelStructureType m_LevelInformationData;

};

#endif  // _LEVEL_DATA_H_