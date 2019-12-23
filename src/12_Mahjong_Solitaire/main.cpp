#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>

using namespace sf;

int field[50][50][50] = { 0 };

int &f(int x, int y, int z) { return field[y + 2][x + 2][z]; }
int &f(Vector3i v) { return f(v.x, v.y, v.z); }

bool isOpen(int x, int y, int z) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (f(x + 2, y + i, z) > 0 && f(x - 2, y + j, z) > 0) {
                return false;
            }
        }
    }

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (f(x + i, y + j, z + 1) > 0) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    srand(time(0));

    const int width = 740;
    const int height = 570;
    RenderWindow window(VideoMode(width, height), "GameDevLog");

    Texture t1, t2;
    t1.loadFromFile("files/tiles.png");
    t2.loadFromFile("files/background.png");

    Sprite s(t1), sBackground(t2);

    int w = 48, h = 66;
    int stepX = w / 2 - 2, stepY = h / 2 - 2;
    float offX = 4.6, offY = 7.1; // z offset

    // load from file
    std::fstream myfile("files/map.txt");
    for (int y = 0; y < 18; y++) {
        for (int x = 0; x < 30; x++) {
            char a;
            myfile >> a;
            int n = a - '0';
            for (int z = 0; z < n; z++) {
                if (f(x - 1, y - 1, z)) {
                    f(x - 1, y, z) = f(x, y - 1, z) = 0;
                } else {
                    f(x, y, z) = 1;
                }
            }
        }
    }

    // shuffle
    for (int k = 1;; k++) {
        std::vector<Vector3i> opens;
        for (int z = 0; z < 10; z++) {
            for (int y = 0; y < 18; y++) {
                for (int x = 0; x < 30; x++) {
                    if (f(x, y, z) > 0 && isOpen(x, y, z)) {
                        opens.push_back(Vector3i(x, y, z));
                    }
                }
            }
        }
        int n = opens.size();
        if (n < 2) {
            break;
        }

        int a = 0, b = 0;
        while (a == b) {
            a = rand() % n;
            b = rand() % n;
        }
        f(opens[a]) = -k;
        f(opens[b]) = -k;
        k %= 42;
    }

    for (int z = 0; z < 10; z++) {
        for (int y = 0; y < 18; y++) {
            for (int x = 0; x < 30; x++) {
                f(x, y, z) *= -1;
            }
        }
    }

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sBackground);
        for (int z = 0; z < 10; z++) {
            for (int x = 30; x >= 0; x--) {
                for (int y = 0; y < 18; y++) {
                    int k = f(x, y, z);
                    if (k == 0) {
                        continue;
                    }
                    s.setTextureRect(IntRect(k * w, 0, w, h));
                    s.setPosition(x * stepX + z * offX, y * stepY - z * offY);
                    window.draw(s);
                }
            }
        }

        window.display();
    }

    return 0;
}
