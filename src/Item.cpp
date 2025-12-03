#include "Item.h"

using namespace std;


// ============================================================================
// Base Item class implementation
// ============================================================================

// TODO: Implement Item constructor
// HINTS:
// - Use initializer list to initialize all member variables
// - Parameters map directly to member variables
//
Item::Item(const std::string& name, const std::string& description,
           const std::string& type, int value)
    : name(name), description(description), type(type), value(value) {
}


// TODO: Implement Item destructor
// HINTS:
// - Can add debug output if helpful
//
Item::~Item() {
}


// TODO: Implement displayInfo (base version)
// HINTS:
// - Print item name, description, and value
// - Format: 
//   [ITEM] ItemName
//     Description text
//     Value: X
//
void Item::displayInfo() const {
    // TODO: Display item information
    cout << "[ITEM] " << name << "\n" //print item name
         << "  " << description << "\n" // print description
         << "  Value: " << value << endl; // print value
}


// TODO: Implement displayBrief
// HINTS:
// - One line format: "Name (Type)"
// - Example: "Iron Sword (Weapon)"
//
void Item::displayBrief() const {
    // TODO: Display brief item info
    cout << name << " (" << type << ")";
}


// ============================================================================
// Weapon class implementation
// ============================================================================

// TODO: Implement Weapon constructor
// HINTS:
// - MUST call base Item constructor using initializer list
// - Type should be "Weapon"
// - Value is the damage bonus
// - Also initialize damage_bonus member
// - Format: Weapon::Weapon(...) : Item(name, desc, "Weapon", damage), damage_bonus(damage) { }
//
Weapon::Weapon(const std::string& name, const std::string& description, int damage)
    : Item(name, description, "Weapon", damage), damage_bonus(damage) {

}


// TODO: Override displayInfo for Weapon
// HINTS:
// - Print weapon-specific format
// - Use getName(), getDescription(), getDamageBonus()
// - Format:
//   [WEAPON] WeaponName
//     Description
//     Damage Bonus: +X
//
void Weapon::displayInfo() const {
    // TODO: Display weapon-specific information
    cout << "[WEAPON] " << getName() << "\n"
        << " " << getDescription() << "\n"
        << " Damage Bonus: +" << damage_bonus << endl;
 }


// ============================================================================
// Armor class implementation
// ============================================================================

// TODO: Implement Armor constructor
// HINTS:
// - MUST call base Item constructor using initializer list
// - Type should be "Armor"
// - Value is the defense bonus
// - Also initialize defense_bonus member
//
Armor::Armor(const std::string& name, const std::string& description, int defense)
    : Item(name, description, "Armor", defense), defense_bonus(defense) {
}


// TODO: Override displayInfo for Armor
// HINTS:
// - Print armor-specific format
// - Format:
//   [ARMOR] ArmorName
//     Description
//     Defense Bonus: +X
//
void Armor::displayInfo() const {
    // TODO: Display armor-specific information
    cout << "[ARMOR] " << getName() << "\n"
        << "  " << getDescription() << "\n"
        << "  Defense Bonus: +" << defense_bonus << endl;

}


// ============================================================================
// Consumable class implementation
// ============================================================================

// TODO: Implement Consumable constructor
// HINTS:
// - MUST call base Item constructor using initializer list
// - Type should be "Consumable"
// - Value is the healing amount
// - Initialize healing_amount and set used to false
//
Consumable::Consumable(const std::string& name, const std::string& description, 
                       int healing)
    : Item(name, description, "Consumable", healing), 
      healing_amount(healing), used(false) {
}


// TODO: Override displayInfo for Consumable
// HINTS:
// - Print consumable-specific format
// - Format:
//   [CONSUMABLE] ConsumableName
//     Description
//     Restores: X HP
//
void Consumable::displayInfo() const {
    // TODO: Display consumable-specific information
    cout << "[CONSUMABLE] " << getName() << "\n"
        << "  " << getDescription() << "\n"
        << "  Restores: " << healing_amount << " HP" << endl;
}


// TODO: Implement use() function
// HINTS:
// - Check if already used
// - If not used: print message and set used to true
// - If already used: print error message
// - Format: "Used ItemName! Restored X HP."
//
void Consumable::use() {
    // TODO: Implement use logic
    if(used){
        //print out that item is already used
        cout << getName() << " has already been used!" << endl;
    }
    //print out that item is used and hp is restored
    cout << "Used " << getName() << "! Restored " << healing_amount << " HP." << endl;
     
    //set used flag to be true 
    used = true;
}
// these items are added for extra credit extensions
// key class implementation

//key is made but I didn't have enough time to build lock and unlocked mechanism to the game
// so key is just an item that can be displayed, but doens't do any functionality in the game
Key::Key(const std::string& name, const std::string& description)
    : Item(name, description, "Key", 0) {}

void Key::displayInfo() const {
    cout << "[KEY] " << getName() << "\n"
         << "  " << getDescription() << endl;
}


// ============================================================================
// scroll class implementation
// ============================================================================

Scroll::Scroll(const string& name, const string& desc, int dmg)
    : Item(name, desc, "Scroll", dmg),
      damage_amount(dmg), used(false) {}

void Scroll::displayInfo() const{
    cout << "[SCROLL] " << getName() << "\n"
         << "  " << getDescription() << "\n"
         << "  Deals: " << damage_amount << " damage\n";
}

void Scroll::use() {
    if(used){
        cout << getName() << " has already been used!\n";
        return;
    }

    cout << "You unleash the power of " << getName() << "! It deals " << damage_amount << " magical damage!\n";

    used = true;
}


// GoldItem class implementation
// GoldItem is an item tha can be sold in the shop for gold coins
// It cannot be used directly

GoldItem::GoldItem(const std::string& name, const std::string& desc, int value)
    : Item(name, desc, "Gold", value), worth(value) {
}

void GoldItem::displayInfo() const {
    cout << "[GOLD] " << getName() << "\n"
         << "  " << getDescription() << "\n"
         << "  Worth: " << worth << " gold coins" << endl;
}

void GoldItem::use() {
    cout << "Gold cannot be used directly! It can only be sold.\n";
    // can't use gold directly
}