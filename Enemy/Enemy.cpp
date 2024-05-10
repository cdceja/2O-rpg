//
// Created by Victor Navarro on 13/02/24.
//
#include "Enemy.h"
#include <iostream>
#include <climits>
#include <cstring>
#include <regex>
#include "../Observer/ISubject.h"

using namespace std;

int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(const char * name, int health, int attack, int defense, int speed, int _expReward) : Character(name, health, attack, defense, speed, false) {
	expReward = _expReward;
}

void Enemy::watchPlayer(ISubject * _player){
	playersWatched.push_back(_player);
	_player->Attach(this);
}

void Enemy::Update(const std::string &msg){
	const std::regex re("\\s+");
	vector<string> tokens{ sregex_token_iterator(begin(msg), end(msg), re, -1), sregex_token_iterator() };
	if(tokens[0] == "LVLUP"){
		adaptToNewPlayerLevel(stoi(tokens[2]));
	}
}

void Enemy::adaptToNewPlayerLevel(int pointsToAward){
    setMaxHealth(getMaxHealth() + 5);
    setHealth(getHealth() + 5);
	while(--pointsToAward){
		int chance = rand() % 100;
		if (chance < 34) setAttack(getAttack() + 1);
		if (chance < 67) setDefense(getDefense() + 1);
		else setSpeed(getSpeed() + 1);
	}
	// TODO disable debug info
	cout << toString();
}

int Enemy::getExpReward(){
    return expReward;
}

void Enemy::setExpReward(int _expReward){
	expReward = _expReward;
}

string Enemy::toString() {
    return "Name: " + string(name) + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed) + "\nExpReward: " + to_string(expReward) + "\n";
}

void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Enemy::takeDamage(int damage) {
    setHealth(getHealth() - damage);
    if(getHealth() <= 0) {
        cout<<getName()<<" has died"<<endl;
		for(auto player: playersWatched){
			player->Detach(this);
		}
    }
    else {
        cout<<getName()<<" has taken " << damage << " damage" << endl;
    }
}

Character* Enemy::getTarget(vector<Player *> teamMembers) {
    // Obtiene el miembro del equipo con menos vida
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for(int i=0; i < teamMembers.size(); i++) {
        if(teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}

Action Enemy::takeAction(vector<Player*> teamMembers) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;
    Character* target = nullptr;

    // Am I dying? Shall I run away right now?
    if (getHealth() < 0.15 * getMaxHealth() && rand() % 100 < 5) {
	// Yes, try to flee
        myAction.action = [this, teamMembers](){
    	    vector<Character*> participants (teamMembers.begin(), teamMembers.end());
    	    flee(participants);
        };
    } else {
	// No, attack
        target = getTarget(teamMembers);
	myAction.target = target;
        myAction.action = [this, target](){
            doAttack(target);
        };
    }
    return myAction;
}

