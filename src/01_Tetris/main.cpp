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

bool check() {
    for (int i = 0; i < 4; i++) {
        if (origin[i].x < 0 || origin[i].x >= N || origin[i].y >= M) {
            return false;
        } else if (field[origin[i].y][origin[i].x]) {
            return false;
        }
    }

    return true;
}

int main() {
    srand(time(0));

    const int w = 320;
    const int h = 480;
    RenderWindow window(VideoMode(w, h), "GameDevLog");

    Texture t1;
    Texture t2;
    Texture t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/background.png");
    t3.loadFromFile("images/frame.png");

    Sprite s(t1);
    Sprite background(t2);
    Sprite frame(t3);

    int dx = 0;
    bool rotate = false;
    int colorNum = 1;

    float timer = 0.0f;
    float delay = 0.3f;

    Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
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
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            delay = 0.05f;
        }

        // move
        for (int i = 0; i < 4; i++) {
            tmp[i] = origin[i];
            origin[i].x += dx;
        }
        
        // check
        if (!check()) {
            for (int i = 0; i < 4; i++) {
                origin[i] = tmp[i];
            }
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

            // check
            if (!check()) {
                for (int i = 0; i < 4; i++) {
                    origin[i] = tmp[i];
                }
            }
        }

        // tick
        if (timer > delay) {
            for (int i = 0; i < 4; i++) {
                tmp[i] = origin[i];
                origin[i].y += 1;
            }

            if (!check()) {
                for (int i = 0; i < 4; i++) {
                    field[tmp[i].y][tmp[i].x] = colorNum;
                }

                colorNum = 1 + rand() % 7;
                int n = rand() % 7;
                for (int i = 0; i < 4; i++) {
                    origin[i].x = figures[n][i] % 2;
                    origin[i].y = figures[n][i] / 2;
                }
            }

            timer = 0;
        }

        // check lines
        int k = M - 1;
        for (int i = M - 1; i > 0; i--) {
            int count = 0;
            for (int j = 0; j < N; j++) {
                if (field[i][j]) {
                    count++;
                }
                field[k][j] = field[i][j];
            }
            if (count < N) {
                k--;
            }
        }

        dx = 0;
        rotate = false;
        delay = 0.3f;

        // draw
        window.clear(Color::White);
        window.draw(background);

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (field[i][j] == 0) {
                    continue;
                }

                s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                s.setPosition(j * 18, i * 18);
                s.move(28, 31); //offset
                window.draw(s);
            }
        }

        for (int i = 0; i < 4; i++) {
            s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            s.setPosition(origin[i].x * 18, origin[i].y * 18);
            s.move(28, 31); //offset
            window.draw(s);
        }

        window.draw(frame);
        window.display();
    }

    return 0;
}
