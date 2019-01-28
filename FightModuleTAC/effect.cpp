#pragma once
#include "effect.h"

Effect::Effect(EffectType _type, double _power)
{
	type = _type;
	power = _power;
	Reset();
}

EffectType Effect::GetType()
{
	return type;
}

double Effect::GetPower()
{
	return power;
}

void Effect::ShowEffect()
{
	switch (type)
	{
	case HealthEffect:
		cout << "Health";
		break;
	case StaminaEffect:
		cout << "Stamina";
		break;
	case StrengthEffect:
		cout << "Strength";
		break;
	case DefenseEffect:
		cout << "Defense";
		break;
	case GoldEffect:
		cout << "Gold";
		break;
	case XPEffect:
		cout << "XP";
		break;
	}
	cout << " buff: " << power;
}

void Effect::Use()
{
	isUsed = true;
}

void Effect::Reset()
{
	isUsed = false;
}

bool Effect::IsUsed()
{
	return isUsed;
}
