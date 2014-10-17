#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Attribute {
	int HP;
	int ATK;
	int DEF;
	float money;
	std::string name;
    char symbol;
	//Attribute(const Attribute& attr); // copy constructor
};




// The initial attribute of Player races
const Attribute HUMAN = {140, 20, 20, 0, "Human",'@'};//no special skills
const Attribute DWARF = {100, 20, 30, 0, "Dwarf",'@'};//gold is doubled in value
const Attribute ELF = {140, 30, 10, 0, "Elf",'@'};//negative potions have positive effect
const Attribute ORC = {180, 30, 25, 0, "Orc",'@'};//gold is worth half value

// The initial attribute of Enemy races
const Attribute VAMPIRE = {50, 25, 25, 1, "Vampire",'V'};//has life steal(transform damage dealt to health)
const Attribute WEREWOLF = {120, 30, 5, 1, "Werewolf",'W'};//has chance to critical strike(deals double damage)
const Attribute TROLL = {120, 25, 15, 1, "Troll",'T'};//has life regeneration
const Attribute GOBLIN = {70, 5, 10, 1, "Goblin",'N'};//steals money when attack(the money wont return to player after goblin is slained)
const Attribute PHOENIX = {50, 35, 25, 1, "Phoenix",'X'};//when deals damage to player, deals additional true damage(ignore defense))
const Attribute MERCHANT = {30, 70, 5, 4, "Merchant",'M'};
const Attribute DRAGON = {150, 20, 20, 6, "Dragon",'D'};//attack ignores defense, and attack increases by 15% everytime it attacks)

class Object {
	public: // ADD GETTER AND SETTER ??
	int index;
	char symbol;
    bool is_pc;
    bool is_npc;
	
	public:
    //Constructors:
	Object(int index, char symbol);
	Object();
    
    //Object methods:
    char get_symbol();
    bool get_npc();
    bool get_pc();
    
    //Abstract methods:
    virtual void money_copy(float money);
    virtual float get_print_money();
    virtual int getmoney();
    virtual int get_attack();
    virtual int get_defense();
    virtual int get_health();
    virtual int get_type();
    virtual std::string get_item_name();
    virtual std::string get_username();
    virtual Attribute get_attribute();
    virtual void attribute_change(char field, int amount);
    //Destructor:
    //~Object();
};


class Character: public Object {
	public:
	Attribute attr;
	Character();
	Character(int index, std::string name);
	Attribute checkRace(std::string name);
    
    //overwritting abstract method:
    int get_attack();
    int get_defense();
    int get_health();
    int getmoney();
    void money_copy(float money);
    Attribute get_attribute();
    void attribute_change(char field, int amount);
    
};

class PC: public Character {
public:
    std::string username;
    // Constructor:
    
	PC(int index, std::string name, std::string username);
    std::string get_username();
    float get_print_money();
};

class NPC: public Character {
	public:
	NPC(int index, std::string name);

};



class Potion: public Object {
	public: 
	int type; // only 6 types of potion
	Potion(int index, int type);
    std::string potion_name;
    //Method:
    std::string type_name(int type);
    std::string get_item_name();
    int get_type();
};

/*class Weapon: public Potion{
public:
    Weapon(int index, int type);
};*/

class Gold: public Object {
	public:
	int value;
	Gold(int index, int type);
	// Gold can be in several types of piles: normal (value 1), 
	// small horde (value 2), merchant hoard (value 4), dragon hoard (value 6).
    
    int getmoney();
};

class Stair: public Object {
	public:
	Stair(int index);
};

class Wall_row: public Object {
	public:
	Wall_row(int index);
};

class Wall_col: public Object {
	public:
	Wall_col(int index);
};

class Door: public Object {
	public:
	Door(int index);
};

class Path: public Object {
	public:
	Path(int index);
};

class Tile: public Object {
	public:
	Tile(int index);
};

class Inventory: public Object {
    public:
    std::vector<Object*> inventory_vec;
    Inventory();
    void inventory_push_back(Object* item);
    std::string get_invent_info();
    Object* use_inventory(int pos);
};


















#endif


