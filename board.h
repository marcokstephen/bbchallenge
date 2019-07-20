#ifndef INCLUDED_BOARD_H
#define INCLUDED_BOARD_H

#include "knight.h"
#include "item.h"

#include <vector>
#include <map>

class Board {

public:

    Board(int xLength, int yLength);

    // Add a knight to the board
    void addKnight(const Knight& knight);

    // Add an item to the board
    void addItem(const Item& item);

    // Return a knight by reference by its colour
    Knight& getKnight(char colour);

    // Determine if there is a knight at a given tile
    bool tileHasKnight(int row, int column, char colourToExclude);

    // Return the knight at this row/column, other than the colourToExclude (if !tileHasKnight(), behaviour is undefined)
    Knight& getKnightAtTile(int row, int column, char colourToExclude);

    // Determine if there are items at a given tile
    bool tileHasItem(int row, int column);

    // Return the item at this row/column (if !tileHasItem(), behaviour is undefined)
    Item& getItemAtTile(int row, int column);

    // Change a board state by processing a single move
    void processMove(char knight, char direction);

    // Print the current state of the board including knights and items
    void printState();

private:
    int d_xLength;
    int d_yLength;

    std::map<char, Knight> d_knights;
    std::map<char, Item> d_items;
};

#endif //INCLUDED_BOARD_H
