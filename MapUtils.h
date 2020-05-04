#ifndef MAPUTILS_H
#define MAPUTILS_H


class MapUtils
{
    public:
        vector<vector<char> >gameMap;
        MapUtils();

        void makeMap(int size){
            gameMap.reserve(size);
            int height = size;
            int width = height;
            for(int i=0; i < height; i++){
                vector<char>x;
                width = height * 2;
                x.reserve(width);
                for(int k = 0; k < x.capacity(); k++){
                    x.push_back(' ');
                }
                gameMap.push_back(x);
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
                    gameMap[ypos + i][xpos + k] = wallsym;
                }
            }
        }

        void drawMap(){
            for(int i=0; i < gameMap.size(); i++){
                for(int k=0; k < y[i].size(); k++){
                    cout << gameMap[i][k];
                }
                cout << endl;
            }
        }


    protected:

    private:
};

#endif // MAPUTILS_H
