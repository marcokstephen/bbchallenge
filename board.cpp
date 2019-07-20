#include "board.h"
#include "utils.h"
#include "config.h"

#include <iostream>

Board::Board(int xLength, int yLength)
    : d_xLength(xLength)
    , d_yLength(yLength)
{
}

void Board::addKnight(const Knight& knight)
{
    char key = knight.colour();
    d_knights.insert( std::pair<char, Knight>(key, knight) );
}

void Board::addItem(const Item& item)
{
    char key = item.key();
    d_items.insert( std::pair<char, Item>(key, item) );
}

Knight& Board::getKnight(char colour)
{
    return d_knights.find(colour)->second;
}

bool Board::tileHasItem(int row, int column)
{
    for (std::map<char, Item>::iterator iter = d_items.begin(); iter != d_items.end(); ++iter)
    {
        Item& item = iter->second;
        if (!item.equipped() && item.row() == row && item.column() == column) return true;
    }
    return false;
}

Item& Board::getItemAtTile(int row, int column)
{
    for (int i = 0; i < Config::NUM_ITEMS; i++) {
        Item& item = d_items.find(Config::ITEM_PICKUP_PRIORITY[i])->second;
        if (!item.equipped() && item.row() == row && item.column() == column) return item;
    }
    throw std::runtime_error("No item found");
}

bool Board::tileHasKnight(int row, int column, char colourToExclude)
{
    for (std::map<char, Knight>::iterator iter = d_knights.begin(); iter != d_knights.end(); ++iter)
    {
        Knight& knight = iter->second;
        if (knight.colour() != colourToExclude && knight.row() == row && knight.column() == column) return true;
    }
    return false;
}

Knight& Board::getKnightAtTile(int row, int column, char colourToExclude)
{
    for (std::map<char, Knight>::iterator iter = d_knights.begin(); iter != d_knights.end(); ++iter)
    {
        Knight& knight = iter->second;
        if (knight.colour() != colourToExclude && knight.row() == row && knight.column() == column) return knight;
    }
    throw std::runtime_error("No knight found");
}

void Board::printState()
{
    for (std::map<char, Knight>::iterator iter = d_knights.begin(); iter != d_knights.end(); ++iter)
    {
        std::cout << iter->first << ": " << iter->second << std::endl;
    }
    for (std::map<char, Item>::iterator iter = d_items.begin(); iter != d_items.end(); ++iter)
    {
        std::cout << iter->first << ": " << iter->second << std::endl;
    }
}

void Board::processMove(char colour, char direction)
{
    std::cout << "moving " << colour << " to " << direction << std::endl;
    Knight& knight = getKnight(colour);

    // Check the living status of the knight 
    if (knight.status() != KnightStatus::LIVE) {
        Utils::log("Attempting to move non-live knight, exiting turn early");
        return;
    }

    // Determine the current coordinates
    int oldRow = knight.row();
    int oldColumn = knight.column();

    // Determine the new coordinates
    switch (direction) {
        case 'N':
            oldRow--;
            break;
        case 'S':
            oldRow++;
            break;
        case 'E':
            oldColumn++;
            break;
        case 'W':
            oldColumn--;
            break;
        default:
            Utils::log("Invalid move direction");
            return;
    }

    // Determine if the knight drowned
    if (oldColumn < 0 || oldColumn > d_xLength || oldRow < 0 || oldRow > d_yLength) {
        Utils::log("Knight drowned!");
        knight.drown();
        return;
    }
    
    // Set the new position for the knight
    knight.setPosition(oldRow, oldColumn);

    // See if there are items to pick up
    if (!knight.hasItem() && tileHasItem(knight.row(), knight.column())) {
        Utils::log("Knight equipped item!");
        knight.equipItem(getItemAtTile(knight.row(), knight.column()));
    }

    // See if there are knights to fight
    if (tileHasKnight(knight.row(), knight.column(), knight.colour())) {
        Utils::log("Knight fight!");
        Knight& opponent = getKnightAtTile(knight.row(), knight.column(), knight.colour());
        knight.fight(opponent);
    }
}