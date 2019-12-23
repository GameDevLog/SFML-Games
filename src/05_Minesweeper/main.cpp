#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

int main() {
    srand(time(0));
    const int weight = 400;
    const int height = 400;
    RenderWindow window(VideoMode(weight, height), "GameDevLog");

    int w = 32;
    int grid[12][12];
    int sgrid[12][12]; // for showing

    Texture t;
    t.loadFromFile("images/tiles.jpg");
    Sprite s(t);

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            sgrid[i][j] = 10;
            if (rand() % 5 == 0) {
                grid[i][j] = 9;
            } else {
                grid[i][j] = 0;
            }
        }
    }

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            int n = 0;
            if (grid[i][j] == 9) { continue; }
            if (grid[i + 1][j] == 9) { n++; } // right
            if (grid[i][j + 1] == 9) { n++; } // bottom
            if (grid[i - 1][j] == 9) { n++; } // left
            if (grid[i][j - 1] == 9) { n++; } // top
            if (grid[i + 1][j + 1] == 9) { n++; }
            if (grid[i - 1][j - 1] == 9) { n++; }
            if (grid[i - 1][j + 1] == 9) { n++; }
            if (grid[i + 1][j - 1] == 9) { n++; }
            grid[i][j] = n;
        }
    }

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color::White);
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                sgrid[i][j] = grid[i][j];
                s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
                s.setPosition(i * w, j * w);
                window.draw(s);
            }
        }
        window.display();
    }

    return 0;
}
