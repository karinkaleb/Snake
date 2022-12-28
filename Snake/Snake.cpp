#include <SFML/Graphics.hpp> //подключенте библиотеки графики
#include <time.h>

using namespace sf;

int N = 30, M = 30;//размер игрового поля

int size = 16;//размер картинок
int w = size * N;
int h = size * M;

int dir, num = 4;

struct Snake //змейка
{
    int x, y;
}  s[100];

struct Fruit //фрукт
{
    int x, y;
} f;

void Tick()
{
    for (int i = num; i > 0; --i)
    {
        s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
    }//для корректого отоброжения змейки

    if (dir == 0) s[0].y += 1; //управление змейки     
    if (dir == 1) s[0].x -= 1;
    if (dir == 2) s[0].x += 1;
    if (dir == 3) s[0].y -= 1;

    if ((s[0].x == f.x) && (s[0].y == f.y)) //появление фруктов
    {
        num++; f.x = rand() % N; f.y = rand() % M;
    }

    if (s[0].x > N) s[0].x = 0;  if (s[0].x < 0) s[0].x = N; // ограничение игрового поля по бокам(чтобы змейка выходила с другой стороны)
    if (s[0].y > M) s[0].y = 0;  if (s[0].y < 0) s[0].y = M;

    for (int i = 1; i < num; i++)
        if (s[0].x == s[i].x && s[0].y == s[i].y)  num = i; // обнуление змейки при столкновении с собой
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Snake Game!"); //имя окна с игрой

    Texture t1, t2, t3;
    t1.loadFromFile("images/white.png"); //подключение картинок
    t2.loadFromFile("images/red.png");
    t3.loadFromFile("images/green.png");
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);

    Clock clock;
    float timer = 0, delay = 0.1;

    f.x = 10;
    f.y = 10;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time; //внутриигровое время

        Event e;
        while (window.pollEvent(e)) //закрытие программы
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;   //управление влево
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 2;    //управление вправао 
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3; //управление вверх
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0; //управление вниз

        if (timer > delay) { timer = 0; Tick(); }

        ////// draw  ///////
        window.clear();

        for (int i = 0; i < N; i++) //создание игрового поля
            for (int j = 0; j < M; j++)
            {
                sprite1.setPosition(i * size, j * size);  window.draw(sprite1);
            }

        for (int i = 0; i < num; i++) //отоброжение змейки
        {
            sprite2.setPosition(s[i].x * size, s[i].y * size);  window.draw(sprite2);
        }

        sprite3.setPosition(f.x * size, f.y * size);  window.draw(sprite3);    //отоброжение фруктов

        window.display();
    }

    return 0;
}
