#pragma once
#include "player.h"


void Player::UpdateLevel()					//lvl 1->2: 3xp, lvl 2->3: 6xp, lvl 3->4: 10xp, lvl 4->5: 15xp
{											//xp(lvl) = lvl(lvl+1)/2
	int requiredXP = 1, currentXP = xp;
	int increment = 2;
	level = 0;

	while (currentXP >= requiredXP)
	{
		currentXP -= requiredXP;
		level++;

		requiredXP+=increment;
		increment++;
	}
}

void Player::UpdateStrength()
{
	strength = 2 + 3 * level;
	for (Item &item : equipment)
	{
		if (!item.IsActive())
			continue;
		if (item.GetType() == WeaponItem)
		{
			strength += item.GetPower();
		}
	}
	strength += bonusEffectStrength;
}

void Player::UpdateDefense()
{
	defense = 2 * level;
	for (Item &item : equipment)
	{
		if (!item.IsActive())
			continue;
		if (item.GetType() == ArmorItem)
		{
			defense += item.GetPower();
		}
	}
	defense += bonusEffectDefense;
}

void Player::UpdateEffects()
{
	bonusItemDefense = 0;
	bonusItemHealth = 0;
	bonusItemStamina = 0;
	bonusItemStrength = 0;
	bonusXPBuff = 1;
	bonusGoldBuff = 1;

	for (Item &item : equipment)
	{
		if (!item.IsActive())
			continue;
		if (!item.NoEffects())
		{
			if (item.GetType() == ConsumableItem)
				continue; 
			for (Effect &effect : item.GetEffects())
			{
				switch (effect.GetType())
				{
				case HealthEffect:
					bonusItemHealth += effect.GetPower();
					break;
				case StaminaEffect:
					bonusItemStamina += effect.GetPower();
					break;
				case StrengthEffect:
					bonusItemStrength += effect.GetPower();
					break;
				case DefenseEffect:
					bonusItemDefense += effect.GetPower();
					break;
				case GoldEffect:
					bonusGoldBuff *= effect.GetPower();
					break;
				case XPEffect:
					bonusXPBuff *= effect.GetPower();
					break;
				default:
					break;
				}
			}
		}
	}

	health += bonusItemHealth;
	stamina += bonusItemStamina;
	strength += bonusItemStrength;
	defense += bonusItemDefense;
	goldBuff *= bonusGoldBuff;
	XPBuff *= bonusXPBuff;
}

void Player::UpdateStats(bool init)
{
	maxHealth = 30 + level * 5;
	maxStamina = 20 + level * 5;
	
	if (init)
	{
		bonusEffectDefense = 0;
		bonusEffectStrength = 0;
		goldBuff = 1.0;
		XPBuff = 1.0;
		health = maxHealth;
		stamina = maxStamina;
	}

	UpdateLevel();
	UpdateStrength();
	UpdateDefense();
	UpdateEffects();
}

Player::Player() = default;

Player::Player(string _name)
{
	name = _name;
	gold = 0;
	xp = 1;
	UpdateStats(true);
}

void Player::AddGold(int addedGold)
{
	gold += addedGold;
}

void Player::SubtractGold(int subtractedGold)
{
	gold = max(0, gold - subtractedGold);
}

int Player::GetMaxHealth()
{
	return maxHealth;
}

int Player::GetMaxStamina()
{
	return maxStamina;
}

int Player::GetGold()
{
	return gold;
}

int Player::GetCurrentLevelXP()
{
	int requiredXP = 5, currentXP = xp;

	while (currentXP >= requiredXP)
	{
		currentXP -= requiredXP;
		requiredXP++;
	}
	return currentXP;
}

void Player::GainXP(int gainedXP)
{
	xp += gainedXP;
	UpdateLevel();
}

int Player::GetLevel()
{
	return level;
}

string Player::GetName()
{
	return name;
}

int Player::GetStrength()
{
	return strength;
}

int Player::GetDefense()
{
	return defense;
}

void Player::ShowBackpack()
{
	textColor.SetColor("backpack");
	cout << "[BACKPACK]" << endl;
	if (backpack.size() == 0)
		cout << "Backpack empty!" << endl << endl;
	int index = 1;
	for (Item item : backpack)
	{
		cout << index << ". ";
		item.ShowItem();
		index++;
	}
	cout << endl;
}

void Player::SelectFromBackpack(int selection)
{
	textColor.SetColor("backpack");
	cout << "[BACKPACK]" << endl;
	if (backpack.size() == 0)
		cout << "Backpack empty!" << endl << endl;
	int index = 1;
	for (Item item : backpack)
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

bool Player::AddToBackpack(Item item)
{
	if (backpack.size() < 10)
	{
		backpack.push_back(item);
		return true;
	}
	else
		return false;
}

void Player::ShowEquipment()
{
	textColor.SetColor("equipment");
	cout << "[EQUIPMENT]" << endl;
	if (equipment.size() == 0)
		cout << "Equipment empty!" << endl << endl;
	int index = 1;
	for (Item item : equipment)
	{
		cout << index << ". ";
		item.ShowItem();
		index++;
	}
	cout << endl;
}

void Player::SelectFromEquipment(int selection)
{
	textColor.SetColor("equipment");
	cout << "[EQUIPMENT]" << endl;
	if (equipment.size() == 0)
		cout << "Equipment empty!" << endl << endl;
	int index = 1;
	for (Item item : equipment)
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

bool Player::AddToEquipment(int backpackItemID)
{
	if (backpack.size() == 0)
		return false;
	if (equipment.size() < 6)
	{
		equipment.push_back(backpack[backpackItemID]);
		backpack.erase(backpack.begin() + backpackItemID);
		equipment[equipment.size() - 1].Equip();
		return true;
	}
	else
		return false;
}

bool Player::RemoveFromEquipment(int equipmenetItemID)
{
	if (equipment.size() == 0)
		return false;
	if (backpack.size() < 10)
	{
		backpack.push_back(equipment[equipmenetItemID]);
		equipment.erase(equipment.begin() + equipmenetItemID);
		backpack[backpack.size() - 1].Unequip();
		return true;
	}
	else
		return false;
}

bool Player::DropFromBackpack(int backpackItemID)
{
	if (backpackItemID >= backpack.size())
		return false;
	if (backpackItemID == 0 && backpack.size() == 1)
		backpack.pop_back();
	else
		backpack.erase(backpack.begin() + backpackItemID);
	return true;
}

bool Player::DropFromEquipment(int equipmentItemID)
{
	if (equipmentItemID >= equipment.size())
		return false;
	equipment.erase(equipment.begin() + equipmentItemID);
	return true;
}

bool Player::IsInInventory(string itemName)
{
	for (Item item : equipment)
	{
		if (item.GetName() == itemName)
			return true;
	}
	for (Item item : backpack)
	{
		if (item.GetName() == itemName)
			return true;
	}
	return false;
}

bool Player::IsInEquipment(string itemName)
{
	for (Item item : equipment)
	{
		if (item.GetName() == itemName)
			return true;
	}
	return false;
}

vector<Item> Player::GetEquipment()
{
	return equipment;
}

vector<Item> Player::GetBackpack()
{
	return backpack;
}

void Player::UseItem(Item item)
{
	if (item.GetType() == ConsumableItem)
	{
		for (Effect effect : item.GetEffects())
		{
			switch (effect.GetType())
			{
			case HealthEffect:
				health = min(maxHealth, health + effect.GetPower());
				break;
			case StaminaEffect:
				stamina = min(maxStamina, stamina + effect.GetPower());
				break;
			case DefenseEffect:
				bonusEffectDefense += effect.GetPower();
				break;
			case StrengthEffect:
				bonusEffectStrength += effect.GetPower();
				break;
			case GoldEffect:
				goldBuff *= effect.GetPower();
				break;
			case XPEffect:
				XPBuff *= effect.GetPower();
				break;
			}
		}
	}
}