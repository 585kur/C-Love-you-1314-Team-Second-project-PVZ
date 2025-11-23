#include "Entity.h"


Entity::Entity(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), alive(true)
{
}


int Entity::get_x() const { return x; }
int Entity::get_y() const { return y; }
int Entity::get_width() const { return width; }
int Entity::get_height() const { return height; }
bool Entity::is_alive() const { return alive; }
bool Entity::is_dead() const { return !alive; }


void Entity::set_x(int x) { this->x = x; }
void Entity::set_y(int y) { this->y = y; }
void Entity::set_position(int x, int y) {
    this->x = x;
    this->y = y;
}

void Entity::set_width(int width) { this->width = width; }
void Entity::set_height(int height) { this->height = height; }
void Entity::set_size(int width, int height) {
    this->width = width;
    this->height = height;
}

void Entity::set_alive(bool alive) { this->alive = alive; }
void Entity::kill() { this->alive = false; }