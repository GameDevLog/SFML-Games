#include <SFML/Graphics.hpp>
#include <ctime>
#include <list>
#include <cmath>

using namespace sf;

const int W = 1200;
const int H = 800;

float DEGTORAD = 0.017453f;

int main() {
    RenderWindow window(VideoMode(W, H), "GameDevLog");
    window.setFramerateLimit(60);

    Texture t1, t2;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");

    Sprite sPlayer(t1), sBackground(t2);
    sPlayer.setTextureRect(IntRect(40, 0, 40, 40));
    sPlayer.setOrigin(20, 20);

    float x = 300, y = 300;
    float dx = 0, dy = 0, angle = 0;
    bool thrust;

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) { angle += 3; }
        if (Keyboard::isKeyPressed(Keyboard::Left)) { angle -= 3; }

        if (Keyboard::isKeyPressed(Keyboard::Up)) { thrust = true; }
        else { thrust = false; }

        // spaceship movement
        if (thrust) {
            dx += cos(angle * DEGTORAD) * 0.2;
            dy += sin(angle * DEGTORAD) * 0.2;
        } else {
            dx *= 0.99;
            dy *= 0.99;
        }

        int maxSpeed = 15;
        float speed = sqrt(dx * dx + dy * dy);
        if (speed > maxSpeed) {
            dx *= maxSpeed / speed;
            dy *= maxSpeed / speed;
        }

        x += dx;
        y += dy;

        if (x > W) { x = 0; }
        if (x < 0) { x = W; }
        if (y > H) { y = 0; }
        if (y < 0) { y = H; }

        sPlayer.setPosition(x, y);
        sPlayer.setRotation(angle + 90);

        // draw
        window.clear();
        window.draw(sBackground);
        window.draw(sPlayer);
        window.display();
    }

    return 0;
}
