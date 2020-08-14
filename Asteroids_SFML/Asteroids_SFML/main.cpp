#include "main.h"
//#include <SFML/Graphics.hpp>
//#include "Ship.h"
//#include "Asteroid.h"




int main()
{

    GameManager gm;

    gm.RunGame();

    delete gm.window;
    delete gm.clock;

    return 0;
}