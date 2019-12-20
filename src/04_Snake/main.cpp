#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

int N = 30, M = 20;
int size = 16;
int w = size * N;
int h = size * M;

int dir, num = 4;

struct Snake {
    int x, y;
} snake[100];

struct Fruit {
    int x, y;
} fruit;

void Tick() {
    for (int i = num; i > 0; --i) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }

    if (dir == 0) { snake[0].y += 1; }
    if (dir == 1) { snake[0].x -= 1; }
    if (dir == 2) { snake[0].x += 1; }
    if (dir == 3) { snake[0].y -= 1; }
    
    if ((snake[0].x == fruit.x) && (snake[0].y == fruit.y)) {
        num++;
        fruit.x = rand() % N;
        fruit.y = rand() % M;
    }
}

int main() {
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "GameDevLog");

    Texture t1, t2;
    t1.loadFromFile("images/white.png");
    t2.loadFromFile("images/red.png");

    Sprite whiteSprite(t1);
    Sprite redSprite(t2);

    Clock clock;
    float timer = 0, delay = 0.1;

    fruit.x = 10;
    fruit.y = 10;

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

        
        if (Keyboard::isKeyPressed(Keyboard::Left)) { dir = 1; }
        if (Keyboard::isKeyPressed(Keyboard::Right)) { dir = 2; }
        if (Keyboard::isKeyPressed(Keyboard::Up)) { dir = 3; }
        if (Keyboard::isKeyPressed(Keyboard::Down)) { dir = 0; }

        if (timer > delay) {
            timer = 0;
            Tick();
        }

        // draw
        window.clear();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                whiteSprite.setPosition(i * size, j * size);
                window.draw(whiteSprite);
            }
        }

        for (int i = 0; i < num; i++) {
            redSprite.setPosition(snake[i].x * size, snake[i].y * size);
            window.draw(redSprite);
        }
        
        redSprite.setPosition(fruit.x * size, fruit.y * size);
        window.draw(redSprite);

        window.display();
    }

    return 0;
}
