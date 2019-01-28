#pragma once
#include "item.h"


Item::Item(ItemType _type, string _name, int _value, int _power, int _staminaDrain)
{
	type = _type;
	name = _name;
	value = _value;
	power = _power;
	staminaDrain = _staminaDrain;
}

Item::Item(ItemType _type, string _name, int _value, int _power, int _staminaDrain, vector<Effect> _effects)
{
	type = _type;
	name = _name;
	value = _value;
	power = _power;
	staminaDrain = _staminaDrain;
	effects = _effects;
}

ItemType Item::GetType()
{
	return type;
}

string Item::GetName()
{
	return name;
}

int Item::GetValue()
{
	return value;
}

int Item::GetPower()
{
	return power;
}

void Item::AddEffect(Effect effect)
{
	effects.push_back(effect);
}

vector<Effect> Item::GetEffects()
{
	return effects;
}

bool Item::NoEffects()
{
	return (effects.empty() == true) ? true : false;
}

bool Item::IsActive()
{
	return isActive;
}

void Item::Equip()
{
	isActive = true;
	for (Effect & effect : effects)
		effect.Reset();
}

void Item::Unequip()
{
	isActive = false;
}

void Item::ShowItem()
{
	cout << name << " ";
	switch (type)
	{
	case WeaponItem:
		cout << "[Weapon]";
		break;
	case ArmorItem:
		cout << "[Armor]";
		break;
	case QuestItem:
		cout << "[Quest item]";
		break;
	case ConsumableItem:
		cout << "[Consumable]";
		break;
	}
	cout << " (Power: " << power << ") ";
	ShowEffects();
	cout << endl;
}

void Item::ShowEffects()
{
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i].ShowEffect();
		if (i != effects.size() - 1)
			cout << ", ";
	}
}
