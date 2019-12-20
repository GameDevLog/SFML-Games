#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

int main() {
    const int w = 320;
    const int h = 480;
    RenderWindow window(VideoMode(w, h), "GameDevLog");

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        window.display();
    }

    return 0;
}
