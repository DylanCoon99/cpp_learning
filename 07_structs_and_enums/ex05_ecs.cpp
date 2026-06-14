// Exercise 5: Simple Entity-Component System
//
// Task: Build a basic Entity-Component System (ECS) — a pattern used
//       heavily in game development. This ties together structs, enums,
//       vectors, and functions from the entire phase.
//
// Overview:
//   - An Entity is just an ID (int)
//   - Components are data attached to entities
//   - Systems are functions that operate on entities with specific components
//
// Define these component structs:
//
//   struct Position {
//       int entity_id;
//       double x, y;
//   };
//
//   struct Velocity {
//       int entity_id;
//       double dx, dy;
//   };
//
//   struct Health {
//       int entity_id;
//       int current;
//       int max;
//       bool is_alive() const { return current > 0; }
//   };
//
//   enum class EntityType { Player, Enemy, Item };
//
//   struct Entity {
//       int id;
//       std::string name;
//       EntityType type;
//   };
//
// Define a World struct that holds all the data:
//
//   struct World {
//       std::vector<Entity> entities;
//       std::vector<Position> positions;
//       std::vector<Velocity> velocities;
//       std::vector<Health> healths;
//       int next_id = 0;
//
//       int create_entity(const std::string& name, EntityType type);
//       void add_position(int id, double x, double y);
//       void add_velocity(int id, double dx, double dy);
//       void add_health(int id, int hp);
//
//       // Helpers to find components by entity ID:
//       Position* get_position(int id);
//       Velocity* get_velocity(int id);
//       Health* get_health(int id);
//   };
//
// Implement these "system" functions (free functions that operate on World):
//
//   void movement_system(World& world)
//     — For every entity that has both Position and Velocity,
//       update position: x += dx, y += dy
//
//   void damage_system(World& world, int entity_id, int damage)
//     — Reduce the entity's health by damage (min 0)
//
//   void print_world(const World& world)
//     — Print all entities and their components
//
// In main():
//   - Create a world
//   - Add a Player entity with position, velocity, and health
//   - Add 2 Enemy entities with position and health
//   - Add 1 Item entity with only position
//   - Print the world state
//   - Run movement_system a few times
//   - Apply damage to an enemy
//   - Print the world state again
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_ecs.cpp

// YOUR CODE HERE
