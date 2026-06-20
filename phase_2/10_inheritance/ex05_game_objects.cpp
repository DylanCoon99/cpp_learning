// Exercise 5: Game Object Hierarchy
//
// Task: Build a game object system using inheritance and polymorphism.
//       This builds on your ECS work but uses an OOP hierarchy instead.
//
// Define:
//
//   struct Vec2 {
//       double x, y;
//       Vec2 operator+(const Vec2& o) const { return {x+o.x, y+o.y}; }
//       Vec2& operator+=(const Vec2& o) { x+=o.x; y+=o.y; return *this; }
//   };
//
//   class GameObject (abstract base):
//       GameObject(const std::string& name, Vec2 pos);
//       virtual void update() = 0;              // called each frame
//       virtual void render() const = 0;        // draw to console
//       virtual std::string type() const = 0;
//       virtual bool is_alive() const { return true; }
//       virtual ~GameObject() = default;
//
//       // Common interface (non-virtual)
//       const std::string& name() const;
//       const Vec2& position() const;
//       void set_position(Vec2 pos);
//
//   protected:
//       std::string name_;
//       Vec2 pos_;
//
//   class Player : public GameObject
//       Additional: int hp_, int max_hp_, Vec2 velocity_
//       update(): position += velocity
//       render(): prints "[P] Name (x, y) HP: 80/100"
//       void take_damage(int amount);
//       void heal(int amount);
//       bool is_alive() const override;
//
//   class Enemy : public GameObject
//       Additional: int hp_, int damage_, double speed_
//       update(): moves toward a target position (simple: move x/y by speed)
//       render(): prints "[E] Name (x, y) HP: 30"
//       void set_target(Vec2 target);
//       bool is_alive() const override;
//
//   class Projectile : public GameObject
//       Additional: Vec2 velocity_, int damage_, int lifetime_ (frames)
//       update(): position += velocity, decrement lifetime
//       render(): prints "[*] (x, y)"
//       bool is_alive() const override — false when lifetime <= 0
//
//   class Collectible : public GameObject
//       Additional: std::string effect_, bool collected_
//       update(): does nothing (static object)
//       render(): prints "[C] effect_name (x, y)" or nothing if collected
//       void collect();
//       bool is_alive() const override — false when collected
//
// class GameWorld:
//   - Holds a std::vector<GameObject*>
//   - void add(GameObject* obj);
//   - void update() — calls update() on all alive objects
//   - void render() const — calls render() on all alive objects
//   - void remove_dead() — removes and deletes objects where !is_alive()
//   - int count() const — number of alive objects
//   - ~GameWorld() — deletes all remaining objects
//
// In main():
//   - Create a GameWorld
//   - Add a Player, 3 Enemies, 2 Projectiles, 1 Collectible
//   - Run a game loop for 10 frames:
//       world.update();
//       world.render();
//       world.remove_dead();
//       // Add some interactions: damage player, collect items, etc.
//   - Print final state
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_game_objects.cpp

// YOUR CODE HERE
