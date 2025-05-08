#include "Graph.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <cmath>
#include <algorithm>
#include "GraphVisualizer.h"

std::map<std::string, sf::Vector2f> getOptimizedPositions(const std::vector<std::string>& cities, const Graph& graph) {
    std::map<std::string, sf::Vector2f> positions;
    const float radius = 300.0f;
    sf::Vector2f center(400.0f, 300.0f);

    std::vector<std::string> mainCities;
    std::map<std::string, std::vector<std::string>> cityLocations;

    for (const auto& location : cities) {
        size_t commaPos = location.find(',');
        std::string city = location.substr(0, commaPos);
        
        if (std::find(mainCities.begin(), mainCities.end(), city) == mainCities.end()) {
            mainCities.push_back(city);
        }
        cityLocations[city].push_back(location);
    }

    float angleStep = 360.0f / mainCities.size();
    for (size_t i = 0; i < mainCities.size(); ++i) {
        float angle = angleStep * i * 3.14159f / 180.0f;
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        
        const auto& locations = cityLocations[mainCities[i]];
        float localRadius = 50.0f + 20.0f * locations.size();
        float localAngleStep = 360.0f / locations.size();
        
        for (size_t j = 0; j < locations.size(); ++j) {
            float localAngle = localAngleStep * j * 3.14159f / 180.0f;
            positions[locations[j]] = sf::Vector2f(
                x + localRadius * cos(localAngle),
                y + localRadius * sin(localAngle)
            );
        }
    }

    return positions;
}

void GraphVisualizer::visualize(const Graph& graph) {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Advanced Graph Visualization");
    sf::View view = window.getDefaultView();
    sf::Vector2f dragStart;
    bool isDragging = false;
    float zoomLevel = 1.0f;
    const float minZoom = 0.1f;
    const float maxZoom = 5.0f;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return;
    }

    auto cities = graph.getAllCities();
    auto cityPositions = getOptimizedPositions(cities, graph);

    // Zmienne do zarządzania widocznością
    bool showLocalConnections = true;
    bool showIntercityConnections = true;
    bool showLocationNames = true;
    bool showCityNames = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Obsługa przeciągania
            else if (event.type == sf::Event::MouseButtonPressed && 
                    event.mouseButton.button == sf::Mouse::Left) {
                isDragging = true;
                dragStart = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            }
            else if (event.type == sf::Event::MouseButtonReleased && 
                    event.mouseButton.button == sf::Mouse::Left) {
                isDragging = false;
            }
            else if (event.type == sf::Event::MouseMoved && isDragging) {
                sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                sf::Vector2f delta = dragStart - newPos;
                view.move(delta);
                window.setView(view);
                dragStart = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            }
            // Obsługa zoomu
            else if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    sf::Vector2f mousePosBefore = window.mapPixelToCoords(
                        sf::Vector2i(event.mouseWheelScroll.x, event.mouseWheelScroll.y));
                    
                    float zoomFactor = (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
                    zoomLevel = std::clamp(zoomLevel * zoomFactor, minZoom, maxZoom);
                    view.zoom(zoomFactor);
                    
                    window.setView(view);
                    sf::Vector2f mousePosAfter = window.mapPixelToCoords(
                        sf::Vector2i(event.mouseWheelScroll.x, event.mouseWheelScroll.y));
                    
                    view.move(mousePosBefore - mousePosAfter);
                    window.setView(view);
                }
            }
            // Obsługa klawiatury
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::L) showLocalConnections = !showLocalConnections;
                if (event.key.code == sf::Keyboard::I) showIntercityConnections = !showIntercityConnections;
                if (event.key.code == sf::Keyboard::N) showLocationNames = !showLocationNames;
                if (event.key.code == sf::Keyboard::C) showCityNames = !showCityNames;
                if (event.key.code == sf::Keyboard::R) { // Reset widoku
                    view = window.getDefaultView();
                    zoomLevel = 1.0f;
                    window.setView(view);
                }
            }
        }

        window.clear(sf::Color(240, 240, 240));

        // Rysowanie połączeń
        for (const auto& city : cities) {
            auto neighbours = graph.getNeighbours(city);
            sf::Vector2f startPos = cityPositions[city];
            
            for (const auto& neighbour : neighbours) {
                sf::Vector2f endPos = cityPositions[neighbour.first];
                
                size_t commaPos1 = city.find(',');
                size_t commaPos2 = neighbour.first.find(',');
                bool isLocalConnection = (city.substr(0, commaPos1) == neighbour.first.substr(0, commaPos2));
                
                if ((isLocalConnection && !showLocalConnections) || 
                    (!isLocalConnection && !showIntercityConnections)) {
                    continue;
                }
                
                sf::Color lineColor = isLocalConnection ? sf::Color(100, 100, 255, 150) : 
                                                         sf::Color(255, 100, 100, 150);
                float thickness = isLocalConnection ? 1.0f : 2.0f;
                
                sf::Vector2f direction = endPos - startPos;
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                direction /= length;
                sf::Vector2f perpendicular(-direction.y, direction.x);
                
                sf::VertexArray line(sf::Quads, 4);
                line[0].position = startPos - perpendicular * thickness;
                line[1].position = startPos + perpendicular * thickness;
                line[2].position = endPos + perpendicular * thickness;
                line[3].position = endPos - perpendicular * thickness;
                
                for (int i = 0; i < 4; ++i) {
                    line[i].color = lineColor;
                }
                
                window.draw(line);
            }
        }

        // Rysowanie wierzchołków
        for (const auto& city : cities) {
            sf::Vector2f pos = cityPositions[city];
            size_t commaPos = city.find(',');
            bool isMainLocation = (city.find("Dworzec") != std::string::npos || 
                                 city.find("Centrum") != std::string::npos);
            
            float radius = isMainLocation ? 10.0f : 6.0f;
            sf::Color nodeColor = isMainLocation ? sf::Color::Red : sf::Color::Blue;
            
            sf::CircleShape node(radius);
            node.setFillColor(nodeColor);
            node.setPosition(pos.x - radius, pos.y - radius);
            window.draw(node);
            
            if ((showCityNames && isMainLocation) || (showLocationNames && !isMainLocation)) {
                sf::Text label;
                label.setFont(font);
                label.setString(city);
                label.setCharacterSize(isMainLocation ? 14 : 10);
                label.setFillColor(sf::Color::Black);
                label.setPosition(pos.x + radius + 2, pos.y - radius / 2);
                window.draw(label);
            }
        }

        // Wyświetlanie instrukcji
        sf::Text instructions;
        instructions.setFont(font);
        instructions.setString(
            "L - lokalne polaczenia\n"
            "I - miedzymiastowe\n"
            "N - nazwy lokacji\n"
            "C - nazwy miast\n"
            "R - reset widoku\n"
            "LPM + przeciagnij - przesun\n"
            "Scroll - zoom"
        );
        instructions.setCharacterSize(14);
        instructions.setFillColor(sf::Color::Black);
        instructions.setPosition(20, 20);
        window.draw(instructions);

        window.display();
    }
}