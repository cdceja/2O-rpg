//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include<string>
#include "../Combat/Action.h"

using namespace std;

class Character {
protected:
    char name[30];
    int health;
    int maxHealth;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    bool fleed;

public:
    Character(const char *, int, int, int, int, bool);

    static bool compareSpeed(Character *a, Character *b);
    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;
    bool flee(vector<Character*> participants);

    void setName(const char *);
    const char * getName();
    void setHealth(int);
    int getHealth();
    void setMaxHealth(int);
    int getMaxHealth();
    void setAttack(int);
    int getAttack();
    void setDefense(int);
    int getDefense();
    void setSpeed(int);
    int getSpeed();
    virtual string toString();
    bool getIsPlayer();
    bool hasFleed();
};


#endif //RPG_CHARACTER_H
