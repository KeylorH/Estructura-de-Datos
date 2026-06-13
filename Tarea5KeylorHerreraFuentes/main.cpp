#define WIDTH 1068
#define HEIGHT 800
#define NODE_SIZE 12
#define NODES 60
#define CONNECT_DISTANCE 160

#include <SFML/Graphics.hpp>
#include "Graph.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Grafo!");
    Graph graph(NODES, &window);
    graph.addRandomNodes(NODES);
    graph.addClosestEdges(CONNECT_DISTANCE);
    List<int>* path = graph.dijkstra();

    // Bucle principal de la aplicación
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        graph.draw();
        if (path->getSize() > 1) {
            graph.drawPath(path);
        }
        window.display();
    }
    delete path;
    return 0;
}