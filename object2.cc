#include "object2.h"

using namespace std;

/* Attribute(const Attribute& attr):
	HP(attr.HP), ATK(attr.ATK), DEF(attr.DEF), money(attr.money),
	name(attr.name) {}; */



Object::Object(int index, char symbol) {
	this->index = index;
	this->symbol = symbol;
};

Object::Object(): index(0), symbol(' ') {};

char Object::get_symbol(){
    return this->symbol;
}

bool Object::get_npc(){
    return this->is_npc;
}

bool Object::get_pc(){
    return this->is_pc;
}

string Object::get_username(){
    return "";
}

float Object::get_print_money(){
    return 0;
}

void Object::money_copy(float money){return;}

Attribute Object::get_attribute(){
    Attribute null = {0,0,0,0," ",' '};
    return null;
}

int Object::getmoney(){return -1;};
int Object::get_attack(){return -1;};
int Object::get_defense(){return -1;};
int Object::get_health(){return -1;};
int Object::get_type(){return -1;};
string Object::get_item_name(){return "";};

void Object::attribute_change(char field, int amount){return;}

Attribute Character::checkRace(string name) {
	if (name == "Human") {
		return HUMAN;
	} else if (name == "Elf") {
		return ELF;
	} else if (name == "Dwarf") {
		return DWARF;
	} else if (name == "Orc") {
		return ORC;
	} else if (name == "Vampire") {
		return VAMPIRE;
	} else if (name == "Werewolf") {
		return WEREWOLF;
	} else if (name == "Troll") {
		return TROLL;
	} else if (name == "Goblin") {
		return GOBLIN;
	} else if (name == "Phoenix") {
		return PHOENIX;
	} else if (name == "Merchant") {
		return MERCHANT;
	} else{
		return DRAGON;}
};

Character::Character() {
	this->symbol = ' ';
	this->index = 0;
	this->attr = HUMAN;
};

Character::Character(int index, string name) {
	Attribute s = checkRace(name);
	this->symbol = s.symbol;
	this->index = index;
    this->attr = s;
};


int Character::get_attack(){
    return this->attr.ATK;
}
int Character::get_defense(){
    return this->attr.DEF;
}
int Character::get_health(){
    return this->attr.HP;
}
int Character::getmoney(){
    return this->attr.money;
}

void Character::money_copy(float money){
    this->attr.money += money;
}


Attribute Character::get_attribute(){
    return this->attr;
}

void Character::attribute_change(char field, int amount){
    if (field == 'a') {
        this->attr.ATK += amount;
    }else
        if (field == 'd') {
        this->attr.DEF += amount;
    }else
        if (field == 'h') {
        this->attr.HP += amount;
    }else
        if (field == 'g'){
            if (this->attr.name == "Orc") {
                this->attr.money += (float(amount) * 0.5);
            }else if (this->attr.name == "Dwarf"){
                this->attr.money += 2 * amount;
            }else{
                this->attr.money += amount;}
    }
}
	
PC::PC(int index, string name, string username) {
    this->username = username;
	this->index = index;
    Attribute s = checkRace(name);
    this->symbol = s.symbol;
    this->attr = s;
    this->is_pc = true;
};

string PC::get_username(){
    return this->username;
}

float PC::get_print_money(){
    return this->attr.money;
}

NPC::NPC(int index, string name) {
	this->index = index;
    Attribute s = checkRace(name);
    this->symbol = s.symbol;
    this->attr = s;
    this->is_npc = true;
};

Potion::Potion(int index, int type):
	Object(index, 'P'), type(type), potion_name(type_name(type)){};

int Potion::get_type(){
    return this->type;
}

string Potion::type_name(int type){
    if (type == 0) {
        return "Health Potion";
    }else if(type == 1){
        return "Poision Potion";
    }else if(type == 2){
        return "Boost Attack Potion";
    }else if(type == 3){
        return "Wound Attack Potion";
    }else if(type == 4){
        return "Boost Defense Potion";
    }else{
        return "Wound Defense Potion";
    }
}

string Potion::get_item_name(){
    return this->potion_name;
}


/*Weapon::Weapon(int index int type):
Object(index,'&'){
    
    
}
};*/

Gold::Gold(int index, int type):
	Object(index, 'G') {
	if (type == 0) {
		// normal treasure:
		value = 1;
	} else if (type == 1) {
		// small horde:
		value = 2;
	} else if (type == 2) {
		// merchant horde:
		value = 4;
	} else if (type == 3) {
		// dragon horde: 
		value = 6;
	};
};

int Gold::getmoney(){
    return this->value;
}
	
Stair::Stair(int index):
	Object(index, '\\') {};
	
Wall_row::Wall_row(int index):
	Object(index, '-') {};

Wall_col::Wall_col(int index):
	Object(index, '|') {};


Door::Door(int index):
	Object(index, '+') {};


Path::Path(int index):
	Object(index, '#') {};


Tile::Tile(int index):
	Object(index, '.') {};
	
Inventory::Inventory(){
    vector<Object*> inventory_vec;
}


void Inventory::inventory_push_back(Object* item){
    this->inventory_vec.push_back(item);
    //inventory_info << "picked up " << item->get_item_name() << " and put it into inventory";
}

string Inventory::get_invent_info(){
    string inventory_info0 = "";
    if(this->inventory_vec.empty()){
        inventory_info0.append("Ur inventory is empty. ");
        return inventory_info0;
    }else{
        inventory_info0.append("Inventory list: \n");
        int size = int(this->inventory_vec.size());
        for (int i = 0; i < size; i++) {
            Object* item = this->inventory_vec.at(i);
            inventory_info0.append(item->get_item_name());
            inventory_info0.append("\n");
        }
    }
    return inventory_info0;
};




Object* Inventory::use_inventory(int pos){
    return this->inventory_vec.at(pos);
}








	

