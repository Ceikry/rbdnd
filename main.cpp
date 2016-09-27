#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <termios.h>
#include <stdlib.h>


using namespace std;

vector<vector<char> >y;
vector<struct NPC>NPCs;
char pChar = '@';

struct NPC{
    string name,message;
    int x;
    int ypos;
    char mychar;
    void printName(void){
        for(int thisChar = 0; thisChar < name.size(); thisChar++){
            y[ypos - 1][x - static_cast<int>(name.size() / 2) + thisChar] = static_cast<char>(name[thisChar]);
        }
    }
    void say(string message){
        cout << name << " says: " << message << endl;
    }
};

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

void makeMap(int size){
    y.reserve(size);
    int height = size;
    int width = height;
    for(int i=0; i < height; i++){
        vector<char>x;
        width = height * 2;
        x.reserve(width);
        for(int k = 0; k < x.capacity(); k++){
            x.push_back(' ');
        }
        y.push_back(x);
    }
}

void makeWall(int xpos, int ypos, int width, int height){
    for(int i = 0; i < height; i++){
        for(int k = 0; k < width; k++){
            char wallsym;
            if(height > width){
                wallsym = '|';
            } else {
                wallsym = '-';
            }
            y[ypos + i][xpos + k] = wallsym;
        }
    }
}


void printMap(){
    for(int i=0; i < y.size(); i++){
        for(int k=0; k < y[i].size(); k++){
            cout << y[i][k];
        }
        cout << endl;
    }
}

int abs(int x){
    if(x > 0){
        return x;
    }
    return -x;
}

void makeNPC(string name, int x, int ypos, char sym, string message=" "){
    struct NPC npc;
    npc.name=name;
    npc.x = x;
    npc.ypos = ypos;
    npc.mychar = sym;
    npc.message=message;
    NPCs.push_back(npc);
}

void displayNPCs(void){
    for(int i=0; i < NPCs.size(); i++){
        y[NPCs[i].ypos][NPCs[i].x] = NPCs[i].mychar;
    }
}

int main()
{
    makeMap(25);
    int iYp = y.size() / 2;
    int iXp = y[iYp].size() / 2;
    NPCs.reserve(10);
    BufferToggle bt;
    bt.off();
    string u_input;
    makeNPC("King Mexis", 16, 2, '&', "Ravioli Ravioli what's in the pocketoli???");
    makeNPC("Andrei the Romanian", 20, 4, '$', "Ey mang you wan sum computer science???");
    makeNPC("Ol'Dally", 13, 12, '%' , "Uhh, weiners.");
    while(true){
        for(int i = 0; i < NPCs.size(); i++){
            NPCs[i].printName();
        }
        displayNPCs();
        y[iYp][iXp] = pChar;
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
            if(abs(iXp - NPCs[i].x) <= 1 && abs(iYp - NPCs[i].ypos) <= 1){
                NPCs[i].say(NPCs[i].message);
            }
        }
        y[iYp][iXp] = ' ';
        cout << endl << endl << endl;
        if(getchar() == '\033'){
            getchar();
            switch(getchar()){
                case 'A':
                    if(y[iYp - 1][iXp] == '-' || y[iYp - 1][iXp] == '|'){
                        } else {
                            if(iYp - 1 > 0){
                                iYp = iYp - 1;
                            }
                        }
                    break;
                case 'B':
                    if(y[iYp + 1][iXp] == '-' || y[iYp + 1][iXp] == '|'){
                    } else {
                        if(iYp + 1 < y.size() - 1){
                            iYp = iYp + 1;
                        }
                    }
                    break;
                case 'C':
                    if(y[iYp][iXp + 1] == '-' || y[iYp][iXp + 1] == '|'){
                    } else {
                        if(iXp + 1 < y[0].size()){
                            iXp = iXp + 1;
                        }
                    }
                    break;
                case 'D':
                    if(y[iYp][iXp - 1] == '-' || y[iYp][iXp - 1] == '|'){
                    } else {
                        if(iXp - 1 > 0){
                        iXp = iXp - 1;
                        }
                    }
                    break;
            }
        }
        system("clear");
    }
    bt.off();
    return 0;
}
