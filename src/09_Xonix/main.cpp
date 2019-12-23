#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

const int M = 25;
const int N = 40;

int grid[M][N] = { 0 };
int ts = 18; // tile size

int main() {
    srand(time(0));

    RenderWindow window(VideoMode(N * ts, M * ts), "GameDevLog");
    window.setFramerateLimit(60);

    Texture t1;
    t1.loadFromFile("images/tiles.png");

    Sprite sTile(t1);

    int x = 0, y = 0, dx = 0, dy = 0;
    float timer = 0, delay = 0.07;
    Clock clock;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1) {
                grid[i][j] = 1;
            }
        }
    }

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) { dx = -1;  dy = 0; };
        if (Keyboard::isKeyPressed(Keyboard::Right)) { dx = 1; dy = 0; };
        if (Keyboard::isKeyPressed(Keyboard::Up)) { dx = 0; dy = -1; };
        if (Keyboard::isKeyPressed(Keyboard::Down))  { dx = 0; dy = 1; };

        if (timer > delay) {
            x += dx;
            y += dy;

            if (x < 0) { x = 0; }
            if (x > N - 1) { x = N - 1; }
            if (y < 0) { y = 0; }
            if (y > M - 1) { y = M - 1; }

            if (grid[y][x] == 0) { grid[y][x] = 2; }
            timer = 0;
        }

        // draw
        window.clear();

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) { continue; }
                if (grid[i][j] == 1) { sTile.setTextureRect(IntRect(0, 0, ts, ts)); }
                if (grid[i][j] == 2) { sTile.setTextureRect(IntRect(54, 0, ts, ts)); }
                sTile.setPosition(j * ts, i * ts);
                window.draw(sTile);
            }
        }

        sTile.setTextureRect(IntRect(36, 0, ts, ts));
        sTile.setPosition(x * ts, y * ts);
        window.draw(sTile);

        window.display();
    }

    return 0;
}
