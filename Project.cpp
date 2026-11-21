/*********************************************
Finn Bryan
Project
Date Completed: October 4, 2026
Description: Project.
Version: 1.0
*********************************************/


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

int MAP_SIZE = 5;

class Move{ 

    public:
    string name;
    string descriptor;
    int damage;
    int hitNumber;

};

class Player{

    public:
    string name;
    int hp;
    int level;
    int room;
    string inventory[20];


};

class Enemy{

    public:
    string name;
    int hp;
    int type;
    string art;


    Enemy()
    {
        name = "";
        hp = 0;
        type = 0;
    }

    Enemy(string n, int h, int t, string a)
    {
        name = n;
        hp = h;
        type = t;
        art = a;

    }

};

class Room{

    public:
    int number;
    bool explored;
    string description;
    Enemy roomEnemy;
    int north;
    int east;
    int south;
    int west;

    Room()
    {
        number = 0;
        explored = false;
        description = "";

        north = -1;
        east = -1;
        south = -1;
        west = -1;
    }

    Room(int num,
         string desc,
         int n,
         int e,
         int s,
         int w,
         Enemy enemy)
    {
        number = num;
        explored = false;
        description = desc;

        north = n;
        east = e;
        south = s;
        west = w;

        roomEnemy = enemy;
    }

};



void fight(Player&, Enemy&);
void roomStuff(Player&, Room&);
void movePlayer(Player& , Room[]);
void mapConstructor(Room rooms[]);
bool char_validation();
string playerChoice();
void mapDisplay(Room rooms[], Player& player);
Enemy getEnemy(string name);
void typrwrite(const string &text, int delayMs);


int main(){

    
    string input;
    Room rooms[25];
    mapConstructor(rooms);
    
    Player player;
    player.hp = 100;
    player.level = 1;
    player.room = 0;


    cout << "Please enter your Characters name: ";
    getline(cin, player.name);
    cout << "You awaken in a damp dungeon, you must escape. There is a door to the south" << endl;

    while(true){

        roomStuff(player, rooms[player.room]);

        input = playerChoice();

        if(input == "E")
            movePlayer(player, rooms);

        if(input == "L")
            cout << rooms[player.room].description << endl;






    }

}




void fight(Player& player, Enemy& enemy){

    while(player.hp > 0 && enemy.hp > 0)
    {
        cout << "\n" << player.name << " attacks "
             << enemy.name << "!\n";

        enemy.hp -= 10;

        if(enemy.hp <= 0)
        {
            cout << enemy.name << " was defeated!\n";
            break;
        }

        cout << enemy.name << " attacks back!\n";
        player.hp -= 5;

        cout << player.name << " HP: "
             << player.hp << endl;

        cout << enemy.name << " HP: "
             << enemy.hp << endl;
    }

    if(player.hp <= 0)
    {
        cout << "Game Over!\n";
        exit(0);
    }



}

void roomStuff(Player &player, Room &room){


    if(!room.explored)
    {
        cout << room.description << endl;

        if(room.roomEnemy.hp > 0)
        {
            cout << "A " << room.roomEnemy.name
                 << " appears!\n";

            fight(player, room.roomEnemy);

            if(player.hp <= 0)
            {
                cout << "Game over!";
                exit(0);
            }
        }

        room.explored = true;
    }


}


void mapConstructor(Room rooms[]){
    

    rooms[0] = Room(
    0,
    "A dark cave entrance.",
    -1, 1, -1, -1,
    Enemy()
    );

    rooms[1] = Room(
    1,
    "A narrow tunnel.",
    -1, 2, -1, 0,
    Enemy()
    );

    rooms[2] = Room(
    2,
    "The treasure room.",
    3, -1, -1, 1,
    Enemy()
    );

    rooms[3] = Room(
    3,
    "The stairwell.",
    -1, -1, 2, 1,
    Enemy()
    );

    rooms[0].roomEnemy = getEnemy("Big Spider");


}

void movePlayer(Player& player, Room rooms[])
{
    string choice;
    cout << "There are doors to the: ";
    if(rooms[player.room].north > -1)
        cout << "North\t";
    if(rooms[player.room].east > -1)
        cout << "East\t";
    if(rooms[player.room].south > -1)
        cout << "South\t";
    if(rooms[player.room].west > -1)
        cout << "West\t";
    cout << "\nDirection (N/E/S/W): ";
    getline(cin,choice);

    choice = toupper(choice[0]);

    switch(choice[0])
    {
        case 'N':
            if(rooms[player.room].north != -1)
                player.room = rooms[player.room].north;
            break;

        case 'E':
            if(rooms[player.room].east != -1)
                player.room = rooms[player.room].east;
            break;

        case 'S':
            if(rooms[player.room].south != -1)
                player.room = rooms[player.room].south;
            break;

        case 'W':
            if(rooms[player.room].west != -1)
                player.room = rooms[player.room].west;
            break;

        default:
            cout << "Invalid direction!\n";
    }
}

bool char_validation(string c)
{

    bool valid = true;

    if(!(isalpha(c[0])) || !(c.size() == 1)){
        valid = false;
    }
    if(!valid){
        cout << "invalid input" << endl;
        return false;
    }
    return true;

}

string playerChoice(){
    string choice;
    bool valid = false;

    while(!valid){
        cout << "Would you like to: " << endl;
        cout << "[L]ook around \t" << "[E]xplore further" << endl;

        getline(cin, choice);
        choice = toupper(choice[0]);

        if(choice =="E" || choice == "L")
            valid = true;
        
        if(!valid)
            cout << "Invalid Input" << endl;

    }

    return choice;

}

void mapDisplay(Room room[],Player& player){
    int mapSize = 25;
    cout << " --------------------- " << endl;

    for(int i = 0; i < 25; i++){
        cout << " | ";
        if(player.room == i)
            cout << "P";
        else if(room[i].explored == true)
            cout << "X";
        else
            cout << " ";
        if(((i + 1) % 5) == 0){
            cout << " | " << endl;
            cout << " --------------------- " << endl;
        }

        
    }

}

Enemy getEnemy(string name){
    if(name == "Big Spider"){
        return Enemy(
            "Big Spider",
            20,
            1,
            "       ___________\n"
            "  ____/           \\____\n"
            " /    |           |    \\ \n"
            "/  ___|___________|___  \\\n"
            "  /    |         |    \\ \n"
            " /   __|_________|__   \\ \n"
            "    /    |. . .|    \\ \n"
            "	      |_____| \n"


        );
    }
}

void typewrite(const string &text, int delayMs)
{
    for (char c : text)
    {
        cout << c;
        this_thread :: sleep_for(chrono::milliseconds(delayMs));
    }
};


