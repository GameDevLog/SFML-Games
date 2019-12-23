#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>

using namespace sf;

const int num = 8; // checkpoints
int points[num][2] = {300, 610,
                      1270, 430,
                      1380, 2380,
                      1900, 2460,
                      1970, 1700,
                      2550, 1680,
                      2560, 3150,
                      500, 3300};

struct Car {
    float x, y, speed, angle;
    int n;

    Car() {
        speed = 2;
        angle = 0;
        n = 0;
    }

    void move() {
        x += sin(angle) * speed;
        y -= cos(angle) * speed;
    }

    void findTarget() {
        float tx = points[n][0];
        float ty = points[n][1];
        float beta = angle - atan2(tx - x, -ty + y);
        if (sin(beta) < 0) {
             angle += 0.005 * speed;
        } else {
            angle -= 0.005 * speed;
        }
        if ((x - tx) * (x - tx) + (y - ty) * (y - ty) < 25 * 25) {
            n = (n + 1) % num;
        }
    }
};

int main() {
    const int w = 640;
    const int h = 480;
    RenderWindow window(VideoMode(w, h), "GameDevLog");
	window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/car.png");
    t1.setSmooth(true);
    t2.setSmooth(true);

    Sprite sBackground(t1), sCar(t2);
    sBackground.scale(2, 2);

    sCar.setOrigin(22, 22);
    float R = 22;

    const int N = 5;
    Car car[N];
    for (int i = 0; i < N; i++) {
        car[i].x = 300 + i * 50;
        car[i].y = 1700 + i * 80;
        car[i].speed = 7 + i;
    }

    float speed = 0, angle = 0;
    float maxSpeed = 12.0;
    float acc = 0.2, dec = 0.3;
    float turnSpeed = 0.08;

    int offsetX = 0, offsetY = 0;

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        bool Up = false, Right = false, Down = false, Left = false;
        if (Keyboard::isKeyPressed(Keyboard::Up)) { Up = true; }
        if (Keyboard::isKeyPressed(Keyboard::Right)) { Right = true; }
        if (Keyboard::isKeyPressed(Keyboard::Down)) { Down = true; }
        if (Keyboard::isKeyPressed(Keyboard::Left)) { Left = true; }

        // car movement
        if (Up && speed < maxSpeed) {
            if (speed < 0) {
                speed += dec;
            } else {
                speed += acc;
            }
        }
        if (Down && speed > -maxSpeed) {
            if (speed > 0) {
                speed -= dec;
            } else {
                speed -= acc;
            }
        }
        if (!Up && !Down) {
            if (speed - dec > 0) {
                speed -= dec;
            } else if (speed + dec < 0) {
                speed += acc;
            } else {
                speed = 0;
            }
        }

        if (Right && speed != 0) {
            angle += turnSpeed * speed / maxSpeed;
        }
        if (Left && speed != 0) {
            angle -= turnSpeed * speed / maxSpeed;
        }

        car[0].speed = speed;
        car[0].angle = angle;

        for (int i = 0; i < N; i++) {
            car[i].move();
        }
        for (int i = 1; i < N; i++) {
            car[i].findTarget();
        }

        // collision
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int dx = 0, dy = 0;
                while (dx * dx + dy * dy < 4 * R * R) {
                    car[i].x += dx / 10.0;
                    car[i].x += dy / 10.0;
                    car[j].x -= dx / 10.0;
                    car[j].y -= dy / 10.0;
                    dx = car[i].x - car[j].x;
                    dy = car[i].y - car[j].y;
                    if (!dx && !dy) {
                        break;
                    }
                }
            }
        }

        // draw
        window.clear(Color::White);

        if (car[0].x > 320) {
            offsetX = car[0].x - 320;
        }
        if (car[0].y > 240) {
            offsetY = car[0].y - 240;
        }

        sBackground.setPosition(-offsetX, -offsetY);
        window.draw(sBackground);

        Color colors[10] = {Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White};

        for (int i = 0; i < N; i++) {
            sCar.setPosition(car[i].x - offsetX, car[i].y - offsetY);
            sCar.setRotation(car[i].angle * 180 / M_PI);
            sCar.setColor(colors[i]);
            window.draw(sCar);
        }

        window.display();
    }

    return 0;
}
