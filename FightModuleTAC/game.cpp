#pragma once
#include "game.h"

void cls()					//ready-made function from stackoverflow in replacement of system("cls")
{
	// Get the Win32 handle representing standard output.
	// This generally only has to be done once, so we make it static.
	static const HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	// std::cout uses a buffer to batch writes to the underlying console.
	// We need to flush that to the console because we're circumventing
	// std::cout entirely; after we clear the console, we don't want
	// stale buffered text to randomly be written out.
	std::cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(handleOut, &csbi)) {
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(handleOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(handleOut, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(handleOut, topLeft);
}

void moveCursor(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void ReverseString(string &text)
{
	string outputString = "";
	for (int i = text.length() - 1; i >= 0; i--)
		outputString += text.at(i);
	text = outputString;
}

string ToString(int number)
{
	bool isNegative = false;
	string outputString = "";
	if (number == 0)
		outputString = "0";
	else if (number < 0)
	{
		isNegative = true;
		number *= -1;
	}
	while (number != 0)
	{
		outputString += (char)(number % 10 + 48);
		number /= 10;
	}
	if (isNegative)
	{
		outputString += "-";
	}
	ReverseString(outputString);
	return outputString;
}


	Game::Game()
	{
		player =  Player("Macrofaculty student");
		player.UpdateStats(true);
		alive = true;
	}

	void Game::PlayerDead()
	{
		bool loop = false;

		cls();
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t    Y  O  U     D  I  E  D " << endl;
		alive = false;
		do
		{
			char c = _getch();
			switch (c)
			{
				case (char)(27) :
					exit(0);
					break;
				default:
					loop = true;
			}
		} while (loop);
	}

	void Game::ShowHelp()
	{
		cls();
		textColor.Write("The Amulets of Camembert - Fight Module\n\nItems\n", "info", "neutral");
		cout << "Each item belongs to one of three categories: Armor, Weapon or Consumable. Weapon items boost your strength, armor corresponds to defense ";
		cout << "while consumables are one-time-use items to grant\nyou some recovery effects (healing) or permanent boosts. Items can be found in the remains of ";
		cout << "defeated monsters and can be stored either in Backpack (10 slots) or Equipment (6 slots).\nWhile one can posses many copies of the same item in Backpack, ";
		cout << "only one can be Equipped, whichmeans its effects will be granted to the Player.\n\n";
		textColor.Write("The Encounter\n", "info", "neutral");
		cout << "Player can meet different foes on his way, each with stats and belongings randomized\naccordingly to its level. Out of three options, the Player can Attack, ";
		cout << "exchanging hits with\nhis enemy (the Player goes first); manipulate their Inventory (at the cost of a lost turn) andtry to Run away, with probability tending to ";
		cout << "50% as the monster is more damaged.\n\n";
		textColor.Write("Effects", "info", "neutral");
		cout << "\nSome items are enchated with spells empowering their effects on the Player. Those Effects can be corelated to: Health, Strength, Defense, Gold and XP. Work with ";
		cout << "the best possible\ncombination of items in you Equipment to make it as far as possible in this satire-ridden\njourney through academic life.";
		cout << endl << endl;
		textColor.SetColor("sub");
		system("pause"); 
	}

	void Game::ShowPlayerStats(Player & player)
	{
		textColor.SetColor("info");
		cout << player.GetName() << "\t\tHealth: " << player.health << "/" << player.GetMaxHealth() << " \tStrength: " << player.GetStrength() << "\tDefense: " << player.GetDefense() << " (" << static_cast<int>(2000*sqrtf((float)(player.GetDefense()))/3 - 500)/100.0 << "% reduction)" << endl;
		textColor.SetColor("sub");
		cout << "Level: " << player.GetLevel() << "\tXP: " << player.GetCurrentLevelXP() << " (" << player.GetLevel()*(player.GetLevel()+1)/2 << ")\tGold: " << player.GetGold() << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl << endl;
	}

	void Game::ShowMonsterStats(Monster & monster)
	{
		textColor.SetColor("danger");
		cout << monster.GetName() << endl;
		textColor.SetColor("neutral");
		cout << "Health: " << monster.health << "\tStrength: " << monster.GetStrength() << "\tDefense:" << monster.GetDefense() << endl << endl;
		textColor.SetColor("fight");
	}

	void Game::ShowInventoryMenu(Player & player)
	{
		int selection = 0;
		bool show = true;
		char keyCode = ' ';
		while (show)
		{
			cls();
			ShowPlayerStats(player);

			switch (keyCode)
			{
			case 72:			//UP
				if (selection > 0)
					selection--;
				break;
			case 80:			//DOWN
				if (selection < player.GetBackpack().size() + player.GetEquipment().size() - 1)
					selection++;
				break;
			case 'E':
			case 'e':
				if (selection >= 0 && selection < player.GetBackpack().size())
				{
					player.UseItem(player.GetBackpack()[selection]);
					if(player.GetBackpack()[selection].GetType() == ConsumableItem)
						player.DropFromBackpack(selection);
				}
				else if (selection >= player.GetBackpack().size() && selection < (player.GetBackpack().size() + player.GetEquipment().size()))
				{
					player.UseItem(player.GetEquipment()[selection - player.GetBackpack().size()]);
					if (player.GetEquipment()[selection - player.GetBackpack().size()].GetType() == ConsumableItem)
						player.DropFromEquipment(selection - player.GetBackpack().size());
				}
				break;
			case 'R':
			case 'r':
				if (selection >= 0 && selection < player.GetBackpack().size())
				{
					if (!(player.IsInEquipment(player.GetBackpack()[selection].GetName())))
					player.AddToEquipment(selection);
				}
				else if (selection >= player.GetBackpack().size() && selection < (player.GetBackpack().size() + player.GetEquipment().size()))
					player.RemoveFromEquipment(selection - player.GetBackpack().size());
				break;
			case 'D':
			case 'd':
				if (selection >= 0 && selection < player.GetBackpack().size())
					player.DropFromBackpack(selection);
				else if (selection >= player.GetBackpack().size() && selection < (player.GetBackpack().size() + player.GetEquipment().size()))
					player.DropFromEquipment(selection - player.GetBackpack().size());
				break;
			case 27:
				show = false;
				break;
			default:
				break;
			}

			if (selection >= 0 && selection < player.GetBackpack().size())
			{
				if (player.IsInEquipment(player.GetBackpack()[selection].GetName()))
					cout << "\033[F" << "Item already in Equipment!" << endl;
			}

			if (show)
			{
				player.UpdateStats(false);
				if (selection < player.GetBackpack().size())
				{
					player.SelectFromBackpack(selection);
					player.ShowEquipment();
				}
				else if (selection >= player.GetBackpack().size())
				{
					player.ShowBackpack();
					player.SelectFromEquipment(selection - player.GetBackpack().size());
				}
				textColor.SetColor("neutral");
				cout << "\n[E] Use    [R] Equip / Unequip    [D] Drop    [ESC] Go back\n";
			}

			keyCode = _getch();
		}
	}

	void Game::Attack(Player & player, Monster & monster, bool isPlayerAttacking)
	{
		if (isPlayerAttacking)
		{
			double armorRatio = (1.05 - sqrtf((float)(monster.GetDefense())) / 15.0);	//calculating what % of damage will be taken due to armor
			int damage = player.GetStrength() * max(armorRatio, 0.3);					//maximal value of 70% of damage can be blocked by armor
			damage = max(1, rand() % (2 * damage / 5 + 1) + 7 * damage / 10);			//each hit is about 70%-110% of potential hit, and never less than 1
			writer.Write(player.GetName() + " attacked " + monster.GetName() + " for " + ToString(damage) + " dmg!\n");
			monster.health -= damage;
		}
		else if(monster.health >= 0)
		{
			double armorRatio = (1.05 - sqrtf((float)(player.GetDefense())) / 15.0);
			int damage = monster.GetStrength() * max(armorRatio, 0.3);
			damage = max(1, (rand() % (2 * damage / 5 + 1)) + 3 * damage / 5);			//monster's hit ranges from 60% to 100%
			writer.Write(monster.GetName() + " attacked " + player.GetName() + " for " + ToString(damage) + " dmg!\n");
			cout << endl;
			player.health -= damage;
		}
	}

	void Game::LootMonster(Monster & monster, Player & player)
	{
		int selection = 0;
		bool show = true;
		char keyCode = ' ';
		while (show)
		{
			cls();
			ShowPlayerStats(player);
			switch (keyCode)
			{
			case 72:			//UP
				if (selection > 0)
					selection--;
				break;
			case 80:			//DOWN
				if (selection < player.GetBackpack().size() + monster.GetLoot().size() - 1)
					selection++;
				break;
			case 'E':
			case 'e':
				if (selection >= 0 && selection < monster.GetLoot().size())
				{
					player.UseItem(monster.GetLoot()[selection]);
					if (monster.GetLoot()[selection].GetType() == ConsumableItem)
						monster.DropItem(selection);
				}
				else if (selection >= monster.GetLoot().size() && selection < (monster.GetLoot().size() + player.GetBackpack().size()))
				{
					player.UseItem(player.GetBackpack()[selection - monster.GetLoot().size()]);
					if (player.GetBackpack()[selection - monster.GetLoot().size()].GetType() == ConsumableItem)
						player.DropFromBackpack(selection - monster.GetLoot().size());
				}
				break;
			case 'R':
			case 'r':
				if (selection >= 0 && selection < monster.GetLoot().size())
				{
					player.AddToBackpack(monster.GetLoot()[selection]);
					monster.DropItem(selection);
				}
				else if (selection >= monster.GetLoot().size() && selection < (monster.GetLoot().size() + player.GetBackpack().size()))
				{
					Item storedItem = player.GetBackpack()[selection - monster.GetLoot().size()];
					player.DropFromBackpack(selection - monster.GetLoot().size());
					monster.StoreItem(storedItem);
				}
				break;
			case 'D':
			case 'd':
				if (selection >= monster.GetLoot().size() && selection < (monster.GetLoot().size() + player.GetBackpack().size()))
					player.DropFromBackpack(selection - monster.GetLoot().size());
				break;
			case 27:
				show = false;
				break;
			default:
				break;
			}


			if (show)
			{
				player.UpdateStats(false);
				if (selection < monster.GetLoot().size())
				{
					monster.SelectFromLoot(selection);
					player.ShowBackpack();
				}
				else if (selection >= monster.GetLoot().size())
				{
					monster.ShowLoot();
					player.SelectFromBackpack(selection - monster.GetLoot().size());
				}
				textColor.SetColor("neutral");
				cout << "\n[E] Use    [R] Loot / Store    [D] Drop    [ESC] Go back\n";
			}

			keyCode = _getch();
		}
	}

	void Game::Fight(Monster & monster)
	{
		ShowPlayerStats(player);
		textColor.SetColor("fight");
		bool fight = true;
		bool firstScreen = true;
		bool doPause = true;
		double runTry;
		char choice;
		writer.Write("You encountered " + monster.GetName() + "!");
		moveCursor(84, 4);
		textColor.Write("[H] Help", "sub", "fight");
		writer.Write("\nIt looks like it has " + ToString(monster.GetMaxHealth()) + " health and " + ToString(monster.GetStrength()) + " strength!\n\n");
		do
		{
			doPause = true;
			if (!firstScreen)
			{
				ShowPlayerStats(player);
				textColor.SetColor("fight");
				cout << "You encountered " << monster.GetName() << "!";
				moveCursor(84, 4);
				textColor.Write("[H] Help", "sub", "fight");
				cout << "\nIt looks like it has " + ToString(monster.GetMaxHealth()) + " health and " + ToString(monster.GetStrength()) + " strength!\n\n";
			}
			ShowMonsterStats(monster);
			textColor.SetColor("neutral");
			cout << "\n\t\t[A] Attack!\n\t\t[I] Inventory\n\t\t[R] Run (" << (int)(50.0*double(monster.GetMaxHealth() - monster.health) / double(monster.GetMaxHealth())) << "% chance)\n";
			//run probability is equal to damage done to monster in % over 2
			//if monster is left with 3HP from 12HP it's 9/12 * 50% = 37.5%
			textColor.SetColor("fight");
			choice = _getch();
			switch (choice)
			{
			case 'A':
			case 'a':
				cout << endl;
				Attack(player, monster, true);
				Attack(player, monster, false);
				break;
			case 'I':
			case 'i':
				ShowInventoryMenu(player);
				textColor.SetColor("fight");
				cout << "You encountered " << monster.GetName() << "!";
				moveCursor(84, 4);
				textColor.Write("[H] Help", "sub", "fight");
				cout << "\nIt looks like it has " + ToString(monster.GetMaxHealth()) + " health and " + ToString(monster.GetStrength()) + " strength!\n\n";
				ShowMonsterStats(monster);
				textColor.SetColor("neutral");
				cout << "\n\t\t[A] Attack!\n\t\t[I] Inventory\n\t\t[R] Run (" << (int)(50.0*double(monster.GetMaxHealth() - monster.health) / double(monster.GetMaxHealth())) << "% chance)\n";
				textColor.SetColor("fight");
				cout << endl;
				Attack(player, monster, false);
				if (player.health <= 0)
					fight = false;
				break;
			case 'R':
			case 'r':
				runTry = (rand() % 10000) / 100;		//70 -> 0-70, 70-100
				if (runTry < 50.0*double(monster.GetMaxHealth() - monster.health) / double(monster.GetMaxHealth()))
				{
					_getch();
					cout << endl;
					writer.Write("Escape successful!\n");
					fight = false;
				}
				else
				{
					_getch();
					cout << endl;
					writer.Write("Escape unsuccessful!\n");
					Attack(player, monster, false);
				}
				break;
			case 'H':
			case 'h':
				ShowHelp();
				doPause = false;
				break;
			default:
				_getch();
				doPause = false;
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			}

			if (player.health <= 0 || monster.health <= 0)
			{
				doPause = false;
				fight = false;
				if (player.health <= 0)
				{
					textColor.SetColor("danger");
					writer.Write(player.GetName() + "'s HP is " + ToString(player.health));
					cout << endl;
					Sleep(2137);
					PlayerDead();
				}
				else
				{
					cls();
					ShowPlayerStats(player);
					cout << "You encountered " << monster.GetName() << "!";
					moveCursor(84, 4);
					textColor.Write("[H] Help", "sub", "sub");
					cout << "\nIt looks like it has " + ToString(monster.GetMaxHealth()) + " health and " + ToString(monster.GetStrength()) + " strength!\n\n";
					textColor.SetColor("consumable");
					Sleep(200);
					writer.Write("\nYou defeated " + monster.GetName() + "!\nXP gained: " + ToString(monster.GetXP()) + "\nGold gained: " + ToString(monster.GetGold()) + "\n\n");
					player.GainXP(monster.GetXP());
					player.AddGold(monster.GetGold());
					textColor.SetColor("default");
					system("pause");
					cls();
					LootMonster(monster, player);
				}
			}

			if (doPause)
				system("pause");
			cls();
			if (firstScreen)
				firstScreen = false;
		} while (fight == true);
	}