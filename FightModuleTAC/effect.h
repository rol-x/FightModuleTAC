#pragma once
#include <iostream>

using namespace std;

enum EffectType
{
	HealthEffect,
	StaminaEffect,
	StrengthEffect,
	DefenseEffect,
	GoldEffect,
	XPEffect
};

class Effect
{
	EffectType type;
	double power;

	bool isUsed;

public:

	Effect(EffectType _type, double _power);

	EffectType GetType();

	double GetPower();

	void ShowEffect();

	void Reset();

	void Use();

	bool IsUsed();
};