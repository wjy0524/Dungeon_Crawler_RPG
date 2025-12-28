# 🐉 Dungeon Adventure RPG

## 🔧 Overview

This is a **text-based RPG game built in C++**, showcasing object-oriented programming concepts such as  
inheritance, polymorphism, dynamic memory management, and class hierarchy design.

The player navigates rooms, battles monsters, collects items, manages equipment, and attempts to defeat  
the **Dragon** in the Throne Room.

---

## ⭐ Key Features

- Object-Oriented Design (Inheritance & Polymorphism)
- Turn-based combat
- Inventory & equipment system
- Character class selection
- Room navigation system
- Shop system (buy & sell)
- Dynamic memory management
- ASCII-art character display

---

## 🧱 Class Structure

### Core Hierarchy

                Character
                /      \
            Player     Monster
                         / |  |  \
           Goblin Skeleton Ghost Dragon ...


### Game World Components

- **Game** → manages world, rooms, interactions  
- **Room** → contains `Monster*`, `vector<Item*>`, `map<string, Room*>`  
- **Items** → base `Item` class with derived types:
  - `Weapon`
  - `Armor`
  - `Consumable`
  - `Scroll`
  - `Key`
  - `GoldItem`

- **Monsters** → base `Monster` class with overrides:
  - Goblin
  - Troll
  - Skeleton
  - Ghost (special dodge ability)
  - Wizard
  - Dragon (boss)

---

## 🧠 Design Decisions

### Inheritance & Polymorphism
The project uses an OOP structure where `Player` and all monster types inherit from `Character`.  
Polymorphism allows monsters to override behaviors such as `calculateDamage()` or special abilities  
(e.g., **Ghost dodge mechanic**).  
This design is far more extensible than a procedural C version and enables a clean separation of logic.

### Memory Management
All dynamically allocated objects (`Item`, `Monster`, `Room`, `Player`) are owned explicitly:  
- `Game` deletes the `Player` and all `Room` objects.  
- Each `Room` destructor deletes its `Monster` and all items it owns.  
- `Player` destructor deletes all inventory items.  
Valgrind was used extensively to ensure **zero memory leaks**.

---

## 🧪 Testing & Debugging

### Testing Strategy
Beyond running `make test`, manual gameplay testing was performed to verify movement, combat,  
inventory operations, shop behavior, and item usage. Edge cases such as invalid input, fleeing combat,  
or picking up nonexistent items were also tested.

### Hardest Bug Found
The most difficult bug involved input handling, where using `getline()` after `cin` caused input buffering  
issues. This was solved by removing the unnecessary `cin.ignore()` after understanding that only `getline()`  
was being used. Valgrind also helped identify missing deletes and ownership issues.

---

## ⚔️ Implementation Challenges

1. **Hardest TODO**  
   Implementing the full combat system with Ghost dodge mechanics and scroll damage logic.

2. **Most Time-Consuming**  
   The inventory system and item ownership transfer between rooms and players.

3. **Most Interesting**  
   Designing monster subclasses and adding unique behaviors like Ghost phase-dodge and Dragon boss logic.

---

## 📝 Reflection

The most valuable lesson from this lab was understanding **ownership and memory management** in C++  
while designing maintainable object-oriented systems. Structuring the project with clean class boundaries  
made debugging and extending the game significantly easier.

---

## 📦 Build & Run

```bash
make clean
make
run
```

## How to Play
go <direction>
look
attack
pickup <item>
inventory
use <item>
equip <item>
stats
shop
help
quit
