//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Combat/Action.h"
#include "../Observer/IObserver.h"
#include "../Observer/ISubject.h"

struct Action;
class Player;
class IObserver;

class Enemy: public Character, public IObserver {
private:
    int expReward;
	vector<ISubject *> playersWatched;
public:
	void Update(const std::string &) override;
    Enemy(const char *, int, int, int, int, int);
	void adaptToNewPlayerLevel(int);
	void watchPlayer(ISubject*);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* getTarget(vector<Player*> teamMembers);
    Action takeAction(vector<Player*> teamMembers);
    int getExpReward();
    void setExpReward(int);
	string toString() override;
};


#endif //RPG_ENEMY_H
