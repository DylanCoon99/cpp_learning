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
#include <iostream>


	class Vec2 {
	public:
		Vec2(double x = 0.0, double y = 0.0) : x_(x), y_(y) {};

		double x() const  {
			return x_;
		}

		double y() const {
			return y_;
		}

		void set(double x, double y) {
			x_ = x; y_ = y;
		}

		Vec2 operator+(const Vec2& other) const {
			// preview of step 09
			return Vec2(x_ + other.x_, y_ + other.y_);
		}  

		Vec2& operator+=(const Vec2& other) {
			x_ += other.x_;
			y_ += other.y_;
			return *this;
		}

		void print() const {
			std::cout << "X: " << std::to_string(x_) << std::endl;
			std::cout << "Y: " << std::to_string(y_) << std::endl;
		}

	private:
		double x_, y_;
	};

	class Entity {
	public:
		Entity(const std::string& name, int max_hp) : name_(name), max_hp_(max_hp), hp_(max_hp), id_(next_id_) {
			++next_id_;
		}

		// Getters
		int id() const {
			return id_;
		}

		const std::string& name() const {
			return name_;
		}

		const Vec2& position() const {
			return position_;
		}

		const Vec2& velocity() const {
			return velocity_;
		}

		int hp() const {
			return hp_;
		}

		int max_hp() const {
			return max_hp_;
		}

		bool is_alive() const {
			return hp_ > 0;
		}

		// Setters — return *this for chaining
		Entity& set_position(double x, double y) {
			position_ = Vec2(x, y);
			return *this;
		}

		Entity& set_velocity(double dx, double dy) {
			velocity_ = Vec2(dx, dy);
			return *this;
		}

		// Actions
		void update() {
			// position += velocity
			position_ += velocity_;
		}

		void take_damage(int amount) {
			// clamp hp to 0
			hp_ = (hp_ - amount < 0) ? 0 : (hp_ - amount);
		}
		void heal(int amount) {
			// clamp hp to max_hp
			hp_ = (hp_ + amount > max_hp_) ? max_hp_ : (hp_ + amount);
		}

		void print() const {
			std::cout << "Name: " << name_ << std::endl;
			std::cout << "Position: " << std::endl;;
			position_.print();
			std::cout << "Velocity: " << std::endl;;
			velocity_.print();
			std::cout << "HP: " << hp_ << std::endl;
			std::cout << "Max HP: " << max_hp_ << std::endl;

		}

	private:
		static int next_id_;
		int id_;
		std::string name_;
		Vec2 position_;
		Vec2 velocity_;
		int hp_;
		int max_hp_;
	};


	class World {
	public:
		World() = default;

		Entity& spawn(const std::string& name, int max_hp) {
			// creates entity, stores in vector, returns reference
			Entity entity = Entity(name, max_hp);
			entities_.push_back(entity);
			return entities_.back(); // not sure if this is ok. I would be returning a local reference
		}
		

		void update() {
			// calls update() on all living entities
			for (Entity& e : entities_) {
				if (e.is_alive()) {
					e.update();
				}
			}
		}


		void print() const {
			// prints all entities
			for (const Entity& e : entities_) {
				e.print();
				std::cout << std::endl;
			}
		}


		Entity* find(const std::string& name) {
			// find by name
			for (Entity& e : entities_) {
				if (e.name() == name) {
					return &e;
				}
			}

			return nullptr;
		}

		int alive_count() const {
			int alive_count = 0;

			for (const Entity& e : entities_) {
				if (e.is_alive()) {
					++alive_count;
				}
			}
			return alive_count;
		}

		int dead_count() const {
			int dead_count = 0;

			for (const Entity& e : entities_) {
				if (!e.is_alive()) {
					++dead_count;
				}
			}
			return dead_count;
		}

	private:
		std::vector<Entity> entities_;
	};


int Entity::next_id_ = 0;


int main() {

	//   - Create a World
	World world;

	//   - Spawn a player and 3 enemies with different positions/velocities/hp
	world.spawn("Player", 100);
	Entity* player = world.find("Player");
	player->set_position(5.0, 5.0);
	player->set_velocity(1.0, 1.0);

	world.spawn("Enemy 1", 50);
	Entity* enemy1 = world.find("Enemy 1");
	enemy1->set_position(1.0, 2.0);
	enemy1->set_velocity(0.5, 0.5);

	world.spawn("Enemy 2", 50);
	Entity* enemy2 = world.find("Enemy 2");
	enemy2->set_position(2.0, 1.0);
	enemy2->set_velocity(0.5, 0.5);

	world.spawn("Enemy 3", 50);
	Entity* enemy3 = world.find("Enemy 3");
	enemy3->set_position(3.0, 7.0);
	enemy3->set_velocity(0.5, 0.5);

	//   - Print the world
	world.print();
	//   - Run update() 3 times, print again
	world.update();
	world.update();
	world.update();
	//   - Deal damage to enemies, kill one
	enemy3->take_damage(25);
	enemy3->take_damage(25);
	player->take_damage(25);
	//   - Print alive/dead counts;
	std::cout << "Alive count: " << world.alive_count() << std::endl;
	std::cout << "Dead count: " << world.dead_count() << std::endl;
	//   - Heal the player
	player->heal(25);
	//   - Print final state
	world.print();



}