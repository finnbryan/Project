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

using namespace std;

class Move{ 

    public:
    string name;
    string descriptor;
    int damage;
    int hitNumber;
    int dodge;
    int item;


};

class Player{

    public:
    string name;
    int hp;
    int level;
    int luck;
    int room;
    string inventory[20];


};

class Enemy{

    public:
    string name;
    int hp;
    int type;


    Enemy()
    {
        name = "";
        hp = 0;
        type = 0;
    }

    Enemy(string n, int h, int t)
    {
        name = n;
        hp = h;
        type = t;

    }

};


int items(int luck, bool drank)
{
    
    if(drank == true)
    {
        luck += 15;
        
    }
    return luck;
}



void weapondamage(int luck, int level, int &sword, int &axe, int &spear)
{
    int criticalhit;
    for(int i = 0; i < 1 + luck; i++)
    {
        criticalhit = rand() % 100;

        if(criticalhit == 10)
        {
            break;
        }
    }
        
        if(criticalhit == 10)
        {
            sword = 30 + level;
            axe = 40 + level;
            spear = 25 + level;
            cout << "You hit A Critical ATTACK!! " << endl;
        }
        else
        {
            sword = 10 + level;
            axe = 15 + level;
            spear = 5 + level;

        }
    }

    void choice(int luck, int level,Enemy& enemy, Player& player)
    {
        int sword, spear, axe, chance;
        weapondamage(luck,level, sword,axe,spear);
        char input;
        cout << "Will you [A]ttack/[D]odge/[F]lee/[I]tem/[R]isky Final attack: " << endl;
        cin >> input;
        
        

        if(input == 'A')
        {
            cout << "Choose one of your current weapon " << endl;;
            cout << "[E]xcalibur" << endl;
            cout << "[A]xe" << endl;
            cout << "[S]pear" << endl;

            cin >> input;

            if(input == 'A')
            {
                cout << player.name <<  " You swung A mean ATTACK at " << enemy.name << endl;
                enemy.hp -= axe;
                
            }
            else if(input == 'E')
            {
                cout << player.name << " Your slash made a bash on " << enemy.name  << endl;
                enemy.hp -= sword;
                
                
            }
            else if (input == 'S')
            {
                cout << player.name << " Careful you might poke a goblins eye out " << enemy.name << endl;
                enemy.hp -= spear;
                
            }
            else
            {
                cout << "Invalid weapon choice " << endl;
                
            }
            

        }
        if(input == 'D')
        {
            chance = rand() % 10;

            if(chance == 5)
            {
                cout << "you dodged and healed up" << endl;
                player.hp += 10;
                return;
            }
            else
            {
                cout << "you failed to dodge but landed a small counter attack" << endl;
                enemy.hp -= 5;
            }
        }

        if (input == 'F')
        {
            
        }

        if (input == 'I')
        {
            cout << "would you like to [B]uy some potions or [U]se your own or [E]xit" << endl;
            
            if(input == 'B')
            {
                cout << "[L]uck potion (1 Level)" << endl;

                if(input == 'L')
                {
                    cout << "youll be feeling extra lucky -merchant" << endl;
                    cout << "-1 level" << endl;
                    cout << "you drank the potion" << endl;
                }
            }
        }

        if (input == 'R')
        {
            chance = rand() % 50;

            if(chance == 8)
            {
                cout << "You Used up ALL your energy and vanquished the enemy" << endl;
                enemy.hp -= 200;
            }
        }
        cin.ignore();
        
        
    }










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
void enemyConstructor();
void mapConstructor(Room rooms[]);
bool char_validation();
string playerChoice();


int main(){
    
    srand(time(0));
    string input;
    Room rooms[4];
    enemyConstructor();
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

{
    while(player.hp > 0 && enemy.hp > 0)
    {
        choice(player.luck, player.level,enemy,player);

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

void enemyConstructor(){
    Enemy goblin("Goblin", 20, 1);

}

void mapConstructor(Room rooms[]){
    

    rooms[0] = Room(
    0,
    "A dark cave entrance.",
    -1, 1, -1, -1,
    Enemy("Goblin", 25, 1)
    );

    rooms[1] = Room(
    1,
    "A narrow tunnel.",
    -1, 2, -1, 0,
    Enemy("Skeleton", 40, 2)
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


}

void movePlayer(Player& player, Room rooms[])
{
    string choice;
    cout << "There are doors to the: ";
    if(rooms[player.room].north > 0)
        cout << "North\t";
    if(rooms[player.room].east > 0)
        cout << "East\t";
    if(rooms[player.room].south > 0)
        cout << "South\t";
    if(rooms[player.room].west > 0)
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