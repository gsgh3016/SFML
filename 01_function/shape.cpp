#include "shape.h"

std::vector<Shape> shape_list;
int next_id = 0;

void create_rectangle(Point& pos1, Point& pos2){
    Shape rect;
    Point center;
    center = {(pos1.x + pos2.x)/2, (pos1.y + pos2.y)/2};
    rect.id = next_id; rect.type = ShapeType::RECT; rect.pos1 = pos1; rect.pos2 = pos2;
    rect.center = center;
    rect.rect =  std::make_unique<sf::RectangleShape>();
    shape_list.push_back(rect);
    next_id++;
}

void create_circle(Point& center, int radius){
    Shape circle;
    Point pos1, pos2;
    circle.id = next_id; circle.type = ShapeType::CIRCLE; circle.center = center; circle.radius = radius;
    pos1 = {center.x - radius, center.y - radius}; pos2 = {center.x + radius, center.y + radius};
    circle.pos1 = pos1; circle.pos2 = pos2;
    circle.circle = std::make_unique<sf::CircleShape>();
    shape_list.push_back(circle);
    next_id++;
}

void move_shape(int id, int x, int y){
    Shape& obj = shape_list[id];
    Point new_center;
    new_center.x = x; new_center.y = y;
    int dx = x - obj.center.x;
    int dy = y - obj.center.y;

    if (obj.type == ShapeType::CIRCLE) {
        obj.center = new_center;
    }
    else {
        obj.center = new_center;
        obj.pos1.x += dx; obj.pos1.y += dy;
        obj.pos2.x += dx; obj.pos2.y += dy;
    }
}

void sort_shapes(){
    auto comp = [](Shape a, Shape b){
        double areaA, areaB;
        if(a.type == ShapeType::RECT){
            areaA = (a.pos2.x - a.pos1.x) * (a.pos2.y - a.pos1.y);
        }
        else{
            areaA = M_PI * a.radius * a.radius;
        }

        if(b.type == ShapeType::RECT){
            areaB = (b.pos2.x - b.pos1.x) * (b.pos2.y - b.pos1.y);
        }
        else{
            areaB = M_PI * b.radius * b.radius;
        }

        return areaA <= areaB;
    };
    std::sort(shape_list.begin(), shape_list.end(), comp);
}

int find_furthest_shape(){
    std::vector<int> distance;
    auto getVec = [&distance](Shape i){
        distance.push_back(i.center.x*i.center.x + i.center.y*i.center.y);
    };
    std::for_each(shape_list.begin(), shape_list.end(), getVec);
    auto d = std::max_element(distance.begin(), distance.end()) - distance.begin();
    return shape_list[d].id;
}

void remove_shape_by_id(int id){
    auto id_match = [id](Shape i){return i.id == id;};
    shape_list.erase(std::remove_if(shape_list.begin(),
                                    shape_list.end(),
                                    id_match),
                     shape_list.end());
}

void align_shapes(){
    sort_shapes();
    Point pos2 = {0, 0};
    auto align = [&pos2](Shape& i){
        if(i.type == ShapeType::RECT){
            int h = i.pos2.y - i.pos1.y;
            int w = i.pos2.x - i.pos1.x;
            int min_l = h < w ? h : w;  // using for increasing pos2
            int max_l = h > w ? h : w;  // using for checking x>0, y>0
            if(max_l/2 > pos2.x + min_l/2){
                i.center = {max_l/2, max_l/2};
            }
            else{
                i.center = {pos2.x + min_l/2, pos2.y + min_l/2};
            }
            i.pos1 = {i.center.x - w/2, i.center.y - h/2};
            i.pos2 = {i.center.x + w/2, i.center.y + h/2};
            pos2 = {i.center.x + min_l/2, i.center.y + min_l/2};
        }
        else{
            i.pos1 = pos2;
            i.center = {pos2.x + i.radius, pos2.y + i.radius};
            i.pos2 = {pos2.x + 2*i.radius, pos2.y + 2*i.radius};
            pos2 = i.pos2;
        }
    };
    std::for_each(shape_list.begin(),
                  shape_list.end(),
                  align);
}

void print_shapes(){
    auto print = [](Shape i){
        std::cout << std::fixed << std::setprecision(2) <<" ID: " << i.id;
        if (i.type == ShapeType::RECT){
            std::cout << ", Type: RECT, Position: (" << i.center.x << ", " << i.center.y
            << "), Width: " << i.pos2.x - i.pos1.x << ", Height: " << i.pos2.y - i.pos1.y
            << ", Area: " << (double)(i.pos2.x - i.pos1.x) * (i.pos2.y - i.pos1.y) << std::endl;
        }
        else{
            std::cout << ", Type: CIRCLE, Center: (" << i.center.x << ", " << i.center.y
                      << "), Radius: " << i.radius << ", Area: " << std::setw(7) << M_PI * i.radius * i.radius << std::endl;
        }
    };
    std::for_each(shape_list.begin(),
                  shape_list.end(),
                  print);
}

void draw_shapes(sf::RenderWindow& window) {
  for (auto& shape : shape_list) {
    if (shape.type == ShapeType::RECT) {
      shape.rect->setSize(sf::Vector2f(shape.pos2.x - shape.pos1.x, shape.pos2.y - shape.pos1.y));
      shape.rect->setPosition(shape.pos1.x, shape.pos1.y);
      shape.rect->setFillColor(sf::Color::White);
      window.draw(*shape.rect);
    } else {
      shape.circle->setRadius(shape.radius);
      shape.circle->setPosition(shape.center.x - shape.radius, shape.center.y - shape.radius);
      shape.circle->setFillColor(sf::Color::White);
      window.draw(*shape.circle);
    }
    std::shared_ptr<sf::CircleShape> point = std::make_shared<sf::CircleShape>();
    point->setRadius(5);
    point->setPosition(shape.center.x-5, shape.center.y-5);
    point->setFillColor(sf::Color::Black);
    window.draw(*point);
  }
}