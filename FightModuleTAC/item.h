#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "effect.h"

using namespace std;

enum ItemType
{
	ConsumableItem,
	ArmorItem,
	WeaponItem,
	QuestItem
};


class Item
{
	ItemType type;
	string name;
	int value, power;
	vector<Effect> effects;
	bool isActive;
	int staminaDrain;

public:

	Item(ItemType _type, string _name, int _value, int _power, int _staminaDrain);

	Item(ItemType _type, string _name, int _value, int _power, int _staminaDrain, vector<Effect> _effects);

	ItemType GetType();

	string GetName();

	int GetValue();

	int GetPower();

	void AddEffect(Effect effect);

	vector<Effect> GetEffects();

	bool NoEffects();

	bool IsActive();

	void Equip();

	void Unequip();

	void ShowItem();

	void ShowEffects();

};
