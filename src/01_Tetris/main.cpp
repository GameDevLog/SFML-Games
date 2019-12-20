#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

int main() {
    const int w = 320;
    const int h = 480;
    RenderWindow window(VideoMode(w, h), "GameDevLog");

    Texture t;
    t.loadFromFile("images/tiles.png");

    Sprite s(t);
    s.setTextureRect(IntRect(0, 0, 18, 18));

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color::White);
        window.draw(s);
        window.display();
    }

    return 0;
}
