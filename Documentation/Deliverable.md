# ECE 312 - Lab 6 Write-Up

**Name:** _____Jaeyeon Won_______  
**EID:** _______JW57786_______  
**Date:** _______5th December, 2025______

---

## 1. Design Decisions (3-4 sentences)

Briefly describe your key design choices and rationale:

- **Overall implementations:** How did you make use of object-oriented concepts in your decision?  Specifically, how did you use inheritance and polymorphism (if you did) and how did it help or complicate the design over using a language like C?  Draw a diagram showing the classes you used and their relationships to each other (subclass to superclass relationships specifically.)<br> 
    I made use of object-oriented concepts in my decision by using an object-oriented heirachy so base classes could use shared behavior usefully while specific features were overriden in subclasses. I used inheritance and polymorphism in characers.cpp and items.cpp. It made it a lot easier to add new monster or item types for extra credits without rewriting every game logic. It helped better to understand and make the codes cleaner than C-style design as each class controlled its own behavior and kept the inherited features.<br> 
Character
   ├── Player
   └── Monster
          ├── Goblin
          ├── Skeleton
          ├── Ghost
          ├── Troll
          ├── Wizard
          └── Dragon

Item
   ├── Weapon
   ├── Armor
   ├── Consumable
   ├── Scroll
   ├── Key
   └── GoldItem

- **Memory management:** What strategy did you use to avoid leaks? Any particular challenges?<br>
    The strategy that I used to avoid leaks is that I used destructors clearly to free everything to prevent possible memory leaks as I built the project gradually. I also tried to follow through ownership rules in rooms, monsters, and the players so I did every methods I can do to avoid leaks. There was no particular challenge in terms of memory leakage.


---


## 2. Testing & Debugging (2-3 sentences)

Describe your testing process and any major bugs you encountered:

- **Testing approach:** What was your strategy beyond running `make test`?<br>
    Beyong running 'make test', I spend lots of time trying and testing with weird and different situations and edge cases. For example, I tried to use the same item twice, enter the room without the keys, press undefined order to the game, and use scroll items not during fighting monsters. I also didn't use valgrind not only for the last part after implementing all the cpp files, but during each time when I make some changes to make sure that no memory is leaked. It was good to see new implementation working well and observe gradual improvement of the game. 

- **Most difficult bug:** What was the hardest bug to find/fix and how did you solve it?<br>
    The hardest bug to find/fix was during implementing the Ghost's 50% avoidance mechanic. The problem was that even when the ghost avoided the attack, the combat loop continued as the damage was applied, which resulted in inconsistent HP updates and confused the output of the combat. I solved it by restructing the attack branch and adding continue to skip the rest of the attack block so that a successful avoidance cleanly end the player's turn.


---

## 3. Implementation Challenges (2-3 sentences)

Which TODOs were most challenging and why?

1. **Hardest TODO:**<br> 
    I think that the hardest TODO was building shop system as the part of the extra credit.  The other extra credits are relatively easier because there were already the formats built that I can utilize to add more monsters, items, and characters. The shop system has selling, buying, checking itmes, updating player's gold, and handling inventory changes. 

2. **Most time-consuming:**<br> 
    Most time-consuming task was building codes for initializeWorld(). In this function, I had to place every room, monster, and items, and make sure that lock systems and connection between the rooms work well. So it took the most time.


3. **Most interesting:**<br>
    Most interesting todo was building the program that allows users to pick their own characters. Since the stats is different depending on the characters each player chooses, so it was fun to make my game like an actual RPG game. Especially, with the help of AI(GPT), it was fun to make ascii draw for characters.


---


## 4. Reflection (1-2 sentences)

What was the most valuable lesson from this lab?<br>
    The most valuable lesson from this lab is that it was good to learn how important clear ownership rules and destructors are when dealing with allocated objects. Furthermore, it was a lot easier to make the program compared to C with the use of class.

---

## Submission Checklist

- [v] All functionality completed
- [v] `make test` passes with no failures
- [v] `make valgrind` shows no memory leaks
- [v] Game fully functional 
- [v] Code compiles without warnings (`-Wall -Wextra`)
- [v] This write-up completed
- [v] Optional Bonus attempted? (Yes/No): __Yes, 4 extensions (items, characters, players, shop)___