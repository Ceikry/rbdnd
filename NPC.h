#ifndef NPC_H
#define NPC_H

#include <Entity.h>


class NPC : public Entity
{
    public:
        NPC();
        bool canWander,friendly;
        int aggroRadius;
        float health,damage;

    protected:

    private:
};

#endif // NPC_H
