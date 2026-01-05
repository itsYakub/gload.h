#define GLOAD_IMPLEMENTATION
#include "./../../gload.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/VideoMode.hpp>


int main(void) {
    sf::Window  window(sf::VideoMode( { 800, 600 } ), "gload.h - SFML sample", sf::Style::Titlebar | sf::Style::Close);
    if (!window.setActive()) { return (1); }
    if (!gloadLoadGL()) { return (1); }

    while (window.isOpen()) {
        window.display();

        sf::Event event = { };
        while (window.pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::Closed): {
                    window.close();
                } break;

                default: { } break;
            }
        }
        
        
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);


        glBegin(GL_QUADS);
            glVertex2f(-0.5,-0.5);
            glVertex2f(-0.5, 0.5);
            glVertex2f( 0.5, 0.5);
            glVertex2f( 0.5,-0.5);
        glEnd();
    }
    
    if (!gloadUnloadGL()) { return (1); }
    
    return (0);
}
