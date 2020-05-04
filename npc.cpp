#include "npc.h"

npc::npc(char symbol, string name, function action)
{
    this.symbol = symbol;
    this.name = name;
}

npc::~npc()
{
    //dtor
}
