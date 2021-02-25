// Postupujte podle pokynů v README.md

#include <iomanip>
#include <iostream>

const int ROOM_SIZE = 15;
const int MAX_BEEPERS = 99;

struct Coords { int x,y; };

enum cellType { Wall, Floor};

class Cell {
    unsigned char beeperCount;
    cellType type;
    static const int height = 1;
    static const int width = 3;
public:

    bool isWall() {
        return type == Wall;
    }

    bool isEmptyFloor() {
        return beeperCount == 0;
    }

    void setWall() {
        type = Wall;
    }

    void setEmptyFloor() {
        beeperCount = 0;
        type = Floor;
    }

    bool isFull ( ) const{
        return beeperCount == MAX_BEEPERS;
    }

    void increaseBeepers() {
        if ( isFull() )
        {
            return;
        }
        beeperCount++;
    }

    void decreaseBeepers() {
        if ( isEmptyFloor() )
        {
            return;
        }
        beeperCount--;
    }

    void print(std::ostream & out) {
        if(isWall()) {
            out << std::setw ( width ) << std::setfill ( '#');
        }
        else if(isEmptyFloor()) {
            out << std::setw ( width ) << std::setfill ( ' ');
        }
        else {
            out << std::setw( width ) << beeperCount; // TODO: použít skutečný počet značek
        }
    }
};



class Karel;

class Room {
    Cell gamePlan [ROOM_SIZE][ROOM_SIZE];
    // TODO: doplňte vhodnou vnitřní reprezentaci místnosti
public:
    void init() {
        for ( int i = 0; i < ROOM_SIZE; i++ ) {
            for ( int j = 0; j < ROOM_SIZE; j++ ) {
                if ( i == 0 || i == ROOM_SIZE - 1 || j == 0 || j == ROOM_SIZE - 1 )
                {
                    gamePlan [ i ] [ j ] . setWall();
                }
                else
                {
                    gamePlan [ i ] [ j ] . setEmptyFloor();
                }
            }
        }

    }

    void print(std::ostream & out, Karel & karel);

    Cell & at(const Coords & coords) { // tato funkce jde zkompilovat, ale je zcela chybná (osiřelá reference)
        return gamePlan [ coords . x] [ coords . y ];
    }

};



enum Direction { UP, RIGHT, DOWN, LEFT };

class Karel {
    std::ostream * outPtr;
    Coords position;
    Direction direction;
    Room gamePlan;
    // TODO: doplňte vhodnou reprezentaci

    friend Room;
    void printKarel(std::ostream & out, const Coords & coords) { // bude potřeba upravit pro různé orientace karla; tuto funkci volá Room při výpisu
        if(coords.x == position . x && coords.y == position . y ) {
            static const char arrows [ 4 ] = { '^', '>', 'v', '<' };
            out << arrows [ direction ];
        }
        else {
            out << " ";
        }
    }
public:
    void init(std::ostream * outPtr) {
        this -> outPtr = outPtr;
        position = { 1, ROOM_SIZE - 2 };
        direction = UP;
        gamePlan . init();
    }

    void print() { // vytiskne celou místnost
        gamePlan.print( *outPtr, *this );
    }

    void step() {

    }

    void turnLeft() {

    }

    void putBeeper() {

    }

    void pickBeeper() {

    }

    bool beforeWall() {
        return false;
    }

    bool onBeeper() {
        return false;
    }
};

void Room::print( std::ostream & out, Karel & karel )
{ // tuto funkci budete muset vyčlenit ven, abyste mohli pracovat s karlem pro potřeby jeho výpisu
    for ( int i = 0; i < ROOM_SIZE; i++ ) {
        for ( int j = 0; j < ROOM_SIZE; j++ ) {
            karel . printKarel ( out, { i, j } );
            at ( { i, j }) . print( out );
        }
    }
}

// otáčení zpět
void turnBack(Karel & karel) {
    karel.turnLeft();
    karel.turnLeft();
}

// cesta tam a zpátky
void hobbit(Karel & karel) {
    while(!karel.beforeWall()) karel.step();
    turnBack(karel);
    while(!karel.beforeWall()) karel.step();
    turnBack(karel);
}

int main() {
    Karel karel;
    karel.init(&std::cout);
    hobbit(karel);
    return 0;
}
