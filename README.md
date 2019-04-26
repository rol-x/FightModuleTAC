# FightModuleTAC
Fight module containing items, effects and different monsters programmed as a part of The Amulets Of Camembert Project.

# Source file organization 
The project consists of 9 source code files (\*.cpp - containing main function file and 8 classes) and 9 header files (\*.h - containing precompiled headers file stdafx.h and 8 classes).

# The Gameplay
Player is presented with a foe, which has some HP, strength, defense and loot. At the beginning of each turn, the player decides whether to attack the enemy, manipulate his invetory or try to run away. As the player progresses, so does the gameplay, facing them with more demanding enemies and rewarding victories with XP and gold.

# Classes
Classes used:
*Monster, Player, Item, Effect, Game, Color, EpicWriter and TextColorMap*.
Each is responsible for a single element of the gameplay and while some of them are subcategorized (e.g. with ItemType enumerator), it's clear what purpose does each one of them serve.

# Cloning the repository
To test the gameplay, simply clone the repository into your local repository: 

<pre class="command-line"><span class="command">git clone https://github.com/rol-x/FightModuleTAC.git</span>
</pre>

`Written in C++ by Charles John Summers 2018`
