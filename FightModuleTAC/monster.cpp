#pragma once
#include "monster.h"


Monster::Monster() = default;

Monster::Monster(string _name, int _level)
{
	name = _name;
	if (_level)
		level = _level;
	else
		level = 1;
	maxHealth = rand() % (level * 6 + 1) + (level * 6);		//1: 6-12	2: 12-24	3: 18-36	4: 24-48	5: 30-60	6: 36-72
	maxStamina = rand() % (level * 4 + 1) + (level * 4);	//1: 4-8	2: 8-16     3: 12-24	4: 16-32	5: 20-40	6: 24-48
	strength = rand() % (level * 2 + 1) + (level * 2);		//1: 2-4	2: 4-8		3: 6-12		4: 8-16		5: 10-20	6: 12-24
	defense = rand() % (level * 2 + 1) + (level);			//1: 1-3	2: 2-6		3: 3-9		4: 4-12		5: 5-15		6: 6-18 
	health = maxHealth;
	stamina = maxStamina;

	goldReward = (int)((double)((double)(maxHealth) * 0.2) + (double)((double)(maxStamina) * 0.3) + (double)((double)(defense) * 0.4) + strength + level);
	XPReward = level;
	if (!(rand() % 10))
		XPReward *= 2;
}

int Monster::GetMaxHealth()
{
	return maxHealth;
}

int Monster::GetMaxStamina()
{
	return maxStamina;
}

int Monster::GetDefense()
{
	return defense;
}

int Monster::GetStrength()
{
	return strength;
}

string Monster::GetName()
{
	return name;
}

void Monster::OverrideLevel(int newLevel)
{
	level = newLevel;
}

bool Monster::IsDead()
{
	return health <= 0 ? true : false;
}

int Monster::GetXP()
{
	return XPReward;
}

int Monster::GetGold()
{
	return goldReward;
}

vector<Item> Monster::GetLoot()
{
	return items;
}

void Monster::ShowLoot()
{
	textColor.SetColor("consumable");
	cout << "[LOOT]" << endl;
	if (items.size() == 0)
		cout << "Loot empty!" << endl << endl;
	int index = 1;
	for (Item item : items)
	{
		cout << index << ". ";
		item.ShowItem();
		index++;
	}
	cout << endl;
}

void Monster::DropItem(int itemID)
{
	items.erase(items.begin() + itemID);
}

void Monster::StoreItem(Item item)
{
	items.push_back(item);
}

void Monster::SelectFromLoot(int selection)
{
	textColor.SetColor("consumable");
	cout << "[LOOT]" << endl;
	if (items.size() == 0)
		cout << "Backpack empty!" << endl << endl;
	int index = 1;
	for (Item item : items)
	{
		if (selection + 1 == index)
			cout << "> ";
		cout << index << ". ";
		item.ShowItem();
		index++;
	}
	cout << endl;
	textColor.SetColor("neutral");
}

