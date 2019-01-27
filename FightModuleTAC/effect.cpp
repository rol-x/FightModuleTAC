#pragma once
#include "effect.h"

Effect::Effect(EffectType _type, double _power)
{
	type = _type;
	power = _power;
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