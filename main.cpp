#include <iostream>
#include <array>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#define RHO 28
#define SIGMA 10
#define BETA 8.0f / 3.0f
#define SCALE 8
#define DT 0.007
// #define DT 0.001
int NUM = 3000;
#define MOVERATE 2

using namespace sf;
using namespace std;

vector<array<double, 3>> points;
vector<Color> colors;
bool paused = true;
int xoff = 0;
int yoff = 0;

int first_var, second_var;

bool left_pressed = false;
bool right_pressed = false;
bool up_pressed = false;
bool down_pressed = false;

void populatePoints()
{
    for (int i = 0; i < NUM; i++)
    {
        points.push_back({(double)rand() / RAND_MAX * 50 - 25, (double)rand() / RAND_MAX * 50 - 25, (double)rand() / RAND_MAX * 50 - 25});
        colors.push_back(Color(rand() % 255, rand() % 255, rand() % 255));
    }
}

void updatePoints()
{
    for (int i = 0; i < points.size(); i++)
    {
        double dx = SIGMA * (points[i][1] - points[i][0]);
        double dy = points[i][0] * (RHO - points[i][2]) - points[i][1];
        double dz = points[i][0] * points[i][1] - BETA * points[i][2];

        points[i][0] += dx * DT;
        points[i][1] += dy * DT;
        points[i][2] += dz * DT;
    }
}

void handleControls()
{
    if (left_pressed)
        xoff -= MOVERATE;
    if (right_pressed)
        xoff += MOVERATE;
    if (down_pressed)
        yoff += MOVERATE;
    if (up_pressed)
        yoff -= MOVERATE;
}

int main()
{
    cout << "Enter number of points: ";
    cin >> NUM;
    cout << "Enter first var index";
    cin >> first_var;
    cout << "Enter second var index";
    cin >> second_var;

    RenderWindow window(VideoMode(600, 600), "Lorenz Attractor");
    window.setFramerateLimit(60);

    srand(time(NULL));
    populatePoints();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
                paused = !paused;

            // Left Key
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
                left_pressed = true;
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Left)
                left_pressed = false;

            // Right Key
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
                right_pressed = true;
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Right)
                right_pressed = false;

            // Up Key
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
                up_pressed = true;
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Up)
                up_pressed = false;

            // Down Key
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
                down_pressed = true;
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Down)
                down_pressed = false;
        }

        // Render
        window.clear(Color::Black);
        CircleShape shape(1.50f);
        shape.setOrigin(shape.getRadius(), shape.getRadius());

        for (int i = 0; i < points.size(); i++)
        {
            // shape.setRadius(points[i][2] * 0.28);
            shape.setFillColor(colors[i]);
            shape.setPosition(points[i][first_var] * SCALE + (window.getSize().x / 2) + xoff, points[i][second_var] * SCALE + (window.getSize().y / 2) + yoff);
            window.draw(shape);
        }

        window.display();

        // Update points
        if (!paused)
            updatePoints();
        handleControls();
    }
    return 0;
}