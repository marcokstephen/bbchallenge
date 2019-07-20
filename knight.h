#ifndef INCLUDED_KNIGHT_H
#define INCLUDED_KNIGHT_H

#include "item.h"

struct KnightStatus {
    enum Value {
        LIVE,
        DEAD,
        DROWNED
    };
    static std::string toString(const KnightStatus::Value& v)
    {
        switch (v) {
            case LIVE: return "LIVE";
            case DEAD: return "DEAD";
            case DROWNED: return "DROWNED";
        }
        return "";
    }
};

class Knight {

public:

    Knight(char colour, int row, int column);

    const char& colour() const;
    const int& row() const;
    const int& column() const;
    int& attack();
    int& defense();

    // Base attack + item attack modifications + surprise advantage
    double totalAttack();

    // Base defense + item defense modifications
    double totalDefense();

    void setPosition(int row, int column);

    void equipItem(Item& item);
    void dropItem();
    bool hasItem();
    Item& item();

    void fight(Knight& opponent);

    void drown();
    void die();

    KnightStatus::Value status() const;

private:
    char d_colour;
    int d_row;
    int d_column;
    
    int d_attack;
    int d_defense;

    Item *d_item;

    KnightStatus::Value d_status;

};

inline
std::ostream& operator<<(std::ostream& oss, Knight& rhs)
{
    oss << "[";

    if (rhs.status() == KnightStatus::DROWNED) {
        oss << "null,";
    } else {
        oss << "[" << rhs.row() << "," << rhs.column() << "],";
    }

    oss << "\"" << KnightStatus::toString(rhs.status()) << "\",";
    
    if (rhs.hasItem()) {
        oss << rhs.item().key() << ",";
    } else {
        oss << "null,";
    }
    
    oss << rhs.attack() << ",";
    oss << rhs.defense() << "]";
    return oss;
}

#endif // INCLUDED_KNIGHT_H

