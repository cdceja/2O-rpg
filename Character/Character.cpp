//
// Created by Victor Navarro on 13/02/24.
//
#include "Character.h"
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

bool Character::compareSpeed(Character *a, Character *b){
    return a->getSpeed() > b->getSpeed();
}

bool Character::flee(vector<Character*> participants) {
    std::sort(participants.begin(), participants.end(), Character::compareSpeed);
    Character* fastestCharacter = participants[0];
    fleed = false;
    if(this->getSpeed() > fastestCharacter->getSpeed()) {
        fleed =  true;
    }
    else {
        srand(time(NULL));
        int chance = rand() % 100;
        cout<< "chance: " << chance << endl;
	// TODO Doesn't this mean that they'll always fail to flee?
	// Because chance is 0-99
        fleed = chance > 99;
    }

    return fleed;
}

Character::Character(const char * _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    setName(_name);
    health = _health;
    maxHealth = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
    fleed = false;
}

void Character::setName(const char * _name) {
    strncpy(name, _name, 30);
}

const char * Character::getName() {
    return name;
}

void Character::setHealth(int _health) {
    health = _health;
}

int Character::getHealth() {
    return health;
}

int Character::getMaxHealth() {
    return maxHealth;
}

void Character::setAttack(int _attack) {
    attack = _attack;
}

int Character::getAttack() {
    return attack;
}

void Character::setDefense(int _defense) {
    defense = _defense;
}

int Character::getDefense() {
    return defense;
}

void Character::setSpeed(int _speed) {
    speed = _speed;
}

int Character::getSpeed() {
    return speed;
}

string Character::toString() {
    return "Name: " + string(name) + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::hasFleed() {
    return fleed;
}
