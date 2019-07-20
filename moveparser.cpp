#include "moveparser.h"

#include <iostream>
#include <fstream>

MoveParser::MoveParser(const std::string& filename)
{
    std::ifstream movefile(filename);
    if (!movefile.is_open()) {
        throw std::runtime_error("Can't find move file!");
    }

    std::string line;
    getline(movefile, line);
    if (line != "GAME-START") throw std::invalid_argument("Bad line in input!");

    while (getline(movefile, line)) {
        parseLine(line);
    }
}

void MoveParser::parseLine(const std::string& line)
{
    if (line == "GAME-END") return;

    if (line.length() != 3) throw std::invalid_argument("Bad line in input");
    if (line.at(1) != ':') throw std::invalid_argument("Bad line in input");

    Move m;
    m.knight = line.at(0);
    m.direction = line.at(2);

    if (!validMove(m)) throw std::invalid_argument("Bad line in input");
    d_moves.push(m);
}

bool MoveParser::validMove(const Move& move)
{
    return (move.knight == 'R' || move.knight == 'G' || move.knight == 'B' || move.knight == 'Y') &&
           (move.direction == 'N' || move.direction == 'S' || move.direction == 'E' || move.direction == 'W');
}

bool MoveParser::hasNextMove() {
    return !d_moves.empty();
}

Move MoveParser::nextMove()
{
    Move move = d_moves.front();
    d_moves.pop();
    return move;
}
