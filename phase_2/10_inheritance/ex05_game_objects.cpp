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
#include <string>
#include <iostream>
#include <cmath>


struct Vec2 {
	double x, y;
	Vec2 operator+(const Vec2& o) const {
		return {x+o.x, y+o.y};
	}
	
	Vec2& operator+=(const Vec2& o) {
		x+=o.x; y+=o.y;
		return *this;
	}
};


class GameObject {

public:
	// Constructor
	GameObject(const std::string& name, Vec2 pos) : name_(name), pos_(pos) {};

	// Virtual Methods with no default implementation
	virtual void update() = 0;              // called each frame
	virtual void render() const = 0;        // draw to console
	virtual std::string type() const = 0;

	virtual bool is_alive() const { return true; }

	// Destructor
	virtual ~GameObject() = default;

	// Common interface (non-virtual)
	const std::string& name() const {
		return name_;
	}

	const Vec2& position() const {
		return pos_;
	}

	void set_position(Vec2 pos) {
		pos_ = pos;
	}

protected:
	std::string name_;
	Vec2 pos_;

};



class Player : public GameObject {

public:
	Player(const std::string& name, Vec2 pos, int hp, int max_hp, Vec2 velocity) 
		: GameObject(name, pos) , hp_(hp), max_hp_(max_hp), velocity_(velocity) {}

	void update() override {
		pos_ += velocity_;
	}

	void render() const override {
		//"[P] Name (x, y) HP: 80/100"
		std::cout << "[P] " << name_ << " (" << pos_.x << ", " << pos_.y << ") " << "HP: " << hp_ << "/" << max_hp_ << std::endl;
	}

	std::string type() const override {
		return "Player";
	}

	void take_damage(int amount) {
		hp_ = (hp_ - amount > 0) ? (hp_ - amount) : 0; 
	}

	void heal(int amount) {
		hp_ = (hp_ + amount > max_hp_) ? (max_hp_) : (hp_ + amount); 
	}

	bool is_alive() const override {
		return hp_ > 0 ;
	}

protected:
	int hp_, max_hp_;
	Vec2 velocity_;

};


class Enemy : public GameObject {

public:
	Enemy(const std::string& name, Vec2 pos, int hp, int damage, double speed) 
		: GameObject(name, pos) , hp_(hp), damage_(damage), speed_(speed) {}

	void update() override {
		double dx = target_.x - pos_.x;                                                                                                                                                
		double dy = target_.y - pos_.y;
		double dist = std::sqrt(dx * dx + dy * dy);                                                                                                                                    
                                                                                                                                                                           
		if (dist > speed_) {                                                                                                                                                           
			// Move toward target by speed_ units
			pos_.x += (dx / dist) * speed_;                                                                                                                                            
			pos_.y += (dy / dist) * speed_;                                                                                                                                          
		} else {
			// Close enough — snap to target
			pos_ = target_;                                                                                                                                                            
		}
	}

	void render() const override {
		//"[P] Name (x, y) HP: 80/100"
		std::cout << "[E] " << name_ << " (" << pos_.x << ", " << pos_.y << ") " << "HP: " << hp_ << std::endl;
	}

	std::string type() const override {
		return "Enemy";
	}

	void set_target(Vec2 target) {
		target_ = target;
	}


	bool is_alive() const override {
		return hp_ > 0 ;
	}

protected:
	int hp_, damage_;
	double speed_;
	Vec2 target_;

};


class Projectile : public GameObject {

public:
	Projectile(const std::string& name, Vec2 pos, Vec2 velocity, int damage, int lifetime) 
		: GameObject(name, pos), velocity_(velocity), damage_(damage), lifetime_(lifetime) {}

	void update() override {
		pos_ += velocity_;
		--lifetime_;
	}

	void render() const override {
		std::cout << "[*] (" << pos_.x << ", " << pos_.y << ")" << std::endl;
	}

	std::string type() const override {
		return "Projectile";
	}

	bool is_alive() const override {
		return lifetime_ >= 0;
	}


private:
	Vec2 velocity_;
	int damage_, lifetime_;

};



class Collectible : public GameObject {

public:
	Collectible(const std::string& name, Vec2 pos, std::string effect, bool collected) 
		: GameObject(name, pos), effect_(effect), collected_(collected) {}

	void update() override {
		return;
	}

	void render() const override{
		if (!collected_) {
			std::cout << "[C] " << name_  << "(" << pos_.x << ", " << pos_.y << ")" << std::endl;
		}
	}

	void collect() {
		collected_ = true;
	}

	std::string type() const override {
		return "Collectible";
	}

	bool is_alive() const override {
		return !collected_;
	}

private:
	std::string effect_;
	bool collected_;

};


class GameWorld {

public:
	void add(GameObject* obj) {
		objects_.push_back(obj);
	}

	void update()  {
		// calls update() on all alive objects
		for (auto& obj : objects_) {
			if (obj->is_alive()) {
				obj->update();
			}
		}

	}

	void render() const {
		// calls render() on all alive objects
		for (auto& obj : objects_) {
			if (obj->is_alive()) {
				obj->render();
			}
		}
	}

	void remove_dead() {
		// removes and deletes objects where !is_alive()

		for (auto it = objects_.begin(); it != objects_.end(); ) {
			if (!(*it)->is_alive()) {
				delete *it;
				it = objects_.erase(it);  // erase returns the next valid iterator
			} else {
			++it;
			}
  		} 
	}

	int count() const {
		// number of alive objects
		int alive_count = 0;
		for (auto& obj : objects_) {
			if (obj->is_alive()) {
				++alive_count;
			}
		}
		return alive_count;
	}

	~GameWorld() {
		// deletes all remaining objects
		for (auto it = objects_.begin(); it != objects_.end(); ) {
			delete *it;
			it = objects_.erase(it);  // erase returns the next valid iterator
  		} 
	}

private:
	std::vector<GameObject*> objects_;

};


int main() {

	//   - Create a GameWorld
	GameWorld world{};
	//   - Add a Player, 3 Enemies, 2 Projectiles, 1 Collectible

	// 1 player
	Player player("cool guy", Vec2{1.0, 2.0}, 100, 100, Vec2{1.0, 1.0});
	world.add(&player);

	// 3 enemies
	Enemy enemy1("bad guy", Vec2{4.0, 5.0}, 50, 5, .1);
	Enemy enemy2("really bad guy", Vec2{7.0, 2.0}, 75, 5, .1);
	Enemy enemy3("very bad guy", Vec2{3.0, 10.0}, 75, 5, .1);
	world.add(&enemy1);
	world.add(&enemy2);
	world.add(&enemy3);

	// 2 projectiles
	Projectile gun("name", Vec2{1.1, 2.2}, Vec2{10.0, 10.0}, 10, 100);
	Projectile arrow("name", Vec2{2.1, 1.2}, Vec2{1.0, 1.0}, 10, 10);
	world.add(&gun);
	world.add(&arrow);

	// 1 collectible
	Collectible diamond("diamond", Vec2{0.5, 0.2}, "makes you rich", false);
	world.add(&diamond);
	//   - Run a game loop for 10 frames:
	//       world.update();
	//       world.render();
	//       world.remove_dead();
	//       // Add some interactions: damage player, collect items, etc.
	//   - Print final state

	for (int i = 0; i < 10; ++i) {
		world.update();
		world.render();
		world.remove_dead();
	}



}



