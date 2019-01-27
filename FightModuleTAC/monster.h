#pragma once
#include "stdafx.h"

class Monster
{

	string name;
	int maxHealth, maxStamina;
	double strength, defense;
	int level;

	int goldReward, XPReward;

	vector<Item> items;

	TextColorMap textColor;

public:

	int health, stamina;

	Monster();

	Monster(string _name, int _level);

	int GetMaxHealth();

	int GetMaxStamina();

	int GetDefense();

	int GetStrength();

	string GetName();

	void OverrideLevel(int newLevel);

	bool IsDead();

	int GetXP();

	int GetGold();

	vector<Item> GetLoot();

	void ShowLoot();

	void DropItem(int itemID);

	void StoreItem(Item item);

	void SelectFromLoot(int selection);

};

