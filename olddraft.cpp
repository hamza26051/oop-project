#include <SFML/Graphics.hpp>
#include <iostream>
#define FPS 60
using namespace sf;
using namespace std;

int main() {
    const int mapwidth = 20;
    const int mapheight = 15;
    const int cellsize = 40;


    std::string pacmanmap[mapheight] = {
        "####################",
        "#..................#",
        "#.###.###.###..#####",
        "#.#...#...#.#..#####",
        "#.#.###.###.#....###",
        "#.#.#...#.#.....####",
        "#...#.#.#.#.###....#",
        "#.###.#.#...#......#",
        "#.###.......#....#.#",
        "#...###.###.###....#",
        "#.#.###.###...#..###",
        "#.#...#.....###..###",
        "#.#................#",
        "#.#.#.#.#.#####..###",
        "####################"

    };

    RenderWindow window(VideoMode(mapwidth*cellsize, mapheight*cellsize ), "Pac-Man Game");

   
    Texture wallTexture, dotTexture, pacManTexture, ghostTexture;
    wallTexture.loadFromFile("textures/neonoutline.png");
    dotTexture.loadFromFile("textures/yellowdot.png");
    pacManTexture.loadFromFile("textures/pacman.png");
    ghostTexture.loadFromFile("textures/game.png");

    Sprite wallSprite(wallTexture);
    Sprite dotSprite(dotTexture);
    Sprite pacManSprite(pacManTexture);
    Sprite ghostSprite(ghostTexture);

    int ghostx = 18;
    int ghosty = 1;
  

    pacManSprite.setScale(0.05f, 0.05f);
    ghostSprite.setScale(0.05f, 0.05f);
    wallSprite.setScale(0.1f, 0.1f);
    dotSprite.setScale(0.02f, 0.02f);

    int pacmanx = 10; 
    int pacmany = 8; 

    bool leftPressed = false;
    bool rightPressed = false;
    bool upPressed = false;
    bool downPressed = false;

    int starttime = 0;



    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        int random;
        static bool isgenerated = true;
        static int movementtime = 0;
        static const int movementinterval = FPS*3 ; 

        if (starttime < 10000) { 
            starttime++;
        }
        else {
            movementtime++;

            if (movementtime >= movementinterval) { // Check if enough time has passed
                random = rand() % 4;

                if (random == 0 && ghostx > 0 && pacmanmap[ghosty][ghostx - 1] != '#') {
                    ghostx--;
                }
                else if (random == 1 && ghostx < mapwidth - 1 && pacmanmap[ghosty][ghostx + 1] != '#') {
                    ghostx++;
                }
                else if (random == 2 && ghosty > 0 && pacmanmap[ghosty - 1][ghostx] != '#') {
                    ghosty--;
                }
                else if (random == 3 && ghosty < mapheight - 1 && pacmanmap[ghosty + 1][ghostx] != '#') {
                    ghosty++;
                }

                movementtime = 0;
                isgenerated = false;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) && !leftPressed && pacmanx > 0 && pacmanmap[pacmany][pacmanx - 1] != '#') {
            pacmanx--; 
            leftPressed = true;
        }
        else if (!Keyboard::isKeyPressed(Keyboard::Left)) {
            leftPressed = false;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right) && !rightPressed && pacmanx < mapwidth - 1 && pacmanmap[pacmany][pacmanx + 1] != '#') {
            pacmanx++; 
            rightPressed = true;
        }
        else if (!Keyboard::isKeyPressed(Keyboard::Right)) {
            rightPressed = false;
        }

        if (Keyboard::isKeyPressed(Keyboard::Up) && !upPressed && pacmany > 0 && pacmanmap[pacmany - 1][pacmanx] != '#') {
            pacmany--; 
            upPressed = true;
        }
        else if (!Keyboard::isKeyPressed(Keyboard::Up)) {
            upPressed = false;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down) && !downPressed && pacmany < mapheight - 1 && pacmanmap[pacmany + 1][pacmanx] != '#') {
            pacmany++; 
            downPressed = true;
        }
        else if (!Keyboard::isKeyPressed(Keyboard::Down)) {
            downPressed = false;
        }

        

        window.clear();

        for (int y = 0; y < mapheight; ++y) {
            for (int x = 0; x < mapwidth; ++x) {
                if (pacmanmap[y][x] == '#') {
                    wallSprite.setPosition(x * cellsize, y * cellsize);
                    window.draw(wallSprite);
                }
                else if (pacmanmap[y][x] == '.') {
                    dotSprite.setPosition(x * cellsize, y * cellsize);
                    window.draw(dotSprite);
                }
            }
        }

        pacManSprite.setPosition(pacmanx * cellsize, pacmany * cellsize);
        window.draw(pacManSprite);

        ghostSprite.setPosition(ghostx * cellsize, ghosty * cellsize);
        window.draw(ghostSprite);
      
        window.display();
    }

    return 0;
}
