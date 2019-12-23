#include <SFML/Graphics.hpp>
#include <ctime>
#include <list>
#include <cmath>

using namespace sf;

const int W = 1200;
const int H = 800;

float DEGTORAD = 0.017453f;

class Animation {
public:
    float frame, speed;
    Sprite sprite;
    std::vector<IntRect> frames;

    Animation() {}

    Animation(Texture &t, int x, int y, int w, int h, int count, float Speed) {
        frame = 0;
        speed = Speed;

        for (int i = 0; i < count; i++) {
            frames.push_back(IntRect(x + i * w, y, w, h));
        }

        sprite.setTexture(t);
        sprite.setOrigin(w / 2, h / 2);
        sprite.setTextureRect(frames[0]);
    }

    void update() {
        frame += speed;
        int n = frames.size();
        if (frame >= n) {
            frame -= n;
        }
        if (n > 0) {
            sprite.setTextureRect(frames[int(frame)]);
        }
    }

    bool isEnd() {
        return frame + speed >= frames.size();
    }
};


class Entity {
public:
    float x, y, dx, dy, R, angle;
    bool life;
    std::string name;
    Animation anim;

    Entity() {
        life = 1;
    }

    void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1) {
        anim = a;
        x = X;
        y = Y;
        angle = Angle;
        R = radius;
    }

    virtual void update(){};

    void draw(RenderWindow &window) {
        anim.sprite.setPosition(x, y);
        anim.sprite.setRotation(angle + 90);
        window.draw(anim.sprite);
    }

    virtual ~Entity(){};
};

class Asteroid : public Entity {
public:
    Asteroid() {
        dx = rand() % 8 - 4;
        dy = rand() % 8 - 4;
        name = "Asteroid";
    }

    void update() {
        x += dx;
        y += dy;

        if (x > W) { x = 0; }
        if (x < 0) { x = W; }
        if (y > H) { y = 0; }
        if (y < 0) { y = H; }
    }
};

class Bullet : public Entity {
public:
    Bullet() {
        name = "Bullet";
    }

    void update() {
        dx = cos(angle * DEGTORAD) * 6;
        dy = sin(angle * DEGTORAD) * 6;
        // angle+=rand()%6-3;
        x += dx;
        y += dy;

        if (x > W || x < 0 || y > H || y < 0)
            life = 0;
    }
};

bool isCollide(Entity *a, Entity *b) {
    return (b->x - a->x) * (b->x - a->x)
        + (b->y - a->y) * (b->y - a->y)
        < (a->R + b->R) * (a->R + b->R);
}


int main() {
    RenderWindow window(VideoMode(W, H), "GameDevLog");
    window.setFramerateLimit(60);

    Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_blue.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");

    Sprite sPlayer(t1), sBackground(t2);
    sPlayer.setTextureRect(IntRect(40, 0, 40, 40));
    sPlayer.setOrigin(20, 20);

    Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
    sRock.sprite.setPosition(400, 400);

    std::list<Entity *> entities;

    for (int i = 0; i < 15; i++) {
        Asteroid *a = new Asteroid();
        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
        entities.push_back(a);
    }

    float x = 300, y = 300;
    float dx = 0, dy = 0, angle = 0;
    bool thrust;

    while (window.isOpen()) {
        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Space) {
                    Bullet *b = new Bullet();
                    b->settings(sBullet, x, y, angle, 10);
                    entities.push_back(b);
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) { angle += 3; }
        if (Keyboard::isKeyPressed(Keyboard::Left)) { angle -= 3; }

        if (Keyboard::isKeyPressed(Keyboard::Up)) { thrust = true; }
        else { thrust = false; }

        for (auto a : entities) {
            for (auto b : entities) {
                if (a->name == "Asteroid" && b->name == "Bullet") {
                    if (isCollide(a, b)) {
                        a->life = false;
                        b->life = false;
                    }
                }
            }
        }

        // spaceship movement
        if (thrust) {
            dx += cos(angle * DEGTORAD) * 0.2;
            dy += sin(angle * DEGTORAD) * 0.2;
        } else {
            dx *= 0.99;
            dy *= 0.99;
        }

        int maxSpeed = 15;
        float speed = sqrt(dx * dx + dy * dy);
        if (speed > maxSpeed) {
            dx *= maxSpeed / speed;
            dy *= maxSpeed / speed;
        }

        x += dx;
        y += dy;

        if (x > W) { x = 0; }
        if (x < 0) { x = W; }
        if (y > H) { y = 0; }
        if (y < 0) { y = H; }

        sPlayer.setPosition(x, y);
        sPlayer.setRotation(angle + 90);

        for (auto i = entities.begin(); i != entities.end();) {
            Entity *e = *i;

            e->update();
            e->anim.update();

            if (e->life == false) {
                i = entities.erase(i);
                delete e;
            } else {
                i++;
            }
        }

        // draw
        window.clear();
        window.draw(sBackground);
        window.draw(sPlayer);

        for (auto i : entities) {
            i->draw(window);
        }

        window.display();
    }

    return 0;
}
