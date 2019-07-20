#include "knight.h"
#include "config.h"

Knight::Knight(char colour, int row, int column)
    : d_colour(colour)
    , d_row(row)
    , d_column(column)
    , d_attack(1)
    , d_defense(1)
    , d_status(KnightStatus::LIVE)
    , d_item(0)
{
}

const char& Knight::colour() const
{
    return d_colour;
}

const int& Knight::row() const
{
    return d_row;
}

const int& Knight::column() const
{
    return d_column;
}

int& Knight::attack()
{
    return d_attack;
}

int& Knight::defense()
{
    return d_defense;
}

double Knight::totalAttack()
{
    double total = d_attack + Config::SURPRISE_ADVANTAGE;
    if (hasItem()) {
        total += item().attack();
    }
    return total;
}

double Knight::totalDefense()
{
    double total = d_defense;
    if (hasItem()) {
        total += item().defense();
    }
    return total;
}

void Knight::setPosition(int row, int column)
{
    d_row = row;
    d_column = column;
    if (hasItem()) {
        d_item->row() = row;
        d_item->column() = column;
    }
}

void Knight::equipItem(Item& item)
{
    item.equipped() = true;
    d_item = &item;
}

void Knight::dropItem()
{
    if (hasItem()) {
        d_item->equipped() = false;
    }
    d_item = 0;
}

bool Knight::hasItem()
{
    return (d_item != 0);
}

Item& Knight::item()
{
    return *d_item;
}

KnightStatus::Value Knight::status() const
{
    return d_status;
}

void Knight::drown()
{
    dropItem();
    d_attack = 0;
    d_defense = 0;
    d_status = KnightStatus::DROWNED;
}

void Knight::die()
{
    dropItem();
    d_attack = 0;
    d_defense = 0;
    d_status = KnightStatus::DEAD;
}

void Knight::fight(Knight& opponent)
{
    double myAttack = totalAttack();
    double opponentDefense = opponent.totalDefense();

    if (myAttack > opponentDefense) {
        opponent.die();
    } else if (myAttack < opponentDefense) {
        die();
    } else {
        throw std::runtime_error("Oh no! A tie!");
    }
}
