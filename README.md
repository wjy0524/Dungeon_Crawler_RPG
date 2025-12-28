🏰 Dungeon Adventure RPG – README
📌 Overview

This project is a text-based RPG built in C++ using object-oriented programming techniques.
The player explores interconnected rooms, battles monsters, manages inventory, collects items, and aims to defeat the Dragon in the Throne Room.

Key features include:

Inheritance & Polymorphism

Turn-based combat

Inventory & equipment system

Character class selection

Room navigation system

Shop system (buy & sell)

Dynamic memory management

ASCII art flavor

🧱 Class Structure
Core Hierarchy
                Character
                /      \
            Player     Monster
                         / |  |  \
           Goblin Skeleton Ghost Dragon ...

Game World Components
Game → manages world, rooms, interactions
Room → contains Monster*, vector<Item*>, map<string, Room*>

Item (base)
 ├─ Weapon
 ├─ Armor
 ├─ Consumable
 ├─ Scroll
 ├─ Key
 └─ GoldItem

🧙‍♂️ Character Classes

Player can select from four classes (stats differ slightly):

Class	HP	Attack	Defense	Notes
Warrior	High HP	High DEF	Tanky frontline	
Mage	Low HP	High magic dmg	Fragile	
Archer	Balanced	Mid dmg	Long-range style	
Rogue	High dmg	Low DEF	Fast striker	

Each class prints unique ASCII character art when showing stats.

⚔️ Combat System

Turn-based battle loop

Player actions:

attack

use <item>

flee

Ghosts have 50% dodge mechanic

Scrolls deal magic damage

Monsters drop loot + exp + gold

Defeating the Dragon activates victory flag

🧭 World Layout
                [Throne Room]
                     |
     [Armory] - [Hallway] - [Treasury] - [Vault]
                     |
    [Barracks] - [Library]
                     |
                [Catacombs]

                   [Entrance]


Each room contains:

Description

Optional monster

Items on ground

Exits to other rooms

🗝 Items

Item types and functionality:

Item Type	Purpose
Weapon	Increase attack damage
Armor	Increase defense
Consumable	Restore HP
Scroll	Magic damage attack
Key	Used to unlock future content
GoldItem	Sellable items for gold

Inventory supports:

pickup

use

equip

remove

🛒 Shop System (Extension)

The dungeon shop allows the player to:

Buy

Potions

Swords

Armor

Magic Scrolls

Sell

Any item from inventory

Prices based on item value

ASCII merchant included for flavor.

🔢 Memory Management

Memory ownership is clearly assigned:

Game deletes:

player

all rooms

Room deletes:

its monster

all items on the ground

Player deletes:

items stored in their inventory

All dynamic allocations verified with:

valgrind --leak-check=full ./bin/rpg_game


Zero leaks confirmed.

🚀 Compilation & Execution
Build
make

Run
./bin/rpg_game

Clean
make clean

Valgrind
valgrind --leak-check=full ./bin/rpg_game

🧪 Testing

Testing included:

Running through every room & command

Fighting all monster types

Inventory stress testing (equip/unequip/use/remove)

Shop buy/sell loops

Invalid command handling

Edge cases (flee in combat, using scrolls, ghost dodge)

Memory validation via Valgrind

Major bugs fixed:

Input buffering issue with getline

Double-delete from Room → Player item transfer

Combat flow breaking when scrolls were used

Monster dodge logic issue

📝 Extensions Implemented

Character class selection (Warrior/Mage/Archer/Rogue)

ASCII art for player characters and NPC merchant

Full Shop system (buy + sell)

Magic scroll attacks

Ghost dodge mechanic

Key items (Silver Key, Golden Key)

Dragon final boss + victory flag

💡 Reflection

This lab taught me real-world OOP design with constructors, destructors, dynamic memory ownership, and how to structure a multi-file C++ project. Debugging with Valgrind was especially helpful for building safer memory habits.
