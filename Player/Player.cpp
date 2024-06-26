//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include "../Utils.h"

using namespace std;
using namespace combat_utils;

Player::Player(const char * name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, true) {
    experience = 75;
    level = 4;
}

Player::Player(const char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer, int _experience, int _level): Character(_name, _health, _attack, _defense, _speed, _isPlayer) {
    experience = _experience;
    level = _level;
}

void Player::Attach(IObserver *observer) {
	enemiesWatching.push_back(observer);
}

void Player::Detach(IObserver *observer) {
	enemiesWatching.erase(std::remove(enemiesWatching.begin(), enemiesWatching.end(), observer), enemiesWatching.end());
}

void Player::Notify(std::string message) {
	vector<IObserver *>::iterator iterator = enemiesWatching.begin();
	for (;iterator != enemiesWatching.end();iterator++) {
		(*iterator)->Update(message);
	}
}

string Player::toString() {
	return "Name: " + string(name) + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed) + "\nLevel: " + to_string(level) + "\nExperience: " + to_string(experience) + "\n";
}

void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    cout << "You have taken " << damage << " damage" << endl;
    if (health <= 0) {
        cout << "You have died" << endl;
    }
}

void Player::emote() {
    cout << "Jokes on you" << endl;
}

void Player::levelUp() {
    level++;
	setMaxHealth(getMaxHealth() + 5);
    setHealth(getHealth() + 5);

	const int awardedPts = 5;
	int ptsToAward = awardedPts, atk = 0, def = 0, spd = 0;
	char opt;
	do{
		cout << "Choose stats to improve (up to " << ptsToAward << " point" << (ptsToAward == 1? "":"s") << " available):\n";
		cout << "1. Attack" << (atk?" (+" + to_string(atk) + ")":"") << "\n";
		cout << "2. Defense" << (def?" (+" + to_string(def) + ")":"") << "\n";
		cout << "3. Speed" << (spd?" (+" + to_string(spd) + ")":"") << "\n";
		cin >> opt;
		switch (opt){
			case '1':
				atk++;
				ptsToAward--;
				break;
			case '2':
				def++;
				ptsToAward--;
				break;
			case '3':
				spd++;
				ptsToAward--;
				break;
			default:
				cout << "Invalid option\n\n";
		}
	} while(ptsToAward);
	setAttack(getAttack() + atk);
	setDefense(getDefense() + def);
	setSpeed(getSpeed() + spd);

	Notify("LVLUP " + to_string(level) + " " + to_string(awardedPts));

	// TODO disable debug info
	cout << toString();
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
		for (int i=0; i < experience/100; i++)
        	levelUp();
        experience %= 100;
    }
}

Character *Player::getTarget(vector<Enemy *> enemies) {
    int targetIndex = 0;
    bool validIndex;
    do{
        cout << "Choose a target" << endl;
        for (int i = 0; i < enemies.size(); i++) {
            cout << i << ". " << enemies[i]->getName() << endl;
        }
    	cin >> targetIndex;
	validIndex = targetIndex >= 0 && targetIndex < enemies.size();
	if (!validIndex)
	    cout<<"Invalid option"<<endl;
    }while(!validIndex);

    return enemies[targetIndex];
}

Action Player::takeAction(vector<Enemy*>enemies) {
    int option = 0;
    Character* target = nullptr;

    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;

    bool validOption;

    do {
	cout<<"Choose an action"<<endl;
	cout<<"1. Attack"<<endl;
	cout<<"2. Flee"<<endl;
	cin >> option;
	validOption = true;
        switch(option) {
            case 1:
                target = getTarget(enemies);
		myAction.target = target;
		myAction.action = [this, target]() {
		    doAttack(target);
		};
                break;
	    case 2:
		myAction.target = this;
		myAction.action = [this, enemies]() {
                    std::vector<Character*> characters (enemies.begin(), enemies.end());
                    flee(characters);
        	};
                break;
            default:
                cout<<"Invalid option"<<endl;
		validOption = false;
                break;
        }
    }while(!validOption);

    return myAction;
}

char* Player::serialize() {
    char* iterator = buffer;

    memcpy(iterator, &name, sizeof name);
    iterator += sizeof name;

    memcpy(iterator, &health, sizeof health);
    iterator += sizeof health;

    memcpy(iterator, &attack, sizeof attack);
    iterator += sizeof attack;

    memcpy(iterator, &defense, sizeof defense);
    iterator += sizeof defense;

    memcpy(iterator, &speed, sizeof speed);
    iterator += sizeof speed;

    memcpy(iterator, &isPlayer, sizeof isPlayer);
    iterator += sizeof isPlayer;

    memcpy(iterator, &experience, sizeof experience);
    iterator += sizeof experience;

    memcpy(iterator, &level, sizeof level);

    return buffer;
}

Player* Player::deserialize(char* _buffer) {
    char* iterator = _buffer;
    char _name[30];
    int _health;
    int _attack;
    int _defense;
    int _speed;
    bool _isPlayer;
    int _experience;
    int _level;

    memcpy(&_name, iterator, sizeof _name);
    iterator += sizeof _name;

    memcpy(&_health, iterator, sizeof _health);
    iterator += sizeof _health;

    memcpy(&_attack, iterator, sizeof _attack);
    iterator += sizeof _attack;

    memcpy(&_defense, iterator, sizeof _defense);
    iterator += sizeof _defense;

    memcpy(&_speed, iterator, sizeof _speed);
    iterator += sizeof _speed;

    memcpy(&_isPlayer, iterator, sizeof _isPlayer);
    iterator += sizeof _isPlayer;

    memcpy(&_experience, iterator, sizeof _experience);
    iterator += sizeof _experience;

    memcpy(&_level, iterator, sizeof _level);

    return new Player(_name, _health, _attack, _defense, _speed, _isPlayer, _experience, _level);
}
