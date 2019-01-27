#pragma once
#include "color.h"
#include <iostream>
#include <windows.h>
#include <string>

Color::Color()
{
	colorID = 15;
}

Color::Color(int _colorID)
{
	colorID = _colorID;
}

void Color::SetColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorID);
}

void Color::Write(std::string outputString, Color currentColor)
{
	this->SetColor();
	std::cout << outputString;
	currentColor.SetColor();
}
