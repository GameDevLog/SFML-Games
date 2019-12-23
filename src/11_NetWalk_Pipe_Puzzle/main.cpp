#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

const int N = 6;
int ts = 54; // tile size
Vector2f offset(65, 55);

struct pipe {
    int orientation;
    bool on;
};

pipe grid[N][N];

int main() {
    srand(time(0));

    const int w = 390;
    const int h = 390;
    RenderWindow window(VideoMode(w, h), "GameDevLog");

    Texture t1, t2, t3, t4;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/comp.png");
    t3.loadFromFile("images/server.png");
    t4.loadFromFile("images/pipes.png");
    t4.setSmooth(true);

    Sprite sBackground(t1), sComp(t2), sServer(t3), sPipe(t4);
    sPipe.setOrigin(27, 27);

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
            if (e.type == Event::MouseButtonPressed) {
                if (e.mouseButton.button == Mouse::Left) {
                    Vector2i pos = Mouse::getPosition(window) + Vector2i(ts / 2, ts / 2) - Vector2i(offset);
                    pos /= ts;
                    grid[pos.x][pos.y].orientation++;
                }
            }
        }

        window.clear();
        window.draw(sBackground);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                pipe &p = grid[j][i];
                sPipe.setTextureRect(IntRect(ts * 2, 0, ts, ts));
                sPipe.setRotation(p.orientation * 90);
                sPipe.setPosition(j * ts, i * ts);
                sPipe.move(offset);
                window.draw(sPipe);
            }
        }

        window.display();
    }

    return 0;
}
