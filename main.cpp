#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const float PI = 3.1415926;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Window");

    float threadLength = 300.f;
    float radius = 30.f;
    float g = 10.f;
    float speed = 0;
    float T = 2 * PI * sqrt(threadLength / g);
    sf::Vector2f startPos = { 400.f, threadLength };

    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Red);
    circle.setOrigin({ radius, radius });

    circle.setPosition({ 400.f, threadLength });

    sf::VertexArray line(sf::PrimitiveType::Lines, 2);


    sf::CircleShape c(threadLength);
    c.setOrigin({ threadLength, threadLength });
    c.setPosition({ 400.f, 0.f });

    c.setFillColor(sf::Color::Transparent);   // без заливки
    c.setOutlineColor(sf::Color::Black);      // цвет линии
    c.setOutlineThickness(1.f);               // толщина линии

    sf::Clock clock;

    sf::Font font;
    font.openFromFile("arial.ttf");

    while (window.isOpen())
    {

        sf::Text text(font, "Speed: " + std::to_string(speed) + "\nX: " + std::to_string(circle.getPosition().x), 24);
        text.setFillColor(sf::Color::Black);
        text.setPosition({ 0.f, 0.f });

        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Vector2f cursorPos = sf::Vector2f(sf::Mouse::getPosition(window));

        line[0].position = circle.getPosition();
        line[0].color = sf::Color::Black;

        line[1].position = sf::Vector2f(window.getSize().x / 2, 0);
        line[1].color = sf::Color::Black;

        float x0 = circle.getPosition().x;
        float y0 = circle.getPosition().y;

        float x = cursorPos.x;
        float y = cursorPos.y;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (x - x0) * (x - x0) + (y - y0) * (y - y0) <= radius * radius) {
            //Moving the ball by cursor
            speed = 0; g = 10.f / 200.f;
            circle.setPosition({ x,sqrt(threadLength * threadLength - (x - 400.f) * (x - 400.f)) });
            startPos = { x0, y0 };

        }
        if (!(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
            //The ball starts oscillating
            if (startPos.x != 400.f && startPos.y != threadLength) {

                // Колебание началось справа
                if (startPos.x > 400.f) {
                    // Грузик движется от начальной координаты до конечной так, что эти координаты равноудаленны от центра равновесия
                    if (x0 > 800.f - startPos.x) {
                        x0 -= speed;
                        circle.setPosition({ x0, sqrt(threadLength * threadLength - (x0 - 400.f) * (x0 - 400.f)) });

                        if (x0 < 400.f) {
                            speed = speed- g * dt;
                        }
                        else {
                            speed = speed + g * dt;
                        }
                    }
                    // Меняем начало колебание на лево для периодичности
                    else {
                        startPos.x = 800.f - startPos.x;
                        speed = 0;
                    }
                }
                // Колебание началось слева
                else if (startPos.x < 400.f) {
                    // Грузик движется от начальной координаты до конечной так, что эти координаты равноудаленны от центра равновесия
                    if (x0 < 800.f - startPos.x) {
                        x0 += speed;
                        circle.setPosition({ x0, sqrt(threadLength * threadLength - (x0 - 400.f) * (x0 - 400.f)) });

                        if (x0 > 400.f) {
                            speed = speed - g * dt;
                        }
                        else {
                            speed = speed + g * dt;
                        }
                    }
                    // // Меняем начало колебание на право для периодичности
                    else {
                        startPos.x = 800.f - startPos.x;
                        speed = 0;
                    }
                }
            }

        }

        window.clear(sf::Color::White); // Background
        window.draw(circle);
        window.draw(line);
        window.draw(c);
        window.draw(text);
        window.display();
    }

    return 0;
}
