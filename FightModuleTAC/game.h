#include "stdafx.h"
#include "monster.h"
#include "player.h"

class Game
{
public:
	Player player;
	TextColorMap textColor;
	EpicWriter writer;
	bool alive;

	Game();

	void PlayerDead();

	void ShowHelp();

	void ShowPlayerStats(Player & player);

	void ShowMonsterStats(Monster & monster);

	void ShowInventoryMenu(Player & player);

	void Attack(Player & player, Monster & monster, bool isPlayerAttacking);

	void LootMonster(Monster & monster, Player & player);

	void Fight(Monster & monster);
};
