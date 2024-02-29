//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include<string>
#include<vector>

using namespace std;

class Character {
protected:
    string name;
    int health;
    int maxHealth;
    int attack;
    int defense;
    int speed;
    bool isPlayer;

public:
    Character(string, int, int, int, int, bool);

    static bool compareSpeed(Character *a, Character *b);
    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;
    bool flee(vector<Character*> participants);

    void setName(string);
    string getName();
    void setHealth(int);
    int getHealth();
    int getMaxHealth();
    void setAttack(int);
    int getAttack();
    void setDefense(int);
    int getDefense();
    void setSpeed(int);
    int getSpeed();
    string toString();
    bool getIsPlayer();
};


#endif //RPG_CHARACTER_H
