#include "item.h"

Item::Item(char key, int row, int column, int attack, int defense)
    : d_key(key)
    , d_row(row)
    , d_column(column)
    , d_attack(attack)
    , d_defense(defense)
    , d_equipped(false)
{
}

const char& Item::key() const
{
    return d_key;
}

int& Item::row()
{
    return d_row;
}

int& Item::column()
{
    return d_column;
}

int& Item::attack()
{
    return d_attack;
}

int& Item::defense()
{
    return d_defense;
}

bool& Item::equipped()
{
    return d_equipped;
}
