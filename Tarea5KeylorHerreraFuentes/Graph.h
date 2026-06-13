#pragma once

#include <string>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "SplayDictionary.h"
#include "DLinkedList.h"
#include "MinHeap.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include <limits>
#include <queue>
#include <vector>

using std::string;
using std::runtime_error;
using std::to_string;
using std::sqrt;

class Graph {
private:
    Dictionary<int, GraphNode>* nodes;
    DLinkedList<GraphEdge>* neighbors;
    int max;

    sf::RenderWindow* window;
    sf::Font font;

    float dist(int n1, int n2) {
        GraphNode node1 = nodes->getValue(n1);
        GraphNode node2 = nodes->getValue(n2);
        sf::Vector2f a(node1.x, node1.y);
        sf::Vector2f b(node2.x, node2.y);
        sf::Vector2f dif = b - a;
        return sqrt(dif.x * dif.x + dif.y * dif.y);
    }

    void reverse(List<int>* list) {
        List<int>* reversedList = new DLinkedList<int>();
        list->goToEnd();
        while (!list->atStart()) {
            reversedList->append(list->getElement());
            list->previous();
        }
        reversedList->append(list->getElement());
        list->clear();
        reversedList->goToStart();
        while (!reversedList->atEnd()) {
            list->append(reversedList->getElement());
            reversedList->next();
        }
        delete reversedList;
    }

    void drawEdges() {
        for (int i = 0; i < max; i++) {
            for (neighbors[i].goToStart(); !neighbors[i].atEnd(); neighbors[i].next()) {
                GraphEdge e = neighbors[i].getElement();
                GraphNode n1 = nodes->getValue(e.source);
                GraphNode n2 = nodes->getValue(e.target);

                sf::Vertex line[2];
                line[0].position = sf::Vector2f(n1.x + NODE_SIZE, n1.y + NODE_SIZE);
                line[0].color = sf::Color::White;
                line[1].position = sf::Vector2f(n2.x + NODE_SIZE, n2.y + NODE_SIZE);
                line[1].color = sf::Color::White;
                window->draw(line, 2, sf::PrimitiveType::Lines);
            }
        }
    }

    void drawNodes() {
        List<GraphNode>* nodeList = nodes->getValues();

        for (nodeList->goToStart(); !nodeList->atEnd(); nodeList->next()) {
            GraphNode n = nodeList->getElement();
            sf::CircleShape circle(NODE_SIZE + 2);
            circle.setFillColor(sf::Color::Green);
            circle.setPosition(n.x - 2, n.y - 2);
            window->draw(circle);

            sf::CircleShape circle2(NODE_SIZE);
            circle2.setFillColor(sf::Color::Blue);
            circle2.setPosition(n.x, n.y);
            window->draw(circle2);

            sf::Text text(n.label, font);
            int charSize = 10;
            text.setCharacterSize(charSize);
            text.setFillColor(sf::Color::White);
            text.setPosition(n.x, n.y + NODE_SIZE - charSize / 2 - 1);
            text.setStyle(sf::Text::Bold);
            window->draw(text);
        }
        delete nodeList;
    }


    bool edgeExists(int source, int target) {
        for (neighbors[source].goToStart(); !neighbors[source].atEnd(); neighbors[source].next()) {
            GraphEdge e = neighbors[source].getElement();
            if (e.target == target) return true;
        }
        return false;
    }

    float edgeWeight(int source, int target) {
        for (neighbors[source].goToStart(); !neighbors[source].atEnd(); neighbors[source].next()) {
            GraphEdge e = neighbors[source].getElement();
            if (e.target == target) return e.weight;
        }
        throw runtime_error("Edge not found.");
    }

    void initializeSingleSource(std::vector<float>& dist, std::vector<int>& prev, int source) {
        dist.assign(max, std::numeric_limits<float>::infinity());
        prev.assign(max, -1);
        dist[source] = 0.0f;
    }

    int extractMin(std::vector<float>& dist, std::vector<bool>& sptSet) {
        float min = std::numeric_limits<float>::infinity();
        int min_index = -1;

        for (int v = 0; v < max; ++v) {
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }
        return min_index;
    }

    List<int>* getNeighbors(int node) {
        List<int>* neighborsList = new DLinkedList<int>();
        neighbors[node].goToStart();
        while (!neighbors[node].atEnd()) {
            neighborsList->append(neighbors[node].getElement().target);
            neighbors[node].next();
        }
        return neighborsList;
    }

    List<int>* constructPath(std::vector<int>& prev, int target) {
        List<int>* path = new DLinkedList<int>();
        for (int at = target; at != -1; at = prev[at]) {
            path->append(at);
        }
        reverse(path);
        return path;
    }

public:
    Graph(int max, sf::RenderWindow* window) {
        if (max < 1) throw runtime_error("Invalid number of nodes.");
        nodes = new SplayDictionary<int, GraphNode>();
        neighbors = new DLinkedList<GraphEdge>[max];
        this->max = max;

        this->window = window;
        font.loadFromFile("arial.ttf");
        std::srand(std::time(0));
    }

    ~Graph() {
        delete nodes;
        delete[] neighbors;
    }

    void addNode(float x, float y, string label) {
        GraphNode node;
        node.x = x;
        node.y = y;
        node.label = label;
        nodes->insert(nodes->getSize(), node);
    }

    void addRandomNodes(int quantity) {
        for (int i = 0; i < quantity; i++) {
            float x = static_cast<float>(std::rand() % (WIDTH - 2 * NODE_SIZE));
            float y = static_cast<float>(std::rand() % (HEIGHT - 2 * NODE_SIZE));
            addNode(x, y, "N" + to_string(i));
        }
    }

    void addEdge(int source, int target, float weight) {
        if (!nodes->contains(source) || !nodes->contains(target))
            throw runtime_error("Invalid nodes.");

        GraphEdge edge;
        edge.source = source;
        edge.target = target;
        edge.weight = weight;
        neighbors[source].append(edge);

        edge.source = target;
        edge.target = source;
        edge.weight = weight;
        neighbors[target].append(edge);
    }

    void addRandomEdges(int quantity) {
        for (int i = 0; i < quantity; i++) {
            int source = std::rand() % max;
            int target = std::rand() % max;
            addEdge(source, target, dist(source, target));
        }
    }

    void addClosestEdges(float minDistance) {
        List<int>* nodeKeys = nodes->getKeys();
        nodeKeys->goToStart();
        for (int i = 0; i < nodeKeys->getSize(); i++) {
            nodeKeys->goToPos(i);
            int n = nodeKeys->getElement();
            for (int j = i + 1; j < nodeKeys->getSize(); j++) {
                if (dist(i, j) < minDistance) {
                    addEdge(i, j, dist(i, j));
                }
            }
        }
    }

    void drawPath(List<int>* nodeList) {
        if (nodeList->getSize() < 2)
            throw runtime_error("Not enough nodes in list.");

        for (nodeList->goToStart(); !nodeList->atEnd(); nodeList->next()) {
            if (!nodes->contains(nodeList->getElement()))
                throw runtime_error("Invalid node in list.");
        }

        nodeList->goToStart();
        int source = nodeList->getElement();
        nodeList->next();

        while (!nodeList->atEnd()) {
            int target = nodeList->getElement();
            GraphNode n1 = nodes->getValue(source);
            GraphNode n2 = nodes->getValue(target);

            sf::Vertex line[2];
            line[0].position = sf::Vector2f(n1.x + NODE_SIZE, n1.y + NODE_SIZE);
            line[1].position = sf::Vector2f(n2.x + NODE_SIZE, n2.y + NODE_SIZE);

            if (edgeExists(source, target)) {
                line[0].color = sf::Color::Green; 
                line[1].color = sf::Color::Green; 
            }
     

            window->draw(line, 2, sf::PrimitiveType::Lines);
            nodeList->next();
            source = target;
        }
    }

    void draw() {
        drawEdges();
        drawNodes();
    }

    int getUpperLeftNode() {
        if (nodes->getSize() < 1)
            throw runtime_error("There are no nodes in the graph.");

        List<int>* nodeKeys = nodes->getKeys();
        nodeKeys->goToStart();
        int result = nodeKeys->getElement();
        GraphNode upperLeft = nodes->getValue(result);
        float value = upperLeft.x + upperLeft.y;
        nodeKeys->next();

        while (!nodeKeys->atEnd()) {
            upperLeft = nodes->getValue(nodeKeys->getElement());
            if (upperLeft.x + upperLeft.y < value) {
                result = nodeKeys->getElement();
                value = upperLeft.x + upperLeft.y;
            }
            nodeKeys->next();
        }
        delete nodeKeys;
        return result;
    }

    int getLowerRightNode() {
        if (nodes->getSize() < 1)
            throw runtime_error("There are no nodes in the graph.");

        List<int>* nodeKeys = nodes->getKeys();
        nodeKeys->goToStart();
        int result = nodeKeys->getElement();
        GraphNode upperLeft = nodes->getValue(result);
        float value = upperLeft.x + upperLeft.y;
        nodeKeys->next();

        while (!nodeKeys->atEnd()) {
            upperLeft = nodes->getValue(nodeKeys->getElement());
            if (upperLeft.x + upperLeft.y > value) {
                result = nodeKeys->getElement();
                value = upperLeft.x + upperLeft.y;
            }
            nodeKeys->next();
        }
        delete nodeKeys;
        return result;
    }

    List<int>* dijkstra() {
        int source = getUpperLeftNode();
        int target = getLowerRightNode();

        std::vector<float> dist(max);
        std::vector<int> prev(max);
        std::vector<bool> sptSet(max, false);

        initializeSingleSource(dist, prev, source);

        for (int count = 0; count < max - 1; ++count) {
            int u = extractMin(dist, sptSet);
            if (u == -1) break;
            sptSet[u] = true;

            List<int>* neighborsList = getNeighbors(u);
            neighborsList->goToStart();
            while (!neighborsList->atEnd()) {
                int v = neighborsList->getElement();
                if (!sptSet[v] && dist[u] + edgeWeight(u, v) < dist[v]) {
                    dist[v] = dist[u] + edgeWeight(u, v);
                    prev[v] = u;
                }
                neighborsList->next();
            }
            delete neighborsList;
        }

        if (dist[target] == std::numeric_limits<float>::infinity()) {
            return new DLinkedList<int>();
        }

        return constructPath(prev, target);
    }
};

