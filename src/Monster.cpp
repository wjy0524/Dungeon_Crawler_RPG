#include "Monster.h"
#include <iostream>
using namespace std;

// ============================================================================
// Base Monster class
// ============================================================================

// TODO: Implement Monster constructor
// HINTS:
// - MUST call Character base constructor
// - Initialize experience_reward and gold_reward
// - Loot table starts empty automatically
//
Monster::Monster(const std::string& name, int hp, int attack, int defense,
                 int exp_reward, int gold_reward)
    : Character(name, hp, attack, defense),
      experience_reward(exp_reward), gold_reward(gold_reward) {
}


// TODO: Implement Monster destructor
// HINTS:
// - Deallocate any allocated memory 
// - Loop through loot_table vector and delete each Item*
// - Clear the vector after deleting items
//
Monster::~Monster() {
    //loop through loot_table and delete each loot_table[i] Item*
    for(size_t i = 0; i < loot_table.size(); i++){
        delete loot_table[i];
    }
    loot_table.clear();
}


// TODO: Override displayStats
// HINTS:
// - Show monster name and HP
// - Format: "MonsterName [HP: current/max]"
// - Keep it simple - monsters don't need detailed stats display
//
void Monster::displayStats() const {
    // TODO: Display monster stats
    cout << getName() << " [HP: " << getCurrentHP() << "/" << getMaxHP() << "]\n";
}


// TODO: Implement addLoot
// HINTS:
// - Check if item pointer is not NULL
// - Add item to loot_table vector using push_back()
//
void Monster::addLoot(Item* item) {
    // TODO: Add item to loot table
    //check if item pointer is NULL 
    //if so just return
    if(item == NULL){
        return;
    }
    //add item to loot_table vector using push_back()
    loot_table.push_back(item);
}


// TODO: Implement dropLoot
// HINTS:
// - Create a copy of the loot_table vector
// - Clear the original loot_table (transfer ownership to caller!)
// - Return the copy
// - This is important: caller now owns the items and must delete them
//
std::vector<Item*> Monster::dropLoot() {
    // TODO: Return loot and transfer ownership
    //create a copy of the loot_table vector
    std::vector<Item*> copy = loot_table;
    //clear the original loot_table
    loot_table.clear();
    return copy;  // return the copy
}


// TODO: Implement getAttackMessage (base version)
// HINTS:
// - Return default attack message
// - Format: "MonsterName attacks!"
// - Use getName() to get monster's name
//
std::string Monster::getAttackMessage() const {
    // TODO: Return attack message
    return getName() + " attacks!";
}


// ============================================================================
// Goblin - Weak but common enemy
// ============================================================================

// TODO: Implement Goblin constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Goblin"
//   * HP: 30
//   * Attack: 5
//   * Defense: 2
//   * Experience: 10
//   * Gold: 5
// - Add a small potion to loot table
// - Example: addLoot(new Consumable("Small Potion", "Restores 10 HP", 10));
//
Goblin::Goblin() 
    : Monster("Goblin", 30, 5, 2, 10, 5) {
    // TODO: Add loot items
    addLoot(new Consumable("Small Potion", "Restores 10 HP", 10));
}


// TODO: Override getAttackMessage for Goblin
// HINTS:
// - Return goblin-specific attack message
// - Example: "The goblin swipes at you with its rusty dagger!"
//
std::string Goblin::getAttackMessage() const {
    // TODO: Return goblin attack message
    return "The goblin slashes toward you with its corroded blade!";
}


// ============================================================================
// Skeleton - Undead warrior
// ============================================================================

// TODO: Implement Skeleton constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Skeleton"
//   * HP: 40
//   * Attack: 8
//   * Defense: 4
//   * Experience: 20
//   * Gold: 10
// - Add an old sword to loot table
//
Skeleton::Skeleton()
    : Monster("Skeleton", 40, 8, 4, 20, 10) {
    // TODO: Add loot items
    addLoot(new Weapon("Old Sword", "A worn-out blade", 3));
}


// TODO: Override getAttackMessage for Skeleton
// HINTS:
// - Return skeleton-specific attack message
// - Example: "The skeleton rattles its bones and slashes with a sword!"
//
std::string Skeleton::getAttackMessage() const {
    // TODO: Return skeleton attack message
    return "The skeleton charges, bones clacking as it swings its rusted sword!";
}


// ============================================================================
// Dragon - Boss enemy with special ability
// ============================================================================

// TODO: Implement Dragon constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Dragon"
//   * HP: 150
//   * Attack: 20
//   * Defense: 10
//   * Experience: 100
//   * Gold: 50
// - Add legendary loot:
//   * Dragon Slayer sword (damage +10)
//   * Dragon Scale Armor (defense +8)
//   * Greater Health Potion (heals 100 HP)
//
Dragon::Dragon()
    : Monster("Dragon", 150, 20, 10, 100, 50) {
    // TODO: Add legendary loot items
    addLoot(new Weapon("Dragon Slayer sword", "Legendary sword forged to slay dragons", 10));
    addLoot(new Armor("Dragon Scale Armor", "Armor made from dragon scales", 8));
    addLoot(new Consumable("Greater Health Potion", "Restores 100 HP", 100));
}


// TODO: Override getAttackMessage for Dragon
// HINTS:
// - Return dragon-specific attack message
// - Example: "The dragon breathes fire at you!"
//
std::string Dragon::getAttackMessage() const {
    // TODO: Return dragon attack message
    return "The dragon breathes fire at you!";
}


// TODO: Override calculateDamage for Dragon
// HINTS:
// - Call Monster::calculateDamage() to get base damage
// - Add bonus fire damage (+5)
// - Return total damage
// - This makes the dragon hit harder than other monsters!
//
int Dragon::calculateDamage() const {
    // TODO: Calculate damage with fire bonus
    //calculate the base damage
    int basedamage = Monster::calculateDamage();
    return basedamage + 5;  // total damage: base + 5
}



// additonal monsters for extra credit extensions
// those extra monsters are implemented in the game appearing
//Troll
Troll::Troll()
    : Monster("Troll", 120, 6, 5, 40, 15){ // the property of troll is that it has high hp
    addLoot(new Consumable("Medium Potion", "Restores 40 HP", 40));
    addLoot(new Weapon("Heavy Club", "A big crude club", 4));
}

std::string Troll::getAttackMessage() const {
    return "The troll smashes you with its heavy club!";
}

//Ghost
//it has the avoidance ability
//hit or miss (50%) when the player attacks the ghost
Ghost::Ghost()
    : Monster("Ghost", 25, 12, 2, 30, 10)
{
    addLoot(new Consumable("Spirit Dust", "Mystical dust", 20));
}

std::string Ghost::getAttackMessage() const {
    return "The ghost unleashes a chilling wail!";
}

//wizard
Wizard::Wizard()
    : Monster("Wizard", 50, 15, 3, 50, 20)
{
    addLoot(new Weapon("Magic Wand", "A wand infused with arcane power", 6));
    addLoot(new Scroll("Scroll of Fireball", "Unleashes a burst of flame", 80)); // scroll item can be used one time attacking 80 damages
}

std::string Wizard::getAttackMessage() const {
    return "The wizard casts a blazing fireball!";
}

int Wizard::calculateDamage() const {
    int base = Monster::calculateDamage();
    return base + 4; // magic bonus adding from base damage
}

