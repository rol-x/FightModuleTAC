#pragma once
#include "epicWriter.h"

void out(char output)
{
	cout << output;
}

void EpicWriter::Write(string outputText)
{
	Sleep(64);
	bool write = true;
	int i = 0;
	for (auto letter : outputText)
	{
		if (_kbhit())
		{
			_getch();
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			write = false;
		}
		if (write)
		{
			cout << letter;
			i++;
			Sleep(32);
		}
	}
	cout << outputText.substr(i, outputText.length());
	Sleep(64);
}
