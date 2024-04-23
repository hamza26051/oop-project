#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <cstdlib> 
#define FPS 60
using namespace sf;
using namespace std;

int main() {
    const int mapwidth = 20;
    const int mapheight = 15;
    const int cellsize = 40;
    int score = 0;

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

    RenderWindow window(VideoMode(mapwidth * cellsize, mapheight * cellsize), "Pac-Man Game");
    Font font;
    font.loadFromFile("textures/fontsss.ttf");

    Text winmsg;
    winmsg.setFont(font);
    winmsg.setString("YOU WON!" + to_string(score));

    winmsg.setCharacterSize(24);
    winmsg.setFillColor(Color::Red);
    winmsg.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2 - 30);

    Text msg;
    msg.setFont(font);
    msg.setString("YOU LOST!\n Your Score is:" + to_string(score));

    msg.setCharacterSize(24);
    msg.setFillColor(Color::Red);
    msg.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2 - 30);
    Texture wallTexture, dotTexture, pacManTexture, ghost1Texture, ghost4Texture, ghost2Texture, ghost3Texture, cherrytexture;
    wallTexture.loadFromFile("textures/neonoutline.png");
    dotTexture.loadFromFile("textures/yellowdot.png");
    pacManTexture.loadFromFile("textures/pacman.png");
    ghost1Texture.loadFromFile("textures/ghost1.png");
    ghost2Texture.loadFromFile("textures/pngegg.png");
    ghost3Texture.loadFromFile("textures/ghost3.png");
    ghost4Texture.loadFromFile("textures/ghost4.png");
    cherrytexture.loadFromFile("textures/cherry.png");


    Sprite cherrySprite(cherrytexture);
    Sprite wallSprite(wallTexture);
    Sprite dotSprite(dotTexture);
    Sprite pacManSprite(pacManTexture);
    Sprite ghost1Sprite(ghost1Texture);
    Sprite ghost2Sprite(ghost2Texture);
    Sprite ghost3Sprite(ghost3Texture);
    Sprite ghost4Sprite(ghost4Texture);

    int ghost1x = 18;
    int ghost1y = 1;
    int ghost2x = 18;
    int ghost2y = 1;
    int ghost3x = 18;
    int ghost3y = 1;
    int ghost4x = 18;
    int ghost4y = 1;

    cherrySprite.setScale(0.05f, 0.05f);
    pacManSprite.setScale(0.05f, 0.05f);
    ghost1Sprite.setScale(0.07f, 0.07f);
    ghost2Sprite.setScale(0.07f, 0.07f);
    ghost3Sprite.setScale(0.07f, 0.07f);
    ghost4Sprite.setScale(0.07f, 0.07f);

    wallSprite.setScale(0.1f, 0.1f);
    dotSprite.setScale(0.02f, 0.02f);

    int pacmanx = 10;
    int pacmany = 8;

    bool leftPressed = false;
    bool rightPressed = false;
    bool upPressed = false;
    bool downPressed = false;

    int starttime = 0;
    bool ispaused = false;

    int generatetiming = 0;
    int cherrytimer = 0;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        bool conditionpriem = false;
        if ((pacmanx == ghost1x && pacmany == ghost1y) && !conditionpriem ||
            (pacmanx == ghost2x && pacmany == ghost2y) && !conditionpriem ||
            (pacmanx == ghost3x && pacmany == ghost3y) && !conditionpriem ||
            (pacmanx == ghost4x && pacmany == ghost4y) && !conditionpriem) {
            ispaused = true;
        }
       
        if (ispaused ) {
            window.clear(Color(128, 128, 128, 50));
            window.draw(msg);
            window.display();
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                break;
            }
        }
        else {
            if (pacmanmap[pacmany][pacmanx] == '.') {
                pacmanmap[pacmany][pacmanx] = ' ';
                score++;
            }

            int random1, random2, random3, random4;

            static int movementTimer = 0;
            static const int movementInterval = FPS * 5;
            static int previousmove1 = -1;
            static int previousmove2 = -1;
            static int previousmove3 = -1;
            static int previousmove4 = -1;

            if (starttime < 65000) {
                starttime++;
            }
            if (starttime > 10000) {
                movementTimer++;

                if (movementTimer >= movementInterval) {

                    int dx1 = pacmanx - ghost1x;
                    int dy1 = pacmany - ghost1y;
                    int direction1;

                    if (abs(dx1) > abs(dy1)) {
                        direction1 = (dx1 > 0) ? 1 : 0;
                    }
                    else {
                        direction1 = (dy1 > 0) ? 3 : 2;
                    }

                    random1 = -1;
                    if (direction1 == 0 && ghost1x > 0 && pacmanmap[ghost1y][ghost1x - 1] != '#') {
                        random1 = 0;
                    }
                    else if (direction1 == 1 && ghost1x < mapwidth - 1 && pacmanmap[ghost1y][ghost1x + 1] != '#') {
                        random1 = 1;
                    }
                    else if (direction1 == 2 && ghost1y > 0 && pacmanmap[ghost1y - 1][ghost1x] != '#') {
                        random1 = 2;
                    }
                    else if (direction1 == 3 && ghost1y < mapheight - 1 && pacmanmap[ghost1y + 1][ghost1x] != '#') {
                        random1 = 3;
                    }

                    if (random1 == -1) {
                        do {
                            random1 = rand() % 4;
                        } while (random1 == previousmove1);
                    }

                    previousmove1 = random1;
                    if (random1 == 0 && ghost1x > 0 && pacmanmap[ghost1y][ghost1x - 1] != '#') {
                        ghost1x--;
                    }
                    else if (random1 == 1 && ghost1x < mapwidth - 1 && pacmanmap[ghost1y][ghost1x + 1] != '#') {
                        ghost1x++;
                    }
                    else if (random1 == 2 && ghost1y > 0 && pacmanmap[ghost1y - 1][ghost1x] != '#') {
                        ghost1y--;
                    }
                    else if (random1 == 3 && ghost1y < mapheight - 1 && pacmanmap[ghost1y + 1][ghost1x] != '#') {
                        ghost1y++;
                    }

                    if (starttime > 30000) {
                        int dx2 = pacmanx - ghost2x;
                        int dy2 = pacmany - ghost2y;
                        int direction2;

                        if (abs(dx2) > abs(dy2)) {
                            direction2 = (dx2 > 0) ? 1 : 0;
                        }
                        else {
                            direction2 = (dy2 > 0) ? 3 : 2;
                        }

                        random2 = -1;
                        if (direction2 == 0 && ghost2x > 0 && pacmanmap[ghost2y][ghost2x - 1] != '#') {
                            random2 = 0;
                        }
                        else if (direction2 == 1 && ghost2x < mapwidth - 1 && pacmanmap[ghost2y][ghost2x + 1] != '#') {
                            random2 = 1;
                        }
                        else if (direction2 == 2 && ghost2y > 0 && pacmanmap[ghost2y - 1][ghost2x] != '#') {
                            random2 = 2;
                        }
                        else if (direction2 == 3 && ghost2y < mapheight - 1 && pacmanmap[ghost2y + 1][ghost2x] != '#') {
                            random2 = 3;
                        }

                        if (random2 == -1) {
                            do {
                                random2 = rand() % 4;
                            } while (random2 == previousmove2);
                        }

                        previousmove2 = random2;
                        if (random2 == 0 && ghost2x > 0 && pacmanmap[ghost2y][ghost2x - 1] != '#') {
                            ghost2x--;
                        }
                        else if (random2 == 1 && ghost2x < mapwidth - 1 && pacmanmap[ghost2y][ghost2x + 1] != '#') {
                            ghost2x++;
                        }
                        else if (random2 == 2 && ghost2y > 0 && pacmanmap[ghost2y - 1][ghost2x] != '#') {
                            ghost2y--;
                        }
                        else if (random2 == 3 && ghost2y < mapheight - 1 && pacmanmap[ghost2y + 1][ghost2x] != '#') {
                            ghost2y++;
                        }
                    }

                    if (starttime > 45000) {
                        int dx3 = pacmanx - ghost3x;
                        int dy3 = pacmany - ghost3y;
                        int direction3;

                        if (abs(dx3) > abs(dy3)) {
                            direction3 = (dx3 > 0) ? 1 : 0;
                        }
                        else {
                            direction3 = (dy3 > 0) ? 3 : 2;
                        }

                        random3 = -1;
                        if (direction3 == 0 && ghost3x > 0 && pacmanmap[ghost3y][ghost3x - 1] != '#') {
                            random3 = 0;
                        }
                        else if (direction3 == 1 && ghost3x < mapwidth - 1 && pacmanmap[ghost3y][ghost3x + 1] != '#') {
                            random3 = 1;
                        }
                        else if (direction3 == 2 && ghost3y > 0 && pacmanmap[ghost3y - 1][ghost3x] != '#') {
                            random3 = 2;
                        }
                        else if (direction3 == 3 && ghost3y < mapheight - 1 && pacmanmap[ghost3y + 1][ghost3x] != '#') {
                            random3 = 3;
                        }

                        if (random3 == -1) {
                            do {
                                random3 = rand() % 4;
                            } while (random3 == previousmove3);
                        }

                        previousmove3 = random3;
                        if (random3 == 0 && ghost3x > 0 && pacmanmap[ghost3y][ghost3x - 1] != '#') {
                            ghost3x--;
                        }
                        else if (random3 == 1 && ghost3x < mapwidth - 1 && pacmanmap[ghost3y][ghost3x + 1] != '#') {
                            ghost3x++;
                        }
                        else if (random3 == 2 && ghost3y > 0 && pacmanmap[ghost3y - 1][ghost3x] != '#') {
                            ghost3y--;
                        }
                        else if (random3 == 3 && ghost3y < mapheight - 1 && pacmanmap[ghost3y + 1][ghost3x] != '#') {
                            ghost3y++;
                        }
                    }
                    if (starttime > 60000) {
                        int dx4 = pacmanx - ghost4x;
                        int dy4 = pacmany - ghost4y;
                        int direction4;

                        if (abs(dx4) > abs(dy4)) {
                            direction4 = (dx4 > 0) ? 1 : 0;
                        }
                        else {
                            direction4 = (dy4 > 0) ? 3 : 2;
                        }

                        random4 = -1;
                        if (direction4 == 0 && ghost4x > 0 && pacmanmap[ghost4y][ghost4x - 1] != '#') {
                            random4 = 0;
                        }
                        else if (direction4 == 1 && ghost4x < mapwidth - 1 && pacmanmap[ghost4y][ghost4x + 1] != '#') {
                            random4 = 1;
                        }
                        else if (direction4 == 2 && ghost4y > 0 && pacmanmap[ghost4y - 1][ghost4x] != '#') {
                            random4 = 2;
                        }
                        else if (direction4 == 3 && ghost4y < mapheight - 1 && pacmanmap[ghost4y + 1][ghost4x] != '#') {
                            random4 = 3;
                        }

                        if (random4 == -1) {
                            do {
                                random4 = rand() % 4;
                            } while (random4 == previousmove4);
                        }

                        previousmove4 = random4;
                        if (random4 == 0 && ghost4x > 0 && pacmanmap[ghost4y][ghost4x - 1] != '#') {
                            ghost4x--;
                        }
                        else if (random4 == 1 && ghost4x < mapwidth - 1 && pacmanmap[ghost4y][ghost4x + 1] != '#') {
                            ghost4x++;
                        }
                        else if (random4 == 2 && ghost4y > 0 && pacmanmap[ghost4y - 1][ghost4x] != '#') {
                            ghost4y--;
                        }
                        else if (random4 == 3 && ghost4y < mapheight - 1 && pacmanmap[ghost4y + 1][ghost4x] != '#') {
                            ghost4y++;
                        }
                    }
                    movementTimer = 0;

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

            if (generatetiming < 20005) {
                generatetiming++;
            }

            int ex = rand() % mapwidth;
            int why = rand() % mapheight;

            if (pacmanmap[why][ex] == ' ' && generatetiming >= 20000) {
                pacmanmap[why][ex] = '%';
                generatetiming = 0;
            }

            int cherrytimer = 0;
            if (pacmanmap[pacmany][pacmanx] == '%') {
                conditionpriem = true;
                pacmanmap[pacmany][pacmanx] = ' ';
                if (cherrytimer < 50000) {
                    cherrytimer++;
                    pacManSprite.setScale(0.07f, 0.07f);
                    if (pacmanx == ghost1x && pacmany == ghost1y) {
                        ghost1x = 18;
                        ghost1y = 1;
                        starttime = 0;
                    }
                    else if (pacmanx == ghost2x && pacmany == ghost2y) {
                        ghost2x = 18;
                        ghost2y = 1;
                        starttime = 0;
                    }
                    else if (pacmanx == ghost3x && pacmany == ghost3y) {
                        ghost3x = 18;
                        ghost3y = 1;
                        starttime = 0;
                    }
                    else if (pacmanx == ghost4x && pacmany == ghost4y) {
                        ghost4x = 18;
                        ghost4y = 1;
                        starttime = 0;
                    }
                }
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
                    else if (pacmanmap[y][x] == '%') {
                        cherrySprite.setPosition(x * cellsize, y * cellsize);
                        window.draw(cherrySprite);
                    }
                }
            }
            int winchk = 0;
            for (int y = 0; y < mapheight; ++y) {
                for (int x = 0; x < mapwidth; ++x) {
                    if (pacmanmap[y][x] == '.') {
                        winchk++;
                    }
                }
            }
            if (winchk == 0) {
                window.clear(Color(128, 128, 128, 50));
                window.draw(winmsg);
                window.display();
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    break;
                }
            }

            pacManSprite.setPosition(pacmanx * cellsize, pacmany * cellsize);
            window.draw(pacManSprite);

            ghost1Sprite.setPosition(ghost1x * cellsize, ghost1y * cellsize);
            window.draw(ghost1Sprite);
            ghost2Sprite.setPosition(ghost2x * cellsize, ghost2y * cellsize);
            window.draw(ghost2Sprite);

            ghost3Sprite.setPosition(ghost3x * cellsize, ghost3y * cellsize);
            window.draw(ghost3Sprite);

            ghost4Sprite.setPosition(ghost4x * cellsize, ghost4y * cellsize);
            window.draw(ghost4Sprite);

            window.display();
        }
    }
    return 0;
}