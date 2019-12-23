#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>

using namespace sf;

int width = 1024;
int height = 768;

void drawQuad(RenderWindow &w, Color c, int x1, int y1, int w1, int x2, int y2, int w2) {
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1 - w1, y1));
    shape.setPoint(1, Vector2f(x2 - w2, y2));
    shape.setPoint(2, Vector2f(x2 + w2, y2));
    shape.setPoint(3, Vector2f(x1 + w1, y1));
    w.draw(shape);
}

int main() {
    RenderWindow window(VideoMode(width, height), "GameDevLog");

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        drawQuad(window, Color::Green, 500, 500, 200, 500, 300, 100);
        window.display();
    }

    return 0;
}
