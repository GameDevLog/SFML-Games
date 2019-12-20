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

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

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
