/**
 * *** This file is part of Luolapeli ***
 *
 * Store build in level data in here.
 */

#include "LevelData.h"


/* ********************************************************************************************* */
LevelData::LevelData(
)
{
    m_LevelsBeaten = 0;
    //CreateLevelDescriptions();
    //CreateLevelData();
}


/* ********************************************************************************************* */
LevelData::~LevelData(
)
{

}


/* ********************************************************************************************* */
auto LevelData::GetLevelsBeaten(
) -> std::int32_t try
{
    std::fstream f("data.dat", std::ios::in);

    // Can't find file, create new one
    if (!f.is_open()) {
        std::fstream f("data.dat", std::ios::out);
        f << 1;
        m_LevelsBeaten = 1;
    }

    // File found, read data
    else {
        std::string data;
        std::getline(f, data);
        m_LevelsBeaten = static_cast<std::int32_t>(std::stoi(data));
    }

    if (f.is_open()) f.close();
    return m_LevelsBeaten;
}
catch (...)
{
    std::string errorMsg("Error: LevelData::GetLevelsBeaten()\n");
    std::cerr << errorMsg;
    throw std::runtime_error("Fatal error\n");
}


/* ********************************************************************************************* */
auto LevelData::SetLevelsBeaten(
    const std::int32_t levelNum
) -> void try
{
    std::fstream f("data.dat", std::ios::out);
    f << levelNum;
    if (f.is_open()) f.close();
}
catch (...)
{
    std::string errorMsg("Error: LevelData::SetLevelsBeaten()\n");
    std::cerr << errorMsg;
    throw std::runtime_error("Fatal error\n");
}


/* ********************************************************************************************* */
auto LevelData::CreateLevelDescriptions()
-> void try
{
    m_LevelDescription.resize(s_NumOfLevels);
    m_LevelDescription.at(0) = "_this_is_custom_level_";
    m_LevelDescription.at(1) = "level1";
    m_LevelDescription.at(2) = "level2";
    m_LevelDescription.at(3) = "level3";
    m_LevelDescription.at(4) = "level4";
    m_LevelDescription.at(5) = "level5";
    m_LevelDescription.at(6) = "level6";
    m_LevelDescription.at(7) = "level7";
    m_LevelDescription.at(8) = "level8";
    m_LevelDescription.at(9) = "level9";
    m_LevelDescription.at(10) = "level10";
    m_LevelDescription.at(11) = "level11";
    m_LevelDescription.at(12) = "level12";
    m_LevelDescription.at(13) = "level13";
    m_LevelDescription.at(14) = "level14";
    m_LevelDescription.at(15) = "level15";
    m_LevelDescription.at(16) = "level16";
    m_LevelDescription.at(17) = "level17";
    m_LevelDescription.at(18) = "level18";
    m_LevelDescription.at(19) = "level19";
    m_LevelDescription.at(20) = "level20";
    m_LevelDescription.at(21) = "level21";
    m_LevelDescription.at(22) = "level22";
    m_LevelDescription.at(23) = "level23";
    m_LevelDescription.at(24) = "level24";
}
catch (const std::out_of_range& e)
{
    std::string errorMsg("Error: LevelData::SetLevelDescriptions(): " + std::string(e.what()) + '\n');
    std::cerr << errorMsg;
    throw std::runtime_error("Fatal error\n");
}


/* ********************************************************************************************* */
auto LevelData::GetLevelDescription(
    const std::size_t index
) -> const char* try
{
    return m_LevelDescription.at(index).c_str();
}
catch (const std::out_of_range& e)
{
    std::string errorMsg("Error: LevelData::GetLevelDescription(): " + std::string(e.what()) + '\n');
    errorMsg.append("Did you remember to call LevelData::SetLevelDescriptions()?\n");
    std::cerr << errorMsg;
    throw std::runtime_error("Fatal error\n");
}


/* ********************************************************************************************* */
auto LevelData::SetLevelGraphicalData(
    const std::size_t levelNum,
    const std::int32_t coordX,
    const std::int32_t coordY
) -> std::uint8_t& try
{
    return m_LevelGraphicalData.at(levelNum).at(coordX).at(coordY);
}
catch (const std::out_of_range& e)
{
    std::string errorMsg("Error: LevelData::SetLevelGraphicalData(): " + std::string(e.what()) + '\n');
    std::cerr << errorMsg;
    throw std::runtime_error("Fatal error\n");
}


/* ********************************************************************************************* */
auto LevelData::GetLevelGraphicalData(
    const std::size_t levelNum,
    const std::int32_t coordX,
    const std::int32_t coordY
) const -> std::uint8_t try
{
    return m_LevelGraphicalData.at(levelNum).at(coordX).at(coordY);
}
catch (const std::out_of_range& e)
{
    std::string errorMsg("Error: LevelData::GetLevelGraphicalData(): " + std::string(e.what()) + '\n');
    std::cerr << errorMsg;
    throw std::runtime_error("Fatal error\n");
}


/* ********************************************************************************************* */
auto LevelData::SetLevelInformationData(
    const std::size_t levelNum,
    const std::int32_t coordX,
    const std::int32_t coordY
) -> std::uint8_t& try
{
    return m_LevelInformationData.at(levelNum).at(coordX).at(coordY);
}
catch (const std::out_of_range& e)
{
    std::string errorMsg("Error: LevelData::SetLevelInformationData(): " + std::string(e.what()) + '\n');
    std::cerr << errorMsg;
    throw std::runtime_error("Fatal error\n");
}


/* ********************************************************************************************* */
auto LevelData::GetLevelInformationData(
    const std::size_t levelNum,
    const std::int32_t coordX,
    const std::int32_t coordY
) const -> std::uint8_t try
{
    return m_LevelInformationData.at(levelNum).at(coordX).at(coordY);
}
catch (const std::out_of_range& e)
{
    std::string errorMsg("Error: LevelData::GetLevelInformationData(): " + std::string(e.what()) + '\n');
    std::cerr << errorMsg;
    throw std::runtime_error("Fatal error\n");
}



/* ********************************************************************************************* */
auto LevelData::CreateLevelData(
) -> void try
{
    // Resize containers
    m_LevelGraphicalData.resize(s_NumOfLevels);
    for (std::size_t i = 0; i < s_NumOfLevels; ++i) {
        m_LevelGraphicalData.at(i).resize(s_LevelHeight);
        for (std::size_t y = 0; y < s_LevelHeight; ++y) {
            m_LevelGraphicalData.at(i).at(y).resize(s_LevelWidth);
        }
    }

    m_LevelInformationData.resize(s_NumOfLevels);
    for (std::size_t i = 0; i < s_NumOfLevels; ++i) {
        m_LevelInformationData.at(i).resize(s_LevelHeight);
        for (std::size_t y = 0; y < s_LevelHeight; ++y) {
            m_LevelInformationData.at(i).at(y).resize(s_LevelWidth);
        }
    }

    // Level 0, which is always going to be overwritten by any custom level
    {
        m_LevelGraphicalData.at(0) = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        m_LevelInformationData.at(0) = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };
    }

    // Level 1
    {
        m_LevelGraphicalData.at(1) = {
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
        };

        m_LevelInformationData.at(1) = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0 }
        };

    }


    // TODO: more build-in levels //


}
catch (const std::out_of_range& e)
{
    std::string errorMsg("Error: LevelData::SetLevelData(): " + std::string(e.what()) + '\n');
    std::cerr << errorMsg;
    throw std::runtime_error("Fatal error\n");
}