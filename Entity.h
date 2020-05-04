#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
    string name,message;
    int xpos;
    int ypos;
    char mychar;

    public:
        Entity();

        //function for drawing the name on the map... I don't know why I wrote this.
        void drawNameOnMap(void){
            for(int thisChar = 0; thisChar < name.size(); thisChar++){
                y[ypos - 1][x - static_cast<int>(name.size() / 2) + thisChar] = static_cast<char>(name[thisChar]);
            }
        }
        void say(string message){
            cout << name << " says: " << message << endl;
        }

        //checks collision, returns true if you can move there, false if not.
        bool checkCollide(int tx, int ty){
            if (y[ty][tx] == '-' || y[ty][tx] == '|' || tx == y[0].capacity() || abs(ty - y.capacity()) == 1 || tx < 1 || ty < 1){
                return false;
            }
            return true;
        }

        //Function for handling movement in a specific direction
        void mv(string direction){
            switch(direction){
               case "down":
                    if(checkCollide(x, ypos + 1){
                        ypos = ypos + 1;
                    }
                    break;
                case "up":
                    if(checkCollide(x, ypos - 1)){
                        ypos = ypos - 1;
                    }
                    break;
                case "left":
                    if(checkCollide(x - 1, ypos)){
                        x -= 1;
                    }
                    break;
                case "right":
                    if(checkCollide(x + 1, ypos)){
                        x += 1;
                    }
                    break;
                case "upright":
                    if(checkCollide(x + 1, ypos - 1)){
                        x += 1;
                        ypos -= 1;
                    }
                    break;
                case "upleft":
                    if(checkCollide(x - 1, ypos - 1) == 0){
                        x -= 1;
                        ypos -= 1;
                    }
                    break;
                case "downright":
                    if(checkCollide(x + 1, ypos + 1) == 0){
                        x += 1;
                        ypos += 1;
                    }
                    break;
                case "downleft":
                    if(checkCollide(x - 1, ypos + 1) == 0){
                        x -= 1;
                        ypos += 1;
                    }
                    break;
            }
        }

        //rudimentary pathfinding, one movement at a time
        void findPath(int tx, int ty){
            int distanceX = tx - xpos;
            int distanceY = ty - ypos;
            if(abs(distanceX) <= 2 && abs(distanceY) <= 2){
            } else if(distanceX > 0 && distanceY > 0){
                mv("downright");
            } else if(distanceX < 0 && distanceY > 0){
                mv("downleft");
            } else if(distanceX > 0 && distanceY < 0){
                mv("upright");
            } else if(distanceX < 0 && distanceY < 0){
                mv("upleft");
            } else if(distanceX < 1 && distanceY == 0){
                mv("left");
            } else if(distanceX > 1 && distanceY == 0){
                mv("right");
            } else if(distanceX == 0 && distanceY > 1){
                mv("down");
            } else if(distanceX == 0 && distanceY < 1){
                mv("up");
            }
    }
    protected:

    private:
};

#endif // ENTITY_H
