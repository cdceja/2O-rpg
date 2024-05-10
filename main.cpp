#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"
#include <queue>

using namespace std;

int main() {
    Player *player = new Player("Victor", 30, 100, 2, 10);
    Enemy *enemy = new Enemy("Goblin", 20, 5, 3, 7, 35);
	Enemy *enemy2 = new Enemy("Orc", 30, 4, 2, 2, 25);

    vector<Character*> participants;
    participants.push_back(player);
	enemy->watchPlayer(player);
	enemy2->watchPlayer(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat* combat = new Combat(participants);
    combat->doCombat();

//    char* buffer = player->serialize();
//
//    Player* ooootroPlayer = Player::deserialize(buffer);
//
//    delete player;
//    delete enemy;
//    delete enemy2;
//    delete combat;

    return 0;
}
