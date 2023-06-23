#include <iostream>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define GRIDSIZE 4
#define UP      0
#define DOWN    2
#define LEFT    3
#define RIGHT   1
#define MAX_SHOTS 3





//string to_string(int x)
//{
//    std::string out_string;
//    std::stringstream ss;
//    ss << x;
//    return ss.str();
//}


class Position
{

    int x, y;

public:

    Position (int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Position() {}

    // Modify the following four so that the resulting position does not leave the grid
    void moveRight()
    {
        x++;
        x=min(x,GRIDSIZE-1);
    }

    void moveLeft()
    {
        x--;
        x=max(x,0);
    }

    void moveUp()
    {
        y++;
        y=min(y,GRIDSIZE-1);
    }

    void moveDown()
    {
        y--;
        y=max(y,0);
    }

    bool isAdjacent(Position p)
    {
        bool fl=false;
        if(0<=p.getX()&&p.getX()<GRIDSIZE&&0<=p.getY()&&p.getY()<GRIDSIZE){
            if(0<=x&&x<GRIDSIZE&&0<=y&&y<GRIDSIZE){
                int sum=abs(x-p.getX())+abs(y-p.getY());
                if(sum==1){fl=true;}
            }
        }
        return fl;
    }

    bool isSamePoint(Position p)
    {
        return (x==p.getX())&&(y==p.getY());
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

};


class Wumpus
{


    bool killed;
    Position p;

public:

    Wumpus(int x, int y)
    {
        p = Position(x, y);
        killed = false;
    }

    Wumpus()
    {
        killed=false;
        int x,y;
        x=abs(rand())%4;
        y=abs(rand())%4;
        if(x==0&&y==0){    x=abs(rand())%3+1;  y=abs(rand())%3+1;          }
        p=Position(x,y);
    }

    void kill()
    {
        killed = true;
    }

    Position getPosition()
    {
        return p;
    }

};


class Player
{

    int direction;
    int total_shots;
    bool killed;
    Position p;

public:

    Player()
    {
        killed=false;
        direction=UP;
        total_shots=3;
        p=Position(0,0);
    }

    void turnLeft()
    {
        direction--;
        direction+=4;direction%=4;
    }

    void turnRight()
    {
        direction++;
        direction%=4;
    }

    void moveForward()
    {
        if(direction==UP){p.moveUp();}
        else if(direction==DOWN){p.moveDown();}
        else if(direction==LEFT){p.moveLeft();}
        else if(direction==RIGHT){p.moveRight();}
    }

    bool isAdjacent(Position pos)
    {
        return p.isAdjacent(pos);
    }

    bool isSamePoint(Position pos)
    {
        return p.isSamePoint(pos);
    }

    void kill()
    {
        killed = true;
    }

    string getPositionInfo()
    {
        return "Player is now at " + to_string(p.getX()) + ", " + to_string(p.getY());
    }

    string getDirectionInfo()
    {
        string s;
        if (direction == UP) s = "up";
        if (direction == DOWN) s = "down";
        if (direction == LEFT) s = "left";
        if (direction == RIGHT) s = "right";
        return "Player is moving at direction: " + s;
    }

};



class WumpusWorld
{

private:

    Player player;
    Wumpus wumpus;
    Position gold_position;
    bool ended;

public:

    WumpusWorld()
    {
       int x=abs(rand())%4;
       int y=abs(rand())%4;
       if(x==0&&y==0){
        x=abs(rand())%3+1;
        y=abs(rand())%3+1;
       }
       gold_position=Position(x,y);
       ended=false;
    }

    WumpusWorld(int wumpus_x, int wumpus_y)
    {
        wumpus=Wumpus(wumpus_x,wumpus_y);
        int x=abs(rand())%4;
       int y=abs(rand())%4;
       if(x==0&&y==0){
        x=abs(rand())%3+1;
        y=abs(rand())%3+1;
       }
       gold_position=Position(x,y);
        ended=false;
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y)
    {
        wumpus=Wumpus(wumpus_x,wumpus_y);
        ended=false;
        gold_position=Position(gold_x,gold_y);
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y)
    {
        //...
    }

    void moveForward()
    {
        player.moveForward();
        return showGameState();
    }

    void turnLeft()
    {
        player.turnLeft();
        return showGameState();
    }

    void turnRight()
    {
        player.turnRight();
        return showGameState();
    }

    void shoot()
    {

        Position p=wumpus.getPosition();
        string s=player.getPositionInfo();
        int x=s[17]-'0';
        int y=s[20]-'0';
        s=player.getDirectionInfo();
        int dir;
        if(s[31]=='u'){dir=0;}
        if(s[31]=='d'){dir=2;}
        if(s[31]=='l'){dir=3;}
        if(s[31]=='r'){dir=1;}
        int fl=0;
        if(dir==0)
        {
            if(p.getX()==x&&p.getY()>y){fl=1;}
        }
        if(dir==2)
        {
            if(p.getX()==x&&p.getY()<y){fl=1;}
        }
        if(dir==3){
            if(p.getY()==y&&p.getX()<x){fl=1;}
        }
        if(dir==1){
            if(p.getY()==y&&p.getX()>x){fl=1;}
        }

        if(fl){
            wumpus.kill();
            cout<<"ssshhhhhh\n      Wumpus has died!!!!!\n";
        }
        else{cout<<"Missed!!!!\n";}

    }

    void showGameState()
    {
        cout << player.getPositionInfo() << endl;
        cout << player.getDirectionInfo() << endl;

        if (player.isAdjacent(wumpus.getPosition()))
        {
            cout << "stench!" << endl;
        }

        if (player.isSamePoint(wumpus.getPosition()))
        {
            cout << "Player is killed!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
        }

        if (player.isSamePoint(gold_position))
        {
            cout << "Got the gold!" << endl;
            cout << "Game ended, you won!" << endl;
            ended = true;
        }
    }

    bool isOver()
    {
        return ended;
    }

};


int main()
{






    int c, wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y;
    char*s=new char[100];
    cin>>s;
    FILE*ptr=fopen(s,"r");
    if(ptr==NULL)
    {
        cout<<"Unable to open the file\n";
        exit(0);
    }


    fscanf(ptr,"%d %d %d %d %d %d",&wumpus_x,&wumpus_y,&gold_x,&gold_y,&pit_x,&pit_y);


    WumpusWorld w(wumpus_x, wumpus_y, gold_x, gold_y);
    srand(time(0));
    w.showGameState();
    while (!w.isOver())
    {
        cout << "1: move forward" << endl;
        cout << "2: Turn left" << endl;
        cout << "3: Turn right" << endl;
        cout << "4: Shoot" << endl;
        cin >> c;
        if (c == 1)
        {
            w.moveForward();
        }
        else if (c == 2)
        {
            w.turnLeft();
        }
        else if (c == 3)
        {
            w.turnRight();
        }
        else if (c == 4)
        {
            w.shoot();
        }
    }
    return 0;
}
