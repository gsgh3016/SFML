#include "shape.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Drawing Shapes");
    sf::View view(sf::FloatRect(0, SCREEN_HEIGHT, SCREEN_WIDTH, -SCREEN_HEIGHT));
    window.setView(view);

    bool isQuit = false;
    while(window.isOpen()&&!isQuit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        while(!isQuit) {
            std::string command;
            std::cin >> command;
            if (command == "RECT") {
                int x1, y1, x2, y2;
                Point r1, r2;
                std::cin >> x1 >> y1 >> x2 >> y2;
                r1.x = x1; r1.y = y1; r2.x = x2; r2.y = y2;
                create_rectangle(r1, r2);
            }
            else if (command == "CIRCLE"){
                int cx, cy, r;
                Point c;
                std::cin >>  cx >> cy >> r;
                c.x = cx; c.y = cy;
                create_circle(c, r);
            }
            else if (command == "MOVE"){
                int id, x, y;
                std::cin >> id >> x >> y;
                move_shape(id, x, y);
            }
            else if (command == "SORT"){
                sort_shapes();
            }
            else if (command == "MAX"){
                find_furthest_shape();
            }
            else if (command == "REMOVE"){
                int id;
                std::cin >> id;
                remove_shape_by_id(id);
            }
            else if (command == "ALIGN"){
                align_shapes();
            }
            else if (command == "PRINT"){
                print_shapes();
            }
            else if (command == "DRAW"){
                draw_shapes(window);
            }
            else if (command == "QUIT") {
                isQuit = true;
            }
            else {
                std::cout << "Invalid command." << std::endl;
            }
        }
    }
    return 0;
}
