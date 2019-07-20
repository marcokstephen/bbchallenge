#include "knight.h"
#include "board.h"
#include "item.h"
#include "config.h"
#include "moveparser.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Usage: ./game <movefile>" << std::endl;
        return 0;
    }

    Board board(Config::BOARD_ROWS, Config::BOARD_COLUMNS);

    board.addKnight(Knight('R', 0, 0));
    board.addKnight(Knight('B', 7, 0));
    board.addKnight(Knight('G', 7, 7));
    board.addKnight(Knight('Y', 0, 7));

    board.addItem(Item('A', 2, 2, 2, 0));
    board.addItem(Item('D', 2, 5, 1, 0));
    board.addItem(Item('M', 5, 2, 0, 1));
    board.addItem(Item('H', 5, 5, 1, 1));

    try {
        MoveParser moves(argv[1]);
        while (moves.hasNextMove()) {
            Move m = moves.nextMove();
            board.processMove(m.knight, m.direction);
        }

    //         board.processMove('R', 'S');
    // board.processMove('R', 'S');
    // board.processMove('R', 'E');
    // board.processMove('R', 'E');
    // board.processMove('R', 'E');
    // board.processMove('R', 'E');
    // board.processMove('R', 'E');
    // board.processMove('R', 'E');
    // board.processMove('R', 'E');
    // board.processMove('R', 'N');
    // board.processMove('R', 'N');
    // board.processMove('R', 'N');

    } catch (const std::exception& e) {
        std::cout << "Failed with exception: " << e.what() << std::endl;
    }

    board.printState();

    return 0;
}
