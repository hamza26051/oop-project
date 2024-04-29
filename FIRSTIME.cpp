
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <cstdlib> 
#define FPS 60
using namespace sf;
using namespace std;

int main() {
    const int mapwidth = 30;
    const int mapheight = 23;
    const int cellsize = 40;
    static int score = 0;

    std::string pacmanmap[mapheight] = {
        "##############################",
        "#............0##0............#",
        "#..####.#####.##.#####.####..#",
        "#..####.#####.##.#####.####..#",
        "#0..........................0#",
        "#####..#...#######....#..#####",
        "#0.....#......#.......#.....0#",
        "#####..####...#.....###..#####",
        "#####..#..............#..#####",
        "#####..#..............#..#####",
        "#####..#..............#..#####",
        "0..........#.....#...........0",
        "####...#....#####.....#...####",
        "####...#..............#...####",
        "####.......#######........####",
        "#.............#...............",
        "#.####...####.#.####....####.#",
        "#...0#..................#0...#",
        "#....#...#.########.#...#....#",
        "#.##.....#....#.....#......###",
        "#....#######..#...#######....#",
        "#0..........................0#",
        "##############################",
        
    };

    Clock clock;
    
    RenderWindow window(VideoMode(mapwidth * cellsize+100, mapheight * cellsize), "Pac-Man Game");
    SoundBuffer buffer1;
    SoundBuffer buffer2;
    SoundBuffer buffer3;
    SoundBuffer buffer4;
    SoundBuffer buffer5;
    SoundBuffer buffer6;
    SoundBuffer main;

    if (!buffer1.loadFromFile("textures/begin.wav")) {
        cout << "Failed to load sound file!" << endl;
        return -1;
    }
    buffer2.loadFromFile("textures/eat.wav");
    buffer3.loadFromFile("textures/death.wav");
    buffer4.loadFromFile("textures/fruit.wav");
    buffer5.loadFromFile("textures/eatghost.wav");
    buffer6.loadFromFile("textures/near.wav");

    
     Sound sound1;
     Sound sound2;
     Sound sound3;
     Sound sound4;
     Sound sound5;
     Sound sound6;


     sound1.setBuffer(buffer1);
     sound2.setBuffer(buffer2);
     sound3.setBuffer(buffer3);
     sound4.setBuffer(buffer4);
     sound5.setBuffer(buffer5);
     sound6.setBuffer(buffer6);


    Font font;
    font.loadFromFile("textures/pacmanfont.ttf");


    RectangleShape loading(Vector2f(50, 0));
    loading.setFillColor(Color::Yellow);
    loading.setPosition(window.getSize().x - 80, 100);
   
    Text readymsg;
    readymsg.setFont(font);
    readymsg.setString("READYYY");
    readymsg.setFillColor(Color::Red);
    readymsg.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2 - 30);

    Text winmsg;
    winmsg.setFont(font);
    winmsg.setString("YOU WON" + to_string(score));
    winmsg.setScale(1.5f, 1.5f);

   

    RectangleShape border(Vector2f(52, 602)); 
    border.setFillColor(Color::Transparent);
    border.setOutlineColor(Color::White); 
    border.setOutlineThickness(10); 
    border.setPosition(window.getSize().x - 81, 99); 

    winmsg.setCharacterSize(24);
    winmsg.setFillColor(Color::Red);
    winmsg.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 - 30);

    Text msg;
    msg.setFont(font);
    msg.setScale(1.5f, 1.5f);
    
    Text scoredis;
    scoredis.setFont(font);
    scoredis.setFillColor(Color::Red);
    scoredis.setPosition(window.getSize().x - 100, 20);
    scoredis.setScale(0.5f, 0.5f);



    msg.setCharacterSize(24);
    msg.setFillColor(Color::Red);
    msg.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 -60);
    Texture wallTexture, dotTexture,dotbigTexture, pacManTexture, ghost1Texture, ghost4Texture, ghost2Texture, ghost3Texture, cherrytexture;
    wallTexture.loadFromFile("textures/neonoutline.png");
    dotTexture.loadFromFile("textures/yellowdot.png");
    dotbigTexture.loadFromFile("textures/yellowdot.png");
    pacManTexture.loadFromFile("textures/pacman.png");
    ghost1Texture.loadFromFile("textures/ghost1.png");
    ghost2Texture.loadFromFile("textures/pngegg.png");
    ghost3Texture.loadFromFile("textures/ghost3.png");
    ghost4Texture.loadFromFile("textures/ghost4.png");
    cherrytexture.loadFromFile("textures/cherry.png");


    Sprite cherrySprite(cherrytexture);
    Sprite wallSprite(wallTexture);
    Sprite dotSprite(dotTexture);
    Sprite dotbigSprite(dotbigTexture);
    Sprite pacManSprite(pacManTexture);
    Sprite ghost1Sprite(ghost1Texture);
    Sprite ghost2Sprite(ghost2Texture);
    Sprite ghost3Sprite(ghost3Texture);
    Sprite ghost4Sprite(ghost4Texture);

    int ghost1x = 15;
    int ghost1y = 10;
    int ghost2x = 13;
    int ghost2y = 10;
    int ghost3x = 15;
    int ghost3y = 11;
    int ghost4x = 13;
    int ghost4y = 11;

    cherrySprite.setScale(0.05f, 0.05f);
    pacManSprite.setScale(0.05f, 0.05f);
    ghost1Sprite.setScale(0.07f, 0.07f);
    ghost2Sprite.setScale(0.07f, 0.07f);
    ghost3Sprite.setScale(0.07f, 0.07f);
    ghost4Sprite.setScale(0.07f, 0.07f);

    wallSprite.setScale(0.1f, 0.1f);
    dotSprite.setScale(0.015f, 0.015f);
    dotbigSprite.setScale(0.03f, 0.03f);

    int pacmanx = 14;
    int pacmany = 13;

    bool leftPressed = false;
    bool rightPressed = false;
    bool upPressed = false;
    bool downPressed = false;

    int starttime1 = 0;
    int starttime2 = 0;
    int starttime3 = 0;
    int starttime4 = 0;
    bool ispaused = false;

    int generatetiming = 0;
    bool ischerryeaten = false;
    int cherrytimer = 0;
    int begin = 0;
    bool gamenotready = true;
    bool isgamewon = false;
    bool ghostvisible1 = true;
    Clock ghosttimer1;
    int toggletime=0;
    int musictimer = 0;
    int lastmusic = 0;


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        if (isgamewon) {
            for (int y = 0; y < mapheight; ++y) {
                for (int x = 0; x < mapwidth; ++x) {
                    if (pacmanmap[y][x] == '#') {
                        wallSprite.setPosition(x * cellsize, y * cellsize);
                        window.draw(wallSprite);
                    }
                    else if (pacmanmap[y][x] == '0') {
                        dotbigSprite.setPosition(x * cellsize, y * cellsize);
                        window.draw(dotbigSprite);
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

            window.draw(winmsg);
            window.display();
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                break;
            }
        }
        if (musictimer < 5) {
            musictimer++;
        }
        if (musictimer < 2) {
            sound1.play();
            window.draw(readymsg);
        }
        
        else if (!isgamewon) {
            if (begin < 4005) {
                gamenotready = true;

                begin++;
            }
            else if (begin > 4000) {
                gamenotready = false;
            }
            if (generatetiming < 40005) {
                generatetiming++;
            }

            int ex = rand() % mapwidth;
            int why = rand() % mapheight;

            if (pacmanmap[why][ex] == ' ' && generatetiming >= 40000 && !gamenotready) {
                pacmanmap[why][ex] = '%';
                generatetiming = 0;
            }


            if (pacmanmap[pacmany][pacmanx] == '%') {
                pacmanmap[pacmany][pacmanx] = ' ';
                sound4.play();
                ischerryeaten = true;
            }

            if (ischerryeaten) {

                cherrytimer++;
                if (cherrytimer < 10000) {
                    pacManSprite.setScale(0.07f, 0.07f);
                    float percentage = static_cast<float>(cherrytimer) / 10000;
                    loading.setSize(sf::Vector2f(50, percentage * 600));
                    if (pacmanx == ghost1x && pacmany == ghost1y) {
                        sound5.play();
                        ghost1x = 15;
                        ghost1y = 10;
                        starttime1 = 0;

                    }
                    else if (pacmanx == ghost2x && pacmany == ghost2y) {
                        sound5.play();
                        ghost2x = 13;
                        ghost2y = 10;
                        starttime2 = 0;

                    }
                    else if (pacmanx == ghost3x && pacmany == ghost3y) {
                        sound5.play();
                        ghost3x = 15;
                        ghost3y = 11;
                        starttime3 = 0;

                    }
                    else if (pacmanx == ghost4x && pacmany == ghost4y) {
                        sound5.play();
                        ghost4x = 13;
                        ghost4y = 11;
                        starttime4 = 0;

                    }
                }
                else if (cherrytimer > 10000) {
                    pacManSprite.setScale(0.05f, 0.05f);
                    ischerryeaten = false;
                    cherrytimer = 0;
                    loading.setSize(sf::Vector2f(50, 0));
                }
            }

            bool ghostnear = false;
            if (!ispaused){
                float dist1 = sqrt(pow(pacmanx - ghost1x, 2) + pow(pacmany - ghost1y, 2));
            float dist2 = sqrt(pow(pacmanx - ghost2x, 2) + pow(pacmany - ghost2y, 2));
            float dist3 = sqrt(pow(pacmanx - ghost3x, 2) + pow(pacmany - ghost3y, 2));
            float dist4 = sqrt(pow(pacmanx - ghost4x, 2) + pow(pacmany - ghost4y, 2));
            if (dist1 < 2 || dist2 < 2 || dist3 < 2 || dist4 < 2) {
                ghostnear = true;
            }

            if (ghostnear) {
                sound6.play();
            }
        }
            bool conditionpriem = false;

            if ((!ischerryeaten && pacmanx == ghost1x && pacmany == ghost1y) ||
                (!ischerryeaten && pacmanx == ghost2x && pacmany == ghost2y) ||
                (!ischerryeaten && pacmanx == ghost3x && pacmany == ghost3y) ||
                (!ischerryeaten && pacmanx == ghost4x && pacmany == ghost4y)) {
                if (lastmusic < 5) {
                    lastmusic++;
                }
                if (lastmusic < 2) {
                    sound3.play();
                }
                ispaused = true;
            }

            if (ispaused) {
                window.clear();
                for (int y = 0; y < mapheight; ++y) {
                    for (int x = 0; x < mapwidth; ++x) {
                        if (pacmanmap[y][x] == '#') {
                            wallSprite.setPosition(x * cellsize, y * cellsize);
                            window.draw(wallSprite);
                        }
                        else if (pacmanmap[y][x] == '0') {
                            dotbigSprite.setPosition(x * cellsize, y * cellsize);
                            window.draw(dotbigSprite);
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
                pacManSprite.setPosition(pacmanx* cellsize, pacmany* cellsize);
                window.draw(pacManSprite);

                ghost1Sprite.setPosition(ghost1x* cellsize, ghost1y* cellsize);
                window.draw(ghost1Sprite);

                ghost2Sprite.setPosition(ghost2x* cellsize, ghost2y* cellsize);
                window.draw(ghost2Sprite);
                ghost3Sprite.setPosition(ghost3x* cellsize, ghost3y* cellsize);
                window.draw(ghost3Sprite);
                ghost4Sprite.setPosition(ghost4x* cellsize, ghost4y* cellsize);
                window.draw(ghost4Sprite);

                msg.setString("YOU LOST!\nYour Score is:" + to_string(score) + " \n\n\n\n\npress Esc to continue");
                window.draw(msg);
                window.display();
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    break;
                }
            }
            else {
                if (pacmanmap[pacmany][pacmanx] == '.') {
                    pacmanmap[pacmany][pacmanx] = ' ';
                    sound2.play();
                    score++;
                }
                if (pacmanmap[pacmany][pacmanx] == '0') {
                    pacmanmap[pacmany][pacmanx] = ' ';
                    sound2.play();
                    score=score+10;
                }

                int random1, random2, random3, random4;

                static int movementTimer = 0;
                static const int movementInterval = FPS * 10;
                static int previousmove1 = -1;
                static int previousmove2 = -1;
                static int previousmove3 = -1;
                static int previousmove4 = -1;

                if (starttime1 < 5005 && !gamenotready) {
                    starttime1++;
                }
                if (starttime2 < 30050 && !gamenotready) {
                    starttime2++;
                }
                if (starttime3 < 45050 && !gamenotready) {
                    starttime3++;
                }
                if (starttime4 < 60050 && !gamenotready) {
                    starttime4++;
                }
                if (starttime1 > 5000 || starttime2 > 5000 || starttime3 > 5000 || starttime4 > 5000) {
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

                        if (starttime2 > 30000) {
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

                        if (starttime3 > 45000) {
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
                        if (starttime4 > 60000) {
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
                if (Keyboard::isKeyPressed(Keyboard::Left) && !leftPressed && pacmanx > 0 && pacmanmap[pacmany][pacmanx - 1] != '#' && !gamenotready) {
                    pacmanx--;
                    leftPressed = true;

                }
                else if (!Keyboard::isKeyPressed(Keyboard::Left)) {
                    leftPressed = false;

                }

                if (Keyboard::isKeyPressed(Keyboard::Right) && !rightPressed && pacmanx < mapwidth - 1 && pacmanmap[pacmany][pacmanx + 1] != '#' && !gamenotready) {
                    pacmanx++;
                    rightPressed = true;
                }
                else if (!Keyboard::isKeyPressed(Keyboard::Right)) {
                    rightPressed = false;
                }

                if (Keyboard::isKeyPressed(Keyboard::Up) && !upPressed && pacmany > 0 && pacmanmap[pacmany - 1][pacmanx] != '#' && !gamenotready) {
                    pacmany--;
                    upPressed = true;
                }
                else if (!Keyboard::isKeyPressed(Keyboard::Up)) {
                    upPressed = false;
                }

                if (Keyboard::isKeyPressed(Keyboard::Down) && !downPressed && pacmany < mapheight - 1 && pacmanmap[pacmany + 1][pacmanx] != '#' && !gamenotready) {
                    pacmany++;
                    downPressed = true;
                }
                else if (!Keyboard::isKeyPressed(Keyboard::Down)) {
                    downPressed = false;
                }

               

                scoredis.setString("SCORE: \n     " + to_string(score));
                window.clear();



                for (int y = 0; y < mapheight; ++y) {
                    for (int x = 0; x < mapwidth; ++x) {
                        if (pacmanmap[y][x] == '#') {
                            wallSprite.setPosition(x * cellsize, y * cellsize);
                            window.draw(wallSprite);
                        }
                        else if (pacmanmap[y][x] == '0') {
                            dotbigSprite.setPosition(x * cellsize, y * cellsize);
                            window.draw(dotbigSprite);
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
                    gamenotready = false;
                    isgamewon = true;

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
                

                window.draw(scoredis);
                window.draw(loading);
                window.draw(border);


                window.display();

            }
        }
    }
    
    return 0;
}