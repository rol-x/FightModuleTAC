#include "stdafx.h"

class Player
{
	int gold, xp, level;

	string name;
	int maxHealth, maxStamina;
	double strength, defense;
	double bonusEffectStrength, bonusEffectDefense;
	double bonusItemStrength, bonusItemDefense, bonusItemHealth, bonusItemStamina, bonusGoldBuff, bonusXPBuff;

	double goldBuff, XPBuff;

	vector<Item> equipment;
	vector<Item> backpack;

	TextColorMap textColor;

	void UpdateLevel();

	void UpdateStrength();

	void UpdateDefense();

	void UpdateEffects();

public:

	int health, stamina;

	Player();

	Player(string _name);

	void UpdateStats(bool init);

	void AddGold(int addedGold);

	void SubtractGold(int subtractedGold);

	int GetGold();

	int GetMaxHealth();

	int GetMaxStamina();

	int GetCurrentLevelXP();

	void GainXP(int gainedXP);

	int GetLevel();

	string GetName();

	int GetStrength();

	int GetDefense();

	void ShowBackpack();

	void SelectFromBackpack(int selection);

	bool AddToBackpack(Item item);

	void ShowEquipment();

	void SelectFromEquipment(int selection);

	bool AddToEquipment(int backpackItemID);

	bool RemoveFromEquipment(int equipmenetItemID);

	bool DropFromBackpack(int backpackItemID);

	bool DropFromEquipment(int equipmentItemID);

	bool IsInInventory(string itemName);

	bool IsInEquipment(string itemName);

	vector<Item> GetEquipment();

	vector<Item> GetBackpack();

	void UseItem(Item item);
};