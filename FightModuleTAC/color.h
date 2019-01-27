#pragma once
#include <string>

class Color
{
	int colorID;

public:
	Color();

	Color(int _colorID);

	void SetColor();

	void Write(std::string outputString, Color currentColor);
};