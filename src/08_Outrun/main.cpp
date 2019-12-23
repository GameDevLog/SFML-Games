#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>

using namespace sf;

int width = 1024;
int height = 768;
int roadW = 2000;
int segL = 200;    // segment length
float camD = 0.84; // camera depth

struct Line {
    float x, y, z; // 3d center of line
    float X, Y, W; // screen coord
    float curve, spriteX, clip, scale;
    Sprite sprite;

    Line() {
        spriteX = curve = x = y = z = 0;
    }

    void project(int camX, int camY, int camZ) {
        scale = camD / (z - camZ);
        X = (1 + scale * (x - camX)) * width / 2;
        Y = (1 - scale * (y - camY)) * height / 2;
        W = scale * roadW * width / 2;
    }
};

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
    std::vector<Line> lines;

    for (int i = 0; i < 1600; i++) {
        Line line;
        line.z = i * segL;
        lines.push_back(line);
    }

    int N = lines.size();

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        // draw road
        for (int n = 0; n < 300; n++) {
            Line &l = lines[n % N];
            l.project(0, 1500, 0);

            Color grass = (n / 3) % 2 ? Color(16, 200, 16) : Color(0, 154, 0);
            Color rumble = (n / 3) % 2 ? Color(255, 255, 255) : Color(0, 0, 0);
            Color road = (n / 3) % 2 ? Color(107, 107, 107) : Color(105, 105, 105);

            Line p = lines[(n - 1) % N]; // previous line

            drawQuad(window, grass, 0, p.Y, width, 0, l.Y, width);
            drawQuad(window, rumble, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2);
            drawQuad(window, road, p.X, p.Y, p.W, l.X, l.Y, l.W);
        }
        
        window.display();
    }

    return 0;
}
