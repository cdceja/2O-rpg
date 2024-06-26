//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include "../Observer/ISubject.h"
#include <list>

struct Action;
class Enemy;
class ISubject;

class Player: public Character, public ISubject {
protected:
    int experience;
    int level;

public:
    Player(const char* _name, int _health, int _attack, int _defense, int _speed);
    Player(const char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer, int _experience, int _level);

	void Attach(IObserver*) override;
	void Detach(IObserver*) override;
	void Notify(std::string) override;

	string toString() override;
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    char* serialize();
    static const unsigned int BUFFER_SIZE = sizeof (name) + sizeof(health) + sizeof(attack) + sizeof(defense) + sizeof(speed) + sizeof(isPlayer) + sizeof(level) + sizeof(experience);

    static Player* deserialize(char* buffer);

    Character* getTarget(vector<Enemy*> enemies);

    void emote();
    void levelUp();
    void gainExperience(int);

    //Podemos hacer que este vector sea polimorfico?
    Action takeAction(vector<Enemy*> enemies);

private:
    char buffer[Player::BUFFER_SIZE];
	vector<IObserver *> enemiesWatching;
};


#endif //RPG_PLAYER_H
