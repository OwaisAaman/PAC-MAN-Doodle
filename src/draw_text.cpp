#include "functions.h"
#include "header_text.h"

void draw_text(sf::Font& font, sf::Font& font_b, sf::RenderWindow& window) {
    header_text top_row("PAC MAN", 50, font, sf::Color::Yellow, 1);
    header_text middle_row("Written in C++ by agabhi017", 25, font_b, sf::Color::Yellow, 1);
    header_text bottom_row("Press any key to start", 30, font_b, sf::Color::Yellow, 1);

    sf::Vector2u window_size = window.getSize();

    top_row.m_text.setPosition(window_size.x / 2, 30);
    middle_row.m_text.setPosition(window_size.x / 2, window_size.y / 2);
    bottom_row.m_text.setPosition(window_size.x / 2, window_size.y - 30);

    window.draw(top_row.m_text);
    window.draw(middle_row.m_text);
    window.draw(bottom_row.m_text);
}