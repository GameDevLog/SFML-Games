#include <SFML/Graphics.hpp>
#include <ctime>
#include <list>
#include <cmath>

using namespace sf;

const int W = 1200;
const int H = 800;

int main() {
    RenderWindow window(VideoMode(W, H), "GameDevLog");
    window.setFramerateLimit(60);

    Texture t1, t2;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");

    Sprite sPlayer(t1), sBackground(t2);
    sPlayer.setTextureRect(IntRect(40, 0, 40, 40));
    sPlayer.setOrigin(20, 20);

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        // draw
        window.clear();
        window.draw(sBackground);
        window.draw(sPlayer);
        window.display();
    }

    return 0;
}
