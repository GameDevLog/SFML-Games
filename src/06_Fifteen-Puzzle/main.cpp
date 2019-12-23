#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

int main() {
    const int weight = 256;
    const int height = 256;
    RenderWindow window(VideoMode(weight, height), "GameDevLog");
    window.setFramerateLimit(60);

    Texture t;
    t.loadFromFile("images/15.png");

    int w = 64;
    int grid[6][6] = { 0 };
    Sprite sprite[20];

    int n = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            n++;
            sprite[n].setTexture(t);
            sprite[n].setTextureRect(IntRect(i * w, j * w, w, w));
            grid[i + 1][j + 1] = n;
        }
    }

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }

            if (e.type == Event::MouseButtonPressed) {
                if (e.mouseButton.button == Mouse::Left) {
                    Vector2i pos = Mouse::getPosition(window);
                    int x = pos.x / w + 1;
                    int y = pos.y / w + 1;

                    int dx = 0;
                    int dy = 0;

                    if (grid[x + 1][y] == 16) { dx = 1; dy = 0; }
                    if (grid[x][y + 1] == 16) { dx = 0; dy = 1; }
                    if (grid[x][y - 1] == 16) { dx = 0; dy = -1; }
                    if (grid[x - 1][y] == 16) { dx = -1; dy = 0; }

                    int n = grid[x][y];
                    grid[x][y] = 16;
                    grid[x + dx][y + dy] = n;

                    // animation
                    sprite[16].move(-dx * w, -dy * w);
                    float speed = 5;

                    for (int i = 0; i < w; i += speed) {
                        sprite[n].move(speed * dx, speed * dy);
                        window.draw(sprite[16]);
                        window.draw(sprite[n]);
                        window.display();
                    }
                }
            }
        }

        window.clear(Color::White);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int n = grid[i + 1][j + 1];
                sprite[n].setPosition(i * w, j * w);
                window.draw(sprite[n]);
            }
        }
        window.display();
    }

    return 0;
}
