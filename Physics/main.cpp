#include "stdafx.h"

int main()
{
    unsigned short WIDTH = 1280;
    unsigned short HEIGHT = 720;
    const std::string NAME = "Silent Hill";

    Game game(WIDTH, HEIGHT, NAME);
    game.run();

    return 0;
}