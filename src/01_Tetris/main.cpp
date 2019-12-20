#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

const int M = 20;
const int N = 10;

struct Point {
    int x, y;
} origin[4], tmp[4];

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

    int dx = 0;
    bool rotate = 0;
    int colorNum = 1;

    float timer = 0f;
    float delay = 0.3f;

    Clock clock;

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }
        
        if (e.type == Event::KeyPressed){
            if (e.key.code == Keyboard::Up) {
                rotate = true;
            } else if (e.key.code == Keyboard::Left) {
                dx = -1;
            } else if (e.key.code == Keyboard::Right) {
                dx = 1;
            }
        }

        // move
        for (int i = 0; i < 4; i++) {
            tmp[i] = origin[i];
            origin[i].x += dx;
        }
        
        // rotate
        if (rotate) {
            Point p = origin[1]; // center of rotation
            for (int i = 0; i < 4; i++) {
                int x = origin[i].y - p.y;
                int y = origin[i].x - p.x;
                origin[i].x = p.x - x;
                origin[i].y = p.y + y;
            }
        }

        int n = 3;
        if (origin[0].x == 0) {
            for (int i = 0; i < 4; i++) {
                origin[i].x = figures[n][i] % 2;
                origin[i].y = figures[n][i] / 2;
            }
        }

        dx = 0;
        rotate = false;

        window.clear(Color::White);

        for (int i = 0; i < 4; i++) {
            s.setPosition(origin[i].x * 18, origin[i].y * 18);
            window.draw(s);
        }

        window.display();
    }

    return 0;
}
