#pragma once

#include <graphics.h>

class Entity {
protected:
 
    int x;
    int y;

 
    int width;
    int height;

    bool alive;

public:

    Entity(int x, int y, int width, int height);


    virtual ~Entity() = default;

 
    virtual void draw() const = 0;

    int get_x() const;
    int get_y() const;
    void set_x(int x);
    void set_y(int y);
    void set_position(int x, int y);

    int get_width() const;
    int get_height() const;
    void set_width(int width);
    void set_height(int height);
    void set_size(int width, int height);

    bool is_alive() const;
    bool is_dead() const; 
    void set_alive(bool alive);
    void kill(); 
};