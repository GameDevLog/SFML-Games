#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

struct point {
    int x;
    int y;
};

int main() {
    srand(time(0));

    const int w = 400;
    const int h = 533;
    RenderWindow window(VideoMode(w, h), "GameDevLog");
    window.setFramerateLimit(60);

    Texture t1,t2,t3;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/platform.png");
    t3.loadFromFile("images/doodle.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3);

    point plat[20];

    for (int i = 0; i < 10 ; i++) {
       plat[i].x = rand() % w;
       plat[i].y = rand() % h;
    }

    int x = 100, y = 100, height = 200;
    float dx = 0, dy = 0;

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            x += 3;
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            x -= 3;
        }

        dy += 0.2f;
        y += dy;

        if (y > 500) {
            dy = -10;
        }

        if (y < height) {
            for (int i = 0; i < 10; i++) {
                y = height;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533) {
                    plat[i].y = 0;
                    plat[i].x = rand() % 400;
                }
            }
        }

        for (int i = 0; i < 10; i++) {
            if ((x + 50 > plat[i].x)
                && (x + 20 < plat[i].x + 68)
                && (y + 70 > plat[i].y)
                && (y + 70 < plat[i].y + 14)
                && (dy > 0)) {
                dy = -10;
            }
        }

        sPers.setPosition(x, y);

        window.draw(sBackground);
        window.draw(sPers);

        for (int i = 0; i < 10; i++) {
            sPlat.setPosition(plat[i].x, plat[i].y);
            window.draw(sPlat);
        }

        window.display();
    }

    return 0;
}
