#include "Player.h"
#include <iostream>
#include <algorithm>
using namespace std;

//lower case function
string toLower(const string& s){
    string lower = s;
    for (int i = 0; i < lower.length(); i++) {
        if (lower[i] >= 'A' && lower[i] <= 'Z') {
            lower[i] = lower[i] + ('a' - 'A');
        }
    }
    return lower;
}

// TODO: Implement Player constructor
// HINTS:
// - MUST call Character base constructor. 
//
Player::Player(const std::string& name)
    : Character(name, 100, 10, 5),
      level(1), experience(0), gold(0),
      equipped_weapon(NULL), equipped_armor(NULL) {
}


// TODO: Implement Player destructor
// HINTS:
// - CRITICAL: Must delete all items in inventory to prevent memory leaks!
// - DON'T delete equipped_weapon or equipped_armor - they point to items
//   already in the inventory, so they're already deleted!
//
Player::~Player() {
    // TODO: Delete all inventory items
    for(int i=0; i<inventory.size(); i++){
        delete inventory[i];
    }
    inventory.clear();

}


// TODO: Override displayStats
// HINTS:
// - Show player-specific information
// - Include: level, HP, attack (with weapon bonus), defense (with armor bonus), gold, experience
// - Show equipped weapon and armor names if any
// - Use decorative formatting (borders, headers)
// - Use getters to access inherited Character data
//
void Player::displayStats() const {
    // TODO: Display comprehensive player stats
    cout << "\n========== PLAYER STATUS ==========\n";
    //player-specific information
    ////player's name
    cout << "Name: " << getName() << "\n"; 
    //player's current level and experience
    cout << "Level: " << level <<  " (EXP: " << experience << "/" << level * 100 << ")\n";
    //player's current HP / MaxHP
    cout << "HP: " << getCurrentHP() << "/" << getMaxHP() << "\n";
    
    //attack(with weapon bonus)
    int weapon_bonus = 0;
    if(equipped_weapon != NULL){
        cout << "Attack: " << getAttack() << " (+" << equipped_weapon->getValue() << " from " << equipped_weapon->getName() << ")\n";
    }else{
        cout << "Attack: " << getAttack() << "\n";
    }

    //defense (with armor bonuns)
    if(equipped_armor != NULL){
        cout << "Defense: " << getDefense() << " (+" << equipped_armor->getValue() << " from " << equipped_armor->getName() << ")\n";
    }else{
        cout << "Defense: " << getDefense() << "\n";
    }

    //Gold
    cout << "Gold: " << gold << "\n";

    // any equipped weapon or armor if any
    cout << "Equipped Weapon: " << (equipped_weapon ? equipped_weapon->getName() : "None") << "\n";
    cout << "Equipped Armor : " << (equipped_armor ? equipped_armor->getName() : "None") << "\n";

    cout << "==================================\n\n";
    
}
// TODO: Override calculateDamage to include weapon bonus
// HINTS:
// - If weapon is equipped, add weapon's damage bonus
// - Return total damage
//
int Player::calculateDamage() const {
    // TODO: Calculate damage with weapon bonus
    //base damage coming from the particular character
    int damage = Character::calculateDamage();
    //if weapon is equipped, add weapon's damage bonus
    if(equipped_weapon != NULL){
        damage += equipped_weapon->getValue();
    }

    return damage;  // return total damage
}


// TODO: Implement addItem
// HINTS:
// - Add item to inventory vector using push_back()
// - Print pickup message with item name
//
void Player::addItem(Item* item) {
    // TODO: Add item to inventory
    //to prevent segfault, I am checking NULL first
    if(item == NULL){
        cout << "Cannot add a null item." << endl;
        return;
    }
    //add item to invetory vector using push_back(item)
    inventory.push_back(item);
    //print pickup message with item name
    cout << "Picked up: " << item->getName() << "\n";
}


// TODO: Implement removeItem
// HINTS:
// - Search inventory for item by name (case-insensitive comparison)
// - If found: delete the item, then erase from vector
// - If not found: print error message
// - Remember: inventory.erase(inventory.begin() + i) to remove at index i
//
void Player::removeItem(const std::string& item_name) {
    // TODO: Find and remove item from inventory
    //i have to check if the inventory is empty before searching the item
    if(inventory.empty()){
        cout << "Inventory is empty: No item to remove." << endl;
        return;
    }
    //change the item name into lowercase (case-insensitive comparsion)
    string target = toLower(item_name);
    //search inventory for item by name
    for(int i = 0; i < inventory.size(); i++){
        string current = toLower(inventory[i]->getName());
        //if found: delete the item, then erase from vector
        if(current == target){
            cout << "Removed: " << inventory[i]->getName() << endl;
            delete inventory[i];   
            inventory.erase(inventory.begin() + i);
            return;  
        }
    }
    //not found: print error message
    //print out: You don't have an item called "item_name".
    cout << "You don't have an item called \"" << item_name << "\"." << endl;

}


// TODO: Implement displayInventory
// HINTS:
// - Print header: "----- Inventory -----"
// - If inventory is empty, print "Empty"
// - Otherwise, loop through and print each item's name and type
// - Format: "- ItemName (ItemType)"
// - Print footer: "--------------------"
//
void Player::displayInventory() const {
    // TODO: Display all items in inventory
    cout << "----- Inventory -----\n";
    //if inventory is empty, just print "Empty"
    if(inventory.empty()){
        cout << "Empty" << "\n";
    }else{
        //loop through and print each item's name and type
        for(int i = 0; i < inventory.size(); i++){
            Item* item = inventory[i];
            cout << " - " << item->getName() << " (" << item->getType() << ")" << "\n";
        }
    }
    //print footer
    cout << "--------------------" << "\n";
}


// TODO: Implement hasItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return true if found, false otherwise
// - Use same case-insensitive comparison as removeItem
//
bool Player::hasItem(const std::string& item_name) const {
    // TODO: Check if item exists in inventory
    string target = toLower(item_name);
    //loop through inventory to figure out if the item is in inventory
    for(int i = 0; i < inventory.size(); i++){
        string current = toLower(inventory[i]->getName());
        //if so, return true
        if (current == target) {
            return true;
        }
    }
    //if not found, return false
    return false;  
}


// TODO: Implement getItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return pointer to item if found
// - Return NULL if not found
//
Item* Player::getItem(const std::string& item_name) {
    // TODO: Find and return item pointer
    string target = toLower(item_name);
    //loop through inventory to figure out if item is in inventory
    for(int i=0; i<inventory.size(); i++){
        string current = toLower(inventory[i]->getName());
        //if found
        if(current == target){
            return inventory[i];
        }
    }
    //if not found
    return NULL;  
}


// TODO: Implement equipWeapon
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Weapon"
// - If current weapon equipped, print unequip message
// - Set equipped_weapon pointer to this item
// - Print equip message
//
void Player::equipWeapon(const std::string& weapon_name) {
    // TODO: Equip weapon from inventory
    //get item from inventory using getItem()
    //toLower is done in getItem(), no need to redo it here
    Item* item = getItem(weapon_name);
    //if item is NULL
    if (item == NULL) {
        cout << "You don't have that item." << endl;
        return;
    }

    //now I have to check if item type is weapon
    //if the item is not NULL
    if(item->getType() != "Weapon"){
        cout << "You cannot equip that item." << endl;
        return;
    }
    //If current weapon equipped, print unequip message
    if(equipped_weapon != NULL){
        cout << "Unequipped " << equipped_weapon->getName() << "." << "\n";
    }
    //equipped with new weapon
    equipped_weapon = item;
    cout << "Equipped " << item->getName() << "." << endl;

}


// TODO: Implement equipArmor
// HINTS:
// - Similar to equipWeapon but for armor
// - Check if item type is "Armor"
// - Set equipped_armor pointer
//
void Player::equipArmor(const std::string& armor_name) {
    // TODO: Equip armor from inventory
    Item* item = getItem(armor_name);
    //if item is NULL
    if (item == NULL) {
        cout << "You don't have that item." << endl;
        return;
    }

    //now I have to check if item type is weapon
    //if the item is not NULL
    if(item->getType() != "Armor"){
        cout << "You cannot equip that item." << endl;
        return;
    }
    //If current armor equipped, print unequip message
    if(equipped_armor != NULL){
        cout << "Unequipped " << equipped_armor->getName() << "." << "\n";
    }
    //equipped with new armor
    equipped_armor = item;
    cout << "Equipped " << item->getName() << "." << endl;
}


// TODO: Implement unequipWeapon
// HINTS:
// - Check if weapon is currently equipped
// - If so, print message and set equipped_weapon to NULL
// - If not, print error message
//
void Player::unequipWeapon() {
    // TODO: Unequip current weapon
    //if no weapon is equipped
    if(equipped_weapon == NULL){
        cout << "No weapon is currently equipped." << endl;
        return;
    }
    //if weapon is equipped
    cout << "Unequipped " << equipped_weapon->getName() << "." << endl;
    //unequip the weapon
    equipped_weapon = NULL;

}


// TODO: Implement unequipArmor
// HINTS:
// - Similar to unequipWeapon
// - Set equipped_armor to NULL
//
void Player::unequipArmor() {
    // TODO: Unequip current armor
    if(equipped_armor == NULL){
        cout << "No armor is currently equipped." << endl;
        return;
    }
    //if armor is equipped
    cout << "Unequipped " << equipped_armor->getName() << "." << endl;
    //unequip the armor
    equipped_armor = NULL;
}


// TODO: Implement useItem
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Consumable"
// - Cast to Consumable*: Consumable* consumable = static_cast<Consumable*>(item)
// - Check if already used: consumable->isUsed()
// - Get healing amount: consumable->getHealingAmount()
// - Call heal() with that amount
// - Call consumable->use() to mark as used
// - Remove item from inventory (it's been consumed!)
//
void Player::useItem(const std::string& item_name) {
    // TODO: Use consumable item
    //have to find the item from the inventory first
    Item* item = getItem(item_name);

    //check if item exits
    //if there is no item, print out that user doesn't have the item
    if(item == NULL){
        cout << "You don't have an item called \"" << item_name << "\"." << endl;
        return;
    }

    //check if item type is consumable
    //if it not, tell users that they can only use consumable items
    if(item->getType() != "Consumable"){
        cout << "You can only use consumable items." << endl;
        return;
    }

    //Cast to Consumable*: Consumable* consumable = static_cast<Consumable*>(item)
    Consumable* consumable = static_cast<Consumable*>(item);

    //check if it is already used
    if(consumable->isUsed()){
        cout << consumable->getName() << " has already been used!" << endl;
        return;
    }

    //get healing amount
    int healamount = consumable->getHealingAmount();

    //player's get healed with that amount
    heal(healamount);

    //use flag for that item becomes true
    consumable->use();

    //remove the item and delete it from the inventory
    removeItem(consumable->getName());
}


// TODO: Implement gainExperience
// HINTS:
// - Add experience points
// - Print message showing exp gained
// - Check if enough exp to level up: if (experience >= level * 100)
// - If so, call levelUp()
//
void Player::gainExperience(int exp) {
    // TODO: Add experience and check for level up
    //add experience points
    experience += exp;
    //print message showing exp gained
    cout << "You gained " << exp << " experience points." << "\n";

    //check if enough exp to level up
    if(experience >= level*100){
        levelUp();
    }

}


// TODO: Implement levelUp
// HINTS:
// - Increment level
// - Reset experience to 0
// - Increase stats:
//   * Increase max_hp by 10 (use setMaxHP())
//   * Set current_hp to max (full heal on level up)
//   * Increase attack by 2
//   * Increase defense by 1
// - Print celebratory level up message
// - Display new stats
//
void Player::levelUp() {
    // TODO: Level up the player
    //increment level
    level++;
    //reset experience to 0
    experience = 0;
    //increase stats
    setMaxHP(getMaxHP()+10);
    setCurrentHP(getMaxHP());
    setAttack(getAttack()+2);
    setDefense(getDefense()+1);

    //print celebratory level up message
    cout << "=== LEVEL UP! ===" << "\n";
    cout << "You reached level " << level << "!" << "\n";

    //display new stats
    displayStats();

}
