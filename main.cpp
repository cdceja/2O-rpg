#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"

int main() {

    Player *player = new Player("Victor", 100, 10, 5, 5);
    Enemy *enemy = new Enemy("Recursos Humanos", 50, 5, 2, 3);

    cout<< player->toString()<< endl;
    cout<< enemy->toString()<< endl;

    while(true){
	    player->doAttack(enemy);
	    if(enemy->getHealth() < 0) break;
	    enemy->doAttack(player);
	    if(player->getHealth() < 0) break;
    }

    cout<< player->toString()<< endl;
    cout<< enemy->toString()<< endl;

    delete player;
    delete enemy;
    return 0;
}
