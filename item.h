#ifndef INCLUDED_ITEM_H
#define INCLUDED_ITEM_H

#include <sstream>

class Item {

public:

    Item(char key, int row, int column, int attack, int defense);

    const char& key() const;
    int& row();
    int& column();
    int& attack();
    int& defense();

    bool& equipped();

private:

    char d_key;
    int d_row;
    int d_column;

    int d_attack;
    int d_defense;

    bool d_equipped;
};

inline
std::ostream& operator<<(std::ostream& oss, Item& rhs)
{
    oss << "[[" << rhs.row() << "," << rhs.column() << "]," << (rhs.equipped() ? "true" : "false") << "]";
    return oss;
}

#endif // INCLUDED_ITEM_H
