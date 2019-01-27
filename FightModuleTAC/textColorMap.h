#pragma once
#include <map>
#include <string>
#include <iostream>
#include "color.h"

using namespace std;

class TextColorMap
{
	map<string, Color> textColor;

public:

	TextColorMap();

	void SetColor(string colorKey);

	void Write(string message, string textColorKey, string currentColorKey);
};