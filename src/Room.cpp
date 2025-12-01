#include "Room.h"
#include <iostream>
#include <algorithm>
using namespace std;

//lower case function
static string toLower(const string& s){
    string lower = s;
    for (int i = 0; i < lower.length(); i++) {
        if (lower[i] >= 'A' && lower[i] <= 'Z') {
            lower[i] = lower[i] + ('a' - 'A');
        }
    }
    return lower;
}

// TODO: Implement Room constructor
Room::Room(const std::string& name, const std::string& description)
    : name(name), description(description), visited(false), monster(NULL) {
}


// TODO: Implement Room destructor
Room::~Room() {
    // TODO: Clean up monster and items
    //clean up monster
    clearMonster();
    //clean up the items
    for(int i = 0; i < items.size(); i++){
        delete items[i];
    }
    items.clear();

}


// TODO: Implement display
// HINTS:
// - Print formatted room information with decorative borders
// - Format:
//   ========================================
//   Room Name
//   ========================================
//   Description text
//   
//   [If monster] A MonsterName blocks your path!
//   
//   [If items] Items here:
//     - item1
//     - item2
//   
//   Exits: north, south, east
//   ========================================
//
void Room::display() const {
    // TODO: Display room information
    cout << "========================================\n";
    cout << name << "\n";
    cout << "========================================\n";
    cout << description << "\n\n";

    //if there is a monster
    if(hasMonster()){
        cout << "A " << monster->getName() << " blocks your path!\n\n";
    }

    //if there are items
    if(!items.empty()){
        cout << "Items here:\n";
        displayItems();
    } 
    //exits
    displayExits();
    cout << "\n========================================\n";
}


// TODO: Implement displayExits
// HINTS:
// - Print "Exits: "
// - Iterate through exits map using iterator
// - Print each direction (the key) separated by commas
// - Example output: "Exits: north, south, east"
//
void Room::displayExits() const {
    // TODO: Display available exits
    cout << "Exits: ";
    //if there is no exit
    if(exits.empty()){
        cout << "None\n";
    }else{
        bool first = true;
        for(map<string, Room*>::const_iterator it = exits.begin(); it != exits.end(); ++it){
            if(!first) cout << ", ";
            cout << it->first;
            first = false;
        }
    }

}


// TODO: Implement addExit
// HINTS:
// - Check if room pointer is not NULL
// - Add to exits map: exits[direction] = room
//
void Room::addExit(const std::string& direction, Room* room) {
    // TODO: Add exit to map
    if(room == NULL)return;
    exits[direction] = room;
}


// TODO: Implement getExit
// HINTS:
// - Look up direction in exits map
// - Use exits.find(direction)
// - If not found, return NULL
//
Room* Room::getExit(const std::string& direction) const {
    // TODO: Look up and return exit
    //loop up direction in exits map
    map<string, Room*>::const_iterator it = exits.find(direction);
    //if not found, return NULL
    if(it == exits.end()) return NULL;

    return it->second;  
}


// TODO: Implement hasExit
// HINTS:
// - Check if direction exists in exits map
bool Room::hasExit(const std::string& direction) const {
    // TODO: Check if exit exists
    //check if direction exits in exits map
    return exits.find(direction) != exits.end();  
}


// TODO: Implement clearMonster
// HINTS:
// - If monster exists, delete it
// - Set monster pointer to NULL
//
void Room::clearMonster() {
    // TODO: Delete and clear monster
    if(monster != NULL){
        delete monster;
        monster = NULL;
    }
}


// TODO: Implement addItem
// HINTS:
// - Check if item pointer is not NULL
// - Add to items vector using push_back()
//
void Room::addItem(Item* item) {
    // TODO: Add item to room
    if(item == NULL)return;
    items.push_back(item);
}


// TODO: Implement removeItem
// HINTS:
// - Search items vector for item by name (case-insensitive)
// - If found: erase from vector (DON'T delete - ownership transferred)
//
void Room::removeItem(const std::string& item_name) {
    // TODO: Find and remove item from room
    //have to search items vector for item by name 
    //case insensitive so I have to use lowerfunciton
    string target = toLower(item_name);
    for(int i = 0; i < items.size(); i++){
        string curritem = toLower(items[i]->getName());

        if (curritem == target) {
            // DON'T delete – ownership will be transferred!
            items.erase(items.begin() + i);
            return;
        }
    }

}


// TODO: Implement displayItems
// HINTS:
// - Print each item's name in a list
// - Format: "  - ItemName"
//
void Room::displayItems() const {
    // TODO: Display all items in room
    // iterate through item vectors to print out all items in a list
    for(int i = 0; i < items.size(); i++){
        cout << "  - " << items[i]->getName() << "\n";
    }

    
}


// TODO: Implement getItem
// HINTS:
// - Search items vector for item by name (case-insensitive)
// - If found, return pointer to item
// - If not found, return NULL
//
Item* Room::getItem(const std::string& item_name) {
    // TODO: Find and return item pointer
    //search items vector for item by name using lowerfunction
    string target = toLower(item_name);
    // Search through items vector
    for(int i = 0; i < items.size(); i++){
        string curritem = toLower(items[i]->getName());

        if (curritem == target) {
            //if found, return pointer to item
            return items[i];   
        }
    }
    return NULL;  // return null if not found
}
