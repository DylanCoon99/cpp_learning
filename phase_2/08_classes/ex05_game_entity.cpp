// Exercise 5: Game Entity — Refactoring to Classes
//
// Task: Take the ECS concepts from step 07 ex05 and refactor them
//       into proper classes with encapsulation.
//
// Define these classes:
//
//   class Vec2 {
//   public:
//       Vec2(double x = 0.0, double y = 0.0);
//       double x() const;
//       double y() const;
//       void set(double x, double y);
//       Vec2 operator+(const Vec2& other) const;   // preview of step 09
//       Vec2& operator+=(const Vec2& other);
//       void print() const;
//   private:
//       double x_, y_;
//   };
//
//   class Entity {
//   public:
//       Entity(const std::string& name, int max_hp);
//
//       // Getters
//       int id() const;
//       const std::string& name() const;
//       const Vec2& position() const;
//       const Vec2& velocity() const;
//       int hp() const;
//       int max_hp() const;
//       bool is_alive() const;
//
//       // Setters — return *this for chaining
//       Entity& set_position(double x, double y);
//       Entity& set_velocity(double dx, double dy);
//
//       // Actions
//       void update();                            // position += velocity
//       void take_damage(int amount);             // clamp hp to 0
//       void heal(int amount);                    // clamp hp to max_hp
//
//       void print() const;
//
//   private:
//       static int next_id_;
//       int id_;
//       std::string name_;
//       Vec2 position_;
//       Vec2 velocity_;
//       int hp_;
//       int max_hp_;
//   };
//
//   class World {
//   public:
//       World() = default;
//
//       Entity& spawn(const std::string& name, int max_hp);
//         // creates entity, stores in vector, returns reference
//
//       void update();       // calls update() on all living entities
//       void print() const;  // prints all entities
//
//       Entity* find(const std::string& name);  // find by name
//       int alive_count() const;
//       int dead_count() const;
//
//   private:
//       std::vector<Entity> entities_;
//   };
//
// In main():
//   - Create a World
//   - Spawn a player and 3 enemies with different positions/velocities/hp
//   - Print the world
//   - Run update() 3 times, print again
//   - Deal damage to enemies, kill one
//   - Print alive/dead counts
//   - Heal the player
//   - Print final state
//
// This exercise shows the shift from "structs + free functions" (procedural)
// to "classes with methods" (object-oriented). Compare to your step 07 version.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_game_entity.cpp

// YOUR CODE HERE
