#include "game.h"

using namespace std;

int main()
{
	srand(time(0));
	TextColorMap textColor;

#pragma region effectsDeclaration

	vector<Effect> effects;

	Effect restoreHPweak(HealthEffect, 5);
	Effect restoreHPmoderate(HealthEffect, 10);
	Effect restoreHPpotent(HealthEffect, 15);
	Effect buffDefenseWeak(DefenseEffect, 5);
	Effect buffDefenseModerate(DefenseEffect, 10);
	Effect buffDefensePotent(DefenseEffect, 15);
	Effect buffStrengthWeak(StrengthEffect, 5);
	Effect buffStrengthModerate(StrengthEffect, 10);
	Effect buffStrengthPotent(StrengthEffect, 15);
	Effect buffXPweak(XPEffect, 1.1);
	Effect buffXPmoderate(XPEffect, 1.2);
	Effect buffXPpotent(XPEffect, 1.3);
	Effect buffGoldWeak(GoldEffect, 1.1);
	Effect buffGoldModerate(GoldEffect, 1.2);
	Effect buffGoldPotent(GoldEffect, 1.3);

	effects.push_back(restoreHPweak);
	effects.push_back(restoreHPmoderate);
	effects.push_back(restoreHPpotent);
	effects.push_back(buffDefenseWeak);
	effects.push_back(buffDefenseModerate);
	effects.push_back(buffDefensePotent);
	effects.push_back(buffStrengthWeak);
	effects.push_back(buffStrengthModerate);
	effects.push_back(buffStrengthPotent);
	effects.push_back(buffXPweak);
	effects.push_back(buffXPmoderate);
	effects.push_back(buffXPpotent);
	effects.push_back(buffGoldWeak);
	effects.push_back(buffGoldModerate);
	effects.push_back(buffGoldPotent);
#pragma endregion		
#pragma region itemsDeclaration

	vector<Item> items;																		//add Effects to Consumables and polish the rest of the code

	Item brokenPen(WeaponItem, "Broken pen", 5, 2, 1);
	Item USB(WeaponItem, "USB stick", 10, 3, 4);
	Item chair(WeaponItem, "Chair", 25, 7, 6);
	Item skates(WeaponItem, "Mr Czekalski's ice-skates", 40, 8, 4);
	Item wire(WeaponItem, "Piece of wire", 1, 1, 1);
	Item capacitor(WeaponItem, "Charged capacitor", 50, 9, 7);
	Item katanaSword(WeaponItem, "Katana sword", 80, 12, 8);
	Item sheet(ArmorItem, "Sheet of paper", 5, 1, 0);
	Item tolcNotes(ArmorItem, "ToLC Notes", 10, 3, 0);
	Item winterHat(ArmorItem, "Winter hat", 15, 7, 0);
	Item NOT(ArmorItem, "Logic gate NOT", 20, 10, 0);
	Item leggins(ArmorItem, "Pair of leggins", 16, 8, 0);
	Item calculus(ArmorItem, "Signature of calculus lecturer", 50, 14, 0);
	Item furCoat(ArmorItem, "Fur coat", 30, 12, 0);
	Item coffeeSmall(ConsumableItem, "Small coffee cup", 6, 5, 0);
	Item coffeeLarge(ConsumableItem, "Large coffee cup", 10, 15, 1);
	Item ciabatta(ConsumableItem, "Ciabatta sandwich", 12, 15, 0);
	Item cig(ConsumableItem, "Cigarette", 15, 10, 2);
	Item twoCigs(ConsumableItem, "Two cigarettes", 25, 10, 5);
	Item cheatSheet(ConsumableItem, "Cheat sheet", 10, 15, 0);
	Item donutSmall(ConsumableItem, "Small donut", 14, 10, 0);
	Item donutLarge(ConsumableItem, "Large donut", 20, 15, 0);
	Item water(ConsumableItem, "Cup of water", 0, 0, 0);
	Item blackHole(ConsumableItem, "Really tiny black hole", 0, 25, 0);
	Item rustyCoin(ConsumableItem, "Rusty coin", 100, 30, 0);
	Item chewingGum(ConsumableItem, "Used chewing gum", 5, 15, 0);

	coffeeSmall.AddEffect(restoreHPweak);								//definition of Consumables' Effects
	coffeeLarge.AddEffect(restoreHPmoderate);
	coffeeLarge.AddEffect(buffXPweak);
	ciabatta.AddEffect(restoreHPmoderate);
	ciabatta.AddEffect(buffDefenseWeak);
	cig.AddEffect(restoreHPweak);
	cig.AddEffect(buffStrengthWeak);
	twoCigs.AddEffect(restoreHPmoderate);
	cheatSheet.AddEffect(buffXPpotent);
	donutSmall.AddEffect(restoreHPmoderate);
	donutLarge.AddEffect(restoreHPpotent);
	blackHole.AddEffect(restoreHPweak);
	blackHole.AddEffect(buffDefenseWeak);
	blackHole.AddEffect(buffStrengthWeak);
	blackHole.AddEffect(buffGoldModerate);
	rustyCoin.AddEffect(buffGoldPotent);
	rustyCoin.AddEffect(buffXPpotent);
	chewingGum.AddEffect(buffStrengthModerate);
	chewingGum.AddEffect(buffDefenseWeak);

	items.push_back(twoCigs);
	items.push_back(skates);
	items.push_back(wire);
	items.push_back(cheatSheet);
	items.push_back(donutSmall);
	items.push_back(donutLarge);
	items.push_back(blackHole);
	items.push_back(rustyCoin);
	items.push_back(chewingGum);
	items.push_back(coffeeLarge);
	items.push_back(brokenPen);
	items.push_back(USB);
	items.push_back(chair);
	items.push_back(katanaSword);
	items.push_back(sheet);
	items.push_back(tolcNotes);
	items.push_back(winterHat);
	items.push_back(coffeeSmall);
	items.push_back(ciabatta);
	items.push_back(cig);
	items.push_back(capacitor);
	items.push_back(NOT);
	items.push_back(water);

#pragma endregion	
#pragma region monsterDeclaration

	vector<Monster> monsters;

	Monster parkingLot("Full Parking Lot", 1);
	Monster elevator("Broken Elevator", 1);
	Monster cigarette("Cigarette", 1);
	Monster socs("Sociology Class Test", 1);
	Monster coffeeCup("Another Coffee Cup", 2);
	Monster ieecQuiz7("IEEC Quiz no 7", 2);
	Monster flatTire("Flat Tire", 2);
	Monster lectureQuiz("Unexpected Calculus Lecture Quiz", 2);
	Monster deansOffice("Dean's Office", 3);
	Monster algebra("Algebra 4th Correction Term", 3);
	Monster focpProj("FoCP Project", 3);
	Monster room622a("Room 622a", 3);
	Monster packOfCigarettes("Another Pack of Cigarettes", 4);
	Monster calculusExam("Calculus I Exam", 4);
	Monster ieecQuiz14("IEEC Quiz no 14", 4);
	Monster secondSem("Second Semester", 4);
	Monster circuitTheory("Circuit Theory Assessment Test", 5);
	Monster room816("Room 816", 5);
	Monster counter("Mod-3 Asynchronous T Flip-Flop Counter", 5);
	Monster derivative("Missing Square Root in E8", 5);

	monsters.push_back(parkingLot);
	monsters.push_back(elevator);
	monsters.push_back(cigarette);
	monsters.push_back(socs);
	monsters.push_back(coffeeCup);
	monsters.push_back(ieecQuiz7);
	monsters.push_back(flatTire);
	monsters.push_back(lectureQuiz);
	monsters.push_back(deansOffice);
	monsters.push_back(algebra);
	monsters.push_back(focpProj);
	monsters.push_back(room622a);
	monsters.push_back(packOfCigarettes);
	monsters.push_back(calculusExam);
	monsters.push_back(ieecQuiz14);
	monsters.push_back(secondSem);
	monsters.push_back(circuitTheory);
	monsters.push_back(room816);
	monsters.push_back(counter);
	monsters.push_back(derivative);
#pragma endregion	

	Game game;

	while (true)
	{
		Monster monster;														//maximum of 1 level higher and minimum of 1 level lower, 1st lvl only with 1st lvl
		if (game.player.GetLevel() == 1)
			monster = monsters[rand() % 4];
		else if (game.player.GetLevel() == 5)
			monster = monsters[rand() % 8 + 12];
		else if(game.player.GetLevel() < 5)
			monster = monsters[rand() % 12 + 4 * (game.player.GetLevel() - 2)];
		else
		{
			monster = monsters[rand() % monsters.size()];
			monster = Monster(monster.GetName(), game.player.GetLevel());
		}

		vector<Item> monsterLoot;

		for (int i = 0; i <= game.player.GetLevel(); i++)
		{
			monsterLoot.push_back(items[rand() % items.size()]);
			if (rand() % 2)
				break;
		}

		for (Item & eqPiece : monsterLoot)
		{
			if (eqPiece.GetType() == ConsumableItem)				//consumables have their own, pre-determined effects
				continue;
			if (!(rand() % 4))
			{
				eqPiece.AddEffect(effects[rand() % effects.size()]);
				if (!(rand() % 4))
					eqPiece.AddEffect(effects[rand() % effects.size()]);
				if (!(rand() % 10))
					eqPiece.AddEffect(effects[rand() % effects.size()]);
			}
		}

		for (Item item : monsterLoot)
			monster.StoreItem(item);

		game.Fight(monster);
	}

	textColor.SetColor("neutral");
	system("pause");
}