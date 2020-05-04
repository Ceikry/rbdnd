#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <termios.h>
#include <stdlib.h>


using namespace std;

vector<struct NPC>NPCs;

class BufferToggle {
    private:
        struct termios t;
    public:
        void off(void){
            tcgetattr(STDIN_FILENO, &t);
            t.c_lflag &= ~ICANON & ~ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &t);
        }
        void on(void){
            tcgetattr(STDIN_FILENO, &t);
            t.c_lflag |= ICANON & ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &t);
        }
};

int abs(int x){
    if(x > 0){
        return x;
    }
    return -x;
}

void displayNPCs(void){
    for(int i=0; i < NPCs.size(); i++){
        y[NPCs[i].ypos][NPCs[i].x] = NPCs[i].mychar;
    }
}

int main()
{
    Entity player = new Entity();

    struct Player player;
    player.pChar='@';
    makeMap(25);
    player.ypos = y.size() / 2;
    player.x = y[player.ypos].size() / 2;
    NPCs.reserve(10);
    BufferToggle bt;
    bt.off();
    string u_input;
    makeNPC("King Mexis", 16, 2, '&', "Ravioli Ravioli what's in the pocketoli???");
    makeNPC("Andrei the Romanian", 20, 4, '$', "Ey mang you wan sum computer science???");
    makeNPC("Ol'Dally", 13, 12, '%' , "Uhh, weiners.");
    while(true){
        y[player.ypos][player.x] = player.pChar;
        for(int i = 0; i < NPCs.size(); i++){
             y[NPCs[i].ypos][NPCs[i].x] = ' ';
            NPCs[i].findPath(player.x,player.ypos);
        }
        displayNPCs();
        makeWall(0,0,1,4);
        makeWall(1,3,3,1);
        makeWall(6,3,3,1);
        makeWall(9,0,1,4);
        makeWall(1,0,8,1);
        makeWall(7,7,5,1);
        makeWall(14,7,5,1);
        makeWall(7,8,1,8);
        makeWall(18,8,1,8);
        makeWall(7,16,12,1);
        printMap();
        for(int i=0; i < NPCs.size(); i++){
            if(abs(player.x - NPCs[i].x) <= 1 && abs(player.ypos - NPCs[i].ypos) <= 1){
                NPCs[i].say(NPCs[i].message);
            }
        }
        y[player.ypos][player.x] = ' ';
        cout << endl << endl << endl;
        if(getchar() == '\033'){
            getchar();
            switch(getchar()){
                case 'A':
                    player.mv("up");
                    break;
                case 'B':
                    player.mv("down");
                    break;
                case 'C':
                    player.mv("right");
                    break;
                case 'D':
                    player.mv("left");
                    break;
            }
        }
        system("clear");
    }
    bt.off();
    return 0;
}
