#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

int main() {
    const int w = 640;
    const int h = 480;
    RenderWindow window(VideoMode(w, h), "GameDevLog");
	window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/car.png");

    Sprite sBackground(t1), sCar(t2);
    sBackground.scale(2, 2);

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        // draw
        window.clear(Color::White);
        window.draw(sBackground);
        window.draw(sCar);
        window.display();
    }

    return 0;
}
