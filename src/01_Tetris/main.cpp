#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

const int M = 20;
const int N = 10;

struct Point {
	int x, y;
} a[4], b[4];

int field[M][N] = {{ 0 }};

int figures[7][4] = {
		{ 1, 3, 5, 7 }, // I
		{ 2, 4, 5, 7 }, // Z
		{ 3, 5, 4, 6 }, // S
		{ 3, 5, 4, 7 }, // T
		{ 2, 3, 5, 7 }, // L
		{ 3, 5, 7, 6 }, // J
		{ 2, 3, 4, 5 }, // O
};

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
