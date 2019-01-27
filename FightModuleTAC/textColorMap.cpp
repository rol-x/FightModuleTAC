#pragma once
#include "textColorMap.h"

TextColorMap::TextColorMap()
{
	static Color consumableText(2);				// green
	static Color dangerText(12);				// bright red
	static Color fightText(11);					// bright blue
	static Color questText(6);					// golden
	static Color subText(8);					// grey
	static Color equipmentText(9);				// blue
	static Color infoText(13);					// bright pink
	static Color backpackText(14);				// yellow
	static Color neutralText(15);				// white

	textColor.insert({ "consumable", consumableText });
	textColor.insert({ "danger", dangerText });
	textColor.insert({ "fight", fightText });
	textColor.insert({ "quest", questText });
	textColor.insert({ "sub", subText });
	textColor.insert({ "equipment", equipmentText });
	textColor.insert({ "info", infoText });
	textColor.insert({ "backpack", backpackText });
	textColor.insert({ "neutral", neutralText });
}


void TextColorMap::SetColor(string colorKey)
{
	textColor[colorKey].SetColor();
}

void TextColorMap::Write(string message, string textColorKey, string currentColorKey)
{
	textColor[textColorKey].Write(message, textColor[currentColorKey]);
}