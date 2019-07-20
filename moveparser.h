#ifndef INCLUDED_MOVE_PARSER_H
#define INCLUDED_MOVE_PARSER_H

#include <string>
#include <queue>

struct Move {
    char knight;
    char direction;
};

class MoveParser {

public:

    MoveParser(const std::string& filename);

    bool hasNextMove();
    Move nextMove();

private:

    void parseLine(const std::string& line);
    bool validMove(const Move& move);

    std::queue<Move> d_moves;

};

#endif // INCLUDED_MOVE_PARSER_H
