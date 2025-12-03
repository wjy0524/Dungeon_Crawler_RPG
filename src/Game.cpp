#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

//lower case function
// this is a helper func to convert a string to lowercase for case insensitive comparison
static string toLower(const string& s){
    string lower = s;
    for (size_t i = 0; i < lower.length(); i++) {
        if (lower[i] >= 'A' && lower[i] <= 'Z') {
            lower[i] = lower[i] + ('a' - 'A');
        }
    }
    return lower;
}

// TODO: Implement Game constructor
Game::Game() : player(NULL), current_room(NULL), 
               game_over(false), victory(false) {
}


// TODO: Implement Game destructor
Game::~Game() {
    // TODO: Clean up player and all rooms
    if(player != NULL){
        delete player;
        player = NULL;
    }
    //has to clean up all rooms
    for(map<string, Room*>::iterator it = world.begin(); it != world.end(); ++it){
        //delete every room
        delete it->second;
    }
    //clear world
    world.clear();
  
}


// TODO: Implement initializeWorld
// HINTS:
// - Create all rooms with new
// - Add each room to world using addRoom()
// - Connect rooms using connectRooms()
// - Add monsters to appropriate rooms using room->setMonster()
// - Add items to rooms using room->addItem()
// - Set current_room to starting room (entrance)
//
// SUGGESTED WORLD LAYOUT:
//                [Throne Room]
//                     |
//     [Armory] - [Hallway] - [Treasury] - [vault]
//                     |
//    [Barracks] - [Library]
//                     |
//                [Catacombs]

//                 [Entrance] to [hallway] (it's like a teleportation)
//
// MONSTERS:
// - Hallway: Goblin
// - Armory: Skeleton
// - Treasury: Ghost
// - Throne Room: Dragon (boss!)
// - Library: Ghost
// - Barracks: Troll
// - Catacombs: Skeleton
// - Vault: Wizard
//
// ITEMS:
// - Entrance: Small Potion
// - Armory: Iron Sword, Chain Mail
// - Treasury: Health Potion
// - Library: Fire Scroll
// - Catacombs: Silver Key
// - Treasury: Golden Key
// - Vault: Gold Pile, Jeweled Cup
// - Barracks: Steel Axe
//
void Game::initializeWorld() {
    // TODO: Create rooms
    // Room* entrance = new Room("Dungeon Entrance", "A dark stone corridor...");
    Room* entrance = new Room("Entrance", "A cold draft crawls along the stone floor as faint echoes fade into darkness.");
    Room* hallway = new Room("Hallway", "Dust swirls in the narrow corridor, disturbed only by your hesitant footsteps.");
    Room* armory = new Room("Armory", "Abandoned racks hold rusted weapons, each telling a forgotten battle’s story.");
    Room* treasury = new Room("Treasury", "Shattered chests spill tarnished coins across the cracked marble tiles.");
    Room* throne = new Room("Throne Room", "A towering throne looms in silence, its presence heavy with an ancient authority.");
    Room* library = new Room("Library", "Ancient books rot on collapsing shelves. A faint whisper echoes between the pages.");
    Room* barracks = new Room("Barracks", "Broken beds and scattered armor pieces suggest a long-abandoned garrison.");
    Room* catacombs = new Room("Catacombs", "A labyrinth of burial chambers filled with eerie silence.");
    Room* vault = new Room("Vault", "Massive stone chests line the walls, glimmering with long-forgotten riches.");

    
    // TODO: Add rooms to world
    addRoom(entrance);
    addRoom(hallway);
    addRoom(armory);
    addRoom(treasury);
    addRoom(throne);
    addRoom(library);
    addRoom(barracks);
    addRoom(catacombs);
    addRoom(vault);
    
    // TODO: Connect rooms bidirectionally
    connectRooms("Entrance", "north", "Hallway");
    connectRooms("Hallway", "west", "Armory");
    connectRooms("Hallway", "east", "Treasury");
    connectRooms("Hallway", "north", "Throne Room");
    connectRooms("Hallway", "south", "Library");
    connectRooms("Library", "south", "Catacombs");
    connectRooms("Library", "west", "Barracks");
    connectRooms("Treasury", "east", "Vault");
    
    // TODO: Add monsters
    world["Hallway"]->setMonster(new Goblin());
    world["Armory"]->setMonster(new Skeleton());
    world["Treasury"]->setMonster(new Ghost());
    world["Throne Room"]->setMonster(new Dragon());
    world["Library"]->setMonster(new Ghost());
    world["Barracks"]->setMonster(new Troll());
    world["Catacombs"]->setMonster(new Skeleton());
    world["Vault"]->setMonster(new Wizard());

    
    // TODO: Add items
    world["Entrance"]->addItem(new Consumable("Small Potion", "A faintly glowing vial of weak healing brew.", 10));
    world["Armory"]->addItem(new Weapon("Iron Sword", "A worn blade with chipped edges but steady performance.", 5));
    world["Armory"]->addItem(new Armor("Chain Mail", "Tightly linked metal rings offering dependable defense.", 3));
    world["Treasury"]->addItem(new Consumable("Health Potion", "A crimson remedy said to mend deeper wounds that restores 20 HP.", 20));
    world["Library"]->addItem(new Scroll("Fire Scroll", "A scroll that unleashes a burst of flame.", 15));
    world["Catacombs"]->addItem(new Key("Silver Key", "Opens a mysterious locked vault."));
    world["Treasury"]->addItem(new Key("Golden Key", "Said to open the throne chamber."));
    world["Vault"]->addItem(new GoldItem("Gold Pile", "A large stack of ancient coins.", 50));
    world["Vault"]->addItem(new GoldItem("Jeweled Cup", "A valuable artifact.", 30));
    world["Barracks"]->addItem(new Weapon("Steel Axe", "A heavy axe used by ancient soldiers.", 7));
    //you need silver key to unlock the vault
    //you need golden key to unlock the throne room
    world["Vault"]->lockRoom("Silver Key");
    world["Throne Room"]->lockRoom("Golden Key");

    
    // TODO: Set starting room
    current_room = entrance;
    current_room->markVisited();
}


// TODO: Implement createStartingInventory
// HINTS:
// - Give player starting weapon: Rusty Dagger (damage +2)
// - Give player starting food: Bread (heals 5 HP)
// - Use: player->addItem(new Weapon(...))
//
void Game::createStartingInventory() {
    // TODO: Give player starting items
    player->addItem(new Weapon("Rusty Dagger", "An old, chipped dagger.", 2));
    player->addItem(new Consumable("Bread", "Dry but edible. Restores a bit of HP.", 5));

}


// TODO: Implement addRoom
// HINTS:
// - Check if room pointer is not NULL
// - Add to world map using room's name as key
// - Use: world[room->getName()] = room
//
void Game::addRoom(Room* room) {
    // TODO: Add room to world map
    if(room == NULL) return;
    world[room->getName()] = room;
}


// TODO: Implement connectRooms
// HINTS:
// - Look up both rooms in world map
// - If both exist:
//   - Add forward direction: room1->addExit(direction, room2)
//   - Determine reverse direction:
//     * north ↔ south
//     * east ↔ west
//   - Add reverse direction: room2->addExit(reverse, room1)
//
void Game::connectRooms(const std::string& room1_name, const std::string& direction,
                       const std::string& room2_name) {
    // TODO: Connect rooms bidirectionally
    //have to look up boths rooms in world map
    map<string, Room*>::iterator it1 = world.find(room1_name);
    map<string, Room*>::iterator it2 = world.find(room2_name);
    //check if both rooms exist
    //if one room doesn't exist, just return
    if(it1 == world.end() || it2 == world.end()){
        return;
    }

    Room* room1 = it1->second;
    Room* room2 = it2->second;

    //add forward direction
    room1->addExit(direction, room2);

    //reverse the direction
    string reverse;
    if(direction == "north") reverse = "south";
    else if(direction == "south") reverse = "north";
    else if(direction == "east") reverse = "west";
    else if(direction == "west") reverse = "east";
    
    //add reverse direction if revese exits
    if(!reverse.empty()){
         room2->addExit(reverse, room1);
    }
    

}


// TODO: Implement run - main game loop
// HINTS:
// - Print welcome message and game title
// - Get player name from input 
// - Create player: player
// - Call initializeWorld()
// - Call createStartingInventory()
// - Display starting room
// - Mark starting room as visited
// - Main loop: 
//   - Print prompt: "> "
//   - Get command (use std::getline)
//   - Convert to lowercase (use std::transform)
//   - Call processCommand()
//   - Check victory condition
//   - Check defeat condition (player dead)
//
void Game::run() {
    // TODO: Implement main game loop
    cout << "====================================\n";
    cout << "    Welcome to DUNGEON ADVENTURE    \n";
    cout << "====================================\n\n";

    string name;
    cout << "Enter your name: ";
    getline(cin, name);
    //if name is empty, name automatically consiered as Hero
    if (name.empty()) name = "Hero";

    //user is able to choose the characters
    //but the stats of the characters are the same for simplicity, but just different names and different ascii arts
    // character selection
    cout << "Choose your character:\n";
    cout << "1. Warrior\n";
    cout << "2. Mage\n";
    cout << "3. Archer\n";
    cout << "4. Rogue\n";
    cout << "> ";
    string choice;
    getline(cin, choice);
    string type = "Warrior"; // default type
    if(choice == "2") type = "Mage";
    else if(choice == "3") type = "Archer";
    else if(choice == "4") type = "Rogue";

    player = new Player(name, type);

    initializeWorld();
    createStartingInventory();

    look();

    //main game loop
    while (!game_over){
        // player dead
        if(!player->isAlive()){
            cout << "\nYou collapse... your journey ends here.\n";
            game_over = true;
            break;
        }

        // player victory
        if(victory){
            cout << "\nYou have conquered the dungeon! Victory!\n";
            game_over = true;
            break;
        }

        // getting input from the user
        cout << "\n> ";
        string line;
        if (!getline(cin, line)) break;
        if (line.empty()) continue;
        // change the input line into lowercase
        line = toLower(line);
        //Call processCommand()
        processCommand(line);
    }

    cout << "\nGame Over.\n";
}


// TODO: Implement processCommand
// HINTS:
// - Parse command into verb and object
// - Extract first word as verb
// - Rest of line is object
// - Dispatch to appropriate method based on verb:
//   * "go" or "move" → move(object)
//   * "look" or "l" → look()
//   * "attack" or "fight" → attack()
//   * "pickup" or "get" or "take" → pickupItem(object)
//   * "inventory" or "i" → inventory()
//   * "use" → useItem(object)
//   * "equip" or "e" → equip(object)
//   * "stats" → player->displayStats()
//   * "help" or "h" or "?" → help()
//   * "quit" or "exit" → set game_over to true
//
void Game::processCommand(const std::string& command) {
    // TODO: Parse and dispatch command
    istringstream iss(command);

    //extract the first word as verb
    string verb;
    iss >> verb;
    //rest of line is object
    string object;
    getline(iss, object);

    //have to remove the space
    //for example if the user inputs "Go    north"
    //then after reading the object, it will read      north, which make the problem
    if (!object.empty()) {
        //I used find_first_not_of(" \t") to find the first character that is NOT a space or a tab. Then I use substr() to cut the string from that point,
        // leaving only the actual word.
        //with the help of AI, I learned the functions find_first_not_of
        size_t pos = object.find_first_not_of(" \t");
        if (pos != string::npos)
            object = object.substr(pos);
        else
            object.clear();
    }

    if(verb == "go" || verb == "move"){
        if(object.empty()){
            cout << "Which way do you want to go?\n";
        }else{
            move(object);
        }
    }else if (verb == "look" || verb == "l"){
        look();
    }else if(verb == "attack" || verb == "fight"){
        attack();
    }else if(verb == "pickup" || verb == "take" || verb == "get"){
        if(object.empty()){
            cout << "Tell me what to pick up.\n";
        }else{
            pickupItem(object);
        }
    }else if(verb == "inventory" || verb == "i"){
        inventory();
    }else if(verb == "use"){
        if(object.empty()){
            cout << "Use which item?\n";
        }else{
            useItem(object);
        }
    }else if(verb == "equip" || verb == "e"){
        if(object.empty()){
            cout << "What would you like to equip?\n";
        }else{
            equip(object);
        }
    }else if(verb == "stats"){
        player->displayStats();
    }else if(verb == "shop"){ // added shop command for extra credit extension
        openShop();
    }else if(verb == "help" || verb == "h" || verb == "?"){
        help();
    }else if(verb == "quit" || verb == "exit"){
        game_over = true;
    }else{
        cout << "Wrong command. Please type the correct command!\n";
    }
}



// TODO: Implement move
// HINTS:
// - Check if monster blocks path (current_room->hasMonster())
// - If blocked, print message and return
// - Get exit in specified direction
// - If exit exists:
//   - Update current_room
//   - Display new room
//   - Mark as visited
// - Otherwise print error: "You can't go that way!"
//
void Game::move(const std::string& direction) {
    // TODO: Move to adjacent room
    //check if currentroom pointer is NULL
    if(current_room == NULL) return;

    //check if monster blocks path
    //you can only move to the other room if you defeated the monster in the current room
    if(current_room->hasMonster()){
        cout << "A monster blocks your way. Defeat it before you can proceed.\n";
        return;
    }

    //get exit in specified direction
    Room* nxt = current_room->getExit(direction);
    if(nxt == NULL){
        cout << "You can't go that way.\n";
        return;
    }
    // check if the room is locked
    if(nxt->isLocked()){
        string key = nxt->getRequiredKey();
        if(!player->hasItem(key)){
            cout << "The " << nxt->getName() << " is locked. You need the " << key << " to enter.\n";
            return;
        }
        cout << "You use the " << key << " to unlock the door!\n";
        nxt->unlockRoom();
    }
    //update current_room
    current_room = nxt;
    look();
    current_room->markVisited();
}


// TODO: Implement look
// HINTS:
// - Simply display current room
//
void Game::look() {
    // TODO: Display current room
    //check if current room pointer is NULL
    if(current_room == NULL) return;
    current_room->display();
}


// TODO: Implement attack
// HINTS:
// - Check if monster in room
// - If no monster, print message and return
// - If monster present, call combat()
//
void Game::attack() {
    // TODO: Attack monster in room
    //check if current room pointer is NULL
    if(current_room == NULL) return;

    //check if monster in room
    if(!current_room->hasMonster()){
        std::cout << "There’s no monster here to fight.\n";
        return;
    }

    // Get the monster pointer
    Monster* monster = current_room->getMonster();
    //if the monsetr pointer is NULL
    if (monster == NULL) {
        cout << "There’s no monster here to fight.\n";
        return;
    }

    // call combat
    combat(monster);
}


// TODO: Implement combat
// HINTS:
// - Print "=== COMBAT BEGINS ==="
// - Combat loop: while both player and monster are alive
//   - Prompt for player action: attack/use <item>/flee
//   - If attack:
//     * Calculate player damage
//     * Monster takes damage
//     * If monster dead:
//       - Print victory
//       - Player gains exp and gold
//       - Get loot from monster
//       - Add loot to current room
//       - Check if Dragon 
//       - Clear monster from room
//       - Break from loop
//   - If use:
//     * Extract item name from command
//     * Call player->useItem()
//   - If flee:
//     * Print message and break
//   - Monster turn (if alive):
//     * Print attack message
//     * Calculate monster damage
//     * Player takes damage
// - Print "=== COMBAT ENDS ==="
//
void Game::combat(Monster* monster) {
    // TODO: Implement turn-based combat
    //check monster pointer is NULL
    if(monster == NULL) return;

    //
    cout << "\n=== COMBAT BEGINS ===\n";

    string command;
    // Fight until one side is down or the player flees
    while(player->isAlive() && monster->isAlive()){
        cout << "\n";
        player->displayStatus();
        cout << "  vs  ";
        monster->displayStatus();
        cout << "\n";
        //print out the promt regarding the user's options
        cout << "Choose an action (attack / use <item> / flee): ";
        //if command is not input break
        if (!getline(cin, command)) break;

        //change into the lower case
        string cmd = toLower(command);

        // attack
        if(cmd == "attack" || cmd == "a"){
            //Ghost avoidance ability
            //use dynamic_cast to check if the monster is a Ghost
            //if casting succeeds, it returns a valid Ghost pointer, otherwise returns NULL
            //I learned the usage of dynamic_cast from AI <chat gpt>
            if (dynamic_cast<Ghost*>(monster) != NULL) {
                if (rand() % 2 == 0) {
                    cout << "\nYour attack passes through the ghost — it avoids your attack!\n";
                    if(monster->isAlive() && player->isAlive()){
                        cout << "\n" << monster->getAttackMessage() << "\n";
                        int monsterdamage = monster->calculateDamage();
                        player->takeDamage(monsterdamage);
                    }
                    continue;  //skip the rest of the attack turn and go to another while loop
                }
            }

            int damage = player->calculateDamage();
            cout << "\nYou strike the " << monster->getName() << " for " << damage << " damage!\n";
            monster->takeDamage(damage);
            //if the monster is dead
            if(!monster->isAlive()){
                cout << "You defeated the " << monster->getName() << "!\n";

                // reward experience and gold
                player->gainExperience(monster->getExperienceReward());
                player->addGold(monster->getGoldReward());

                // loot
                vector<Item*> loot = monster->dropLoot();
                for(vector<Item*>::iterator it = loot.begin(); it != loot.end(); ++it){
                    current_room->addItem(*it);
                }

                // check if it is a dragon
                if(monster->getName() == "Dragon"){
                    //yay you conquered the dungeon
                    cout << "The Dragon falls! You have conquered the dungeon.\n";
                    victory = true;
                }

                current_room->clearMonster();
                break;
            }
        // Item
        //checking if the command starts with "use" from index 0
        //studied the use of rfind and find_first_not_of from AI <chat gpt>
        }else if(cmd.rfind("use", 0) == 0){
            string item_name = cmd.substr(3); //extract item name after use
            // same with above, I have to remove all the spaces to prevent the error
            size_t pos = item_name.find_first_not_of(" \t");
            if(pos != string::npos){
                item_name = item_name.substr(pos);
            }else{
                item_name.clear();
            }

            if(item_name.empty()){
                cout << "What item do you want to use?\n";
                continue;
            }

            Item* item = player->getItem(item_name);
            if(item == NULL){
                cout << "You don't have an item called \"" << item_name << "\".\n";
                continue;
            }
            if(item->getType() == "Scroll"){
                Scroll* scr = static_cast<Scroll*>(item);

                if(scr->isUsed()){
                    cout << scr->getName() << " has already been used!\n";
                    continue;
                }

                scr->use();  // prints message

                int dmg = scr->getDamageAmount();
                cout << "The " << scr->getName() << " hits the " << monster->getName() << " for " << dmg << " magic damage!\n";

                monster->takeDamage(dmg);

                // delete from inventory after use
                player->removeItem(scr->getName());

                // check death
                if(!monster->isAlive()){
                    cout << "You defeated the " << monster->getName() << "!\n";
                    player->gainExperience(monster->getExperienceReward());
                    player->addGold(monster->getGoldReward());

                    vector<Item*> loot = monster->dropLoot();
                    for(size_t i = 0; i < loot.size(); i++){
                        current_room->addItem(loot[i]);
                    }

                    if(monster->getName() == "Dragon"){
                        cout << "The Dragon falls! You have conquered the dungeon.\n";
                        victory = true;
                    }

                    current_room->clearMonster();
                    break;
                }

                continue; // skip monster's turn
            }

    // 2) otherwise use potion / regular item
            player->useItem(item_name);
        //flee
        }else if(cmd == "flee"){
            cout << "You run away from the fight!\n";
            break;
        }else{
            cout << "That action isn’t recognized.\n";
            continue;
        }

        // Monster's trun
        if(monster->isAlive() && player->isAlive()){
            cout << "\n" << monster->getAttackMessage() << "\n";
            int monsterdamage = monster->calculateDamage();
            player->takeDamage(monsterdamage);
        }
    }

    cout << "=== COMBAT ENDS ===\n";
}


// TODO: Implement pickupItem
// HINTS:
// - Get item from current room
// - If exists:
//   - Add to player inventory
//   - Remove from room (ownership transfer!)
// - Otherwise print error
//
void Game::pickupItem(const std::string& item_name) {
    // TODO: Pick up item from room
    //check if the current room pointer is NULL
    if(current_room == NULL) return;
    //get item from current room
    Item* item = current_room->getItem(item_name);
    if(item == NULL){
        cout << "There is no \"" << item_name << "\" here.\n";
        return;
    }

    //add to player inventory
    player->addItem(item);
    cout << "You picked up " << item->getName() << ".\n";
    //remove from room
    current_room->removeItem(item_name);

}


// TODO: Implement inventory
//
void Game::inventory() {
    // TODO: Display player inventory
    player->displayInventory();
}


// TODO: Implement useItem
// HINTS:
// - Call player->useItem(item_name)
//
void Game::useItem(const std::string& item_name) {
    // TODO: Use item from inventory
    player->useItem(item_name);
    
}


// TODO: Implement equip
// HINTS:
// - Get item from player inventory
// - Check if item exists
// - Check item type:
//   - If "Weapon": call player->equipWeapon()
//   - If "Armor": call player->equipArmor()
//   - Otherwise: print error (can't equip consumables)
//
void Game::equip(const std::string& item_name) {
    // TODO: Equip weapon or armor
    Item* item = player->getItem(item_name);

    if(item == NULL){
        cout << "You don't have \"" << item_name << "\".\n";
        return;
    }

    string itemtype = item->getType();

    if(itemtype == "Weapon"){
        player->equipWeapon(item_name);
    }else if (itemtype == "Armor"){
        player->equipArmor(item_name);
    }else{
        cout << "You can't equip that.\n";
    }
}


// TODO: Implement help
// HINTS:
// - Print all available commands with descriptions
// - Format nicely with headers
// - Commands:
//   * go <direction> - Move
//   * look - Look around
//   * attack - Attack monster
//   * pickup <item> - Pick up item
//   * inventory - Show inventory
//   * use <item> - Use consumable
//   * equip <item> - Equip weapon/armor
//   * stats - Show character stats
//   * help - Show this help
//   * quit - Exit game
//
void Game::help() {
    // TODO: Display help message
    cout << "\n===== Available Commands =====\n";
    cout << "  go <direction>   - Move to another room (north, south, east, west)\n";
    cout << "  look             - Look around the room\n";
    cout << "  attack           - Attack the current monster\n";
    cout << "  pickup <item>    - Pick up an item on the ground\n";
    cout << "  inventory        - Show your inventory\n";
    cout << "  use <item>       - Use a consumable/scroll item\n";
    cout << "  equip <item>     - Equip a weapon/armor\n";
    cout << "  shop             - Open the dungeon shop to buy/sell items\n";
    cout << "  stats            - Show your character stats\n";
    cout << "  help             - Show this help menu\n";
    cout << "  quit             - Exit the game\n";
    cout << "===============================\n";
}


//extra credit extension
//openshop functions where players can buy and sell items
void Game::openShop(){
    cout << "\n========== SHOP ==========\n";
    //ascii art for the shopkeeper generated with the help of AI <chat gpt>
    cout << "        ╭━★\n";
    cout << "     ( ͡° ͜ʖ ͡°)     Welcome to the Dungeon Shop!\n";
    cout << "      /|💰        I've got wares if you've got coin.\n";
    cout << "      / \\\n"; 
    cout << "\n";
    cout << "You currently have " << player->getGold() << " gold.\n";
    cout << "You can buy and sell items here.\n";
    cout << "Type 'buy' to purchase, 'sell' to sell items, or 'exit' to leave.\n";

    while(true){
        cout << "\nShop> ";
        string line;
        if (!getline(cin, line)) break;
        if (line.empty()) continue;

        string cmd = toLower(line);

        if(cmd == "buy"){
            shopBuyMenu();
        }else if(cmd == "sell"){
            shopSellMenu();
        }else if(cmd == "exit"){
            cout << "Thank you for visiting the shop!\n";
            break;
        }else{
            cout << "Invalid command. Please type 'buy', 'sell', or 'exit'.\n";
        }
    }

}

void Game::shopBuyMenu(){
    cout << "\n--- Buy Menu ---\n";
    cout << "You currently have " << player->getGold() << " gold.\n";
    cout << "Available items for purchase:\n";
    cout << "1. Health Potion (Restores 20 HP) - 10 Gold\n";
    cout << "2. Iron Sword (+5 Damage) - 25 Gold\n";
    cout << "3. Leather Armor (+3 Armor) - 20 Gold\n";
    cout << "4. Magic Scroll (+100 Damage) - 40 Gold\n";
    cout << "5. Exit\n";

    while(true){
        cout << "\nBuy> ";
        string choice;
        getline(cin, choice);
        if(choice == "1"){
            if(player->getGold() < 10){ 
                cout << "Not enough gold!\n"; 
                continue; 
            }
            player->spendGold(10);
            player->addItem(new Consumable("Small Potion", "Restores 20 HP", 20));
            cout << "Purchased Small Potion!\n";
        }else if(choice == "2"){
            if(player->getGold() < 25){ 
                cout << "Not enough gold!\n";
                continue; 
            }
            player->spendGold(25);
            player->addItem(new Weapon("Iron Sword", "A sturdy iron blade", 5));
            cout << "Purchased Iron Sword!\n";
        }else if(choice == "3"){
            if(player->getGold() < 20){
                cout << "Not enough gold!\n";
                continue; 
            }
            player->spendGold(20);
            player->addItem(new Armor("Leather Armor", "Basic protection", 3));
            cout << "Purchased Leather Armor!\n";
        }else if(choice == "4"){
            if(player->getGold() < 40){ 
                cout << "Not enough gold!\n"; 
                continue; 
            }
            player->spendGold(40);
            player->addItem(new Scroll("Magic Scroll", "Deals strong magic damage", 100));
            cout << "Purchased Magic Scroll!\n";
        }else if(choice == "5"){
            cout << "Returning to shop...\n";
            return;
        }else{
            cout << "Invalid choice.\n";
        }
    }        
}

void Game::shopSellMenu(){
    cout << "\n--- Sell Menu ---\n";
    cout << "You currently have " << player->getGold() << " gold.\n";
    cout << "Your Inventory:\n";
    player->displayInventory();
    cout << "Type the name of the item to sell or 'exit' to leave.\n";

    while(true){
        cout << "\nSell> ";
        string item_name;
        getline(cin, item_name);
        if(item_name == "exit"){
            cout << "Returning to shop...\n";
            return;
        }

        Item* item = player->getItem(item_name);
        if(item == NULL){
            cout << "You don't have that item.\n";
            continue;
        }

        // Every item sells for its value
        int sell_price = item->getValue();

        cout << "Sold " << item->getName() << " for " << sell_price << " gold.\n";

        player->addGold(sell_price);
        player->removeItem(item->getName());

        
    }
}