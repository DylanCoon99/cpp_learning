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
#include <string>
#include <iostream>
#include <vector>




struct Position {
	int entity_id;
	double x, y;

	Position(int id, double posx, double posy) : entity_id(id), x(posx), y(posy) {}

	void print() const {
		std::cout << "X: " << x << "  Y: " << y << std::endl;
	}

};


struct Velocity {
	int entity_id;
	double dx, dy;

	Velocity(int id, int dx, int dy) : entity_id(id), dx(dx), dy(dy) {}

	void print() const {
		std::cout << "dx: " << dx << "  dy: " << dy << std::endl;
	}

};


struct Health {
	int entity_id;
	int current;
	int max;

	Health(int id, int hp) : entity_id(id), current(hp), max(hp) {}

	bool is_alive() const {
		return current > 0;
	}

	void print() const {
		std::cout << "Health: " << current << "  HP: " << max << std::endl;
	}

};


enum class EntityType { Player, Enemy, Item };


std::string entity_type_to_string(EntityType y) {
	switch (y) {
	case EntityType::Player:
		return "Player";
	case EntityType::Enemy:
		return "Enemy";
	case EntityType::Item:
		return "Item";
	}
}


struct Entity {
	int id;
	std::string name;
	EntityType type;

	void print() const {
		std::cout << "Name: " << name << "  Type: " << entity_type_to_string(type) << std::endl;
	}

};


struct World {
	std::vector<Entity> entities;
	std::vector<Position> positions;
	std::vector<Velocity> velocities;
	std::vector<Health> healths;
	int next_id = 0;

	int create_entity(const std::string& name, EntityType type) {

		entities.push_back(Entity{next_id, name, type});
		int ret = next_id;
		next_id += 1;
		return ret;
	}


	void add_position(int id, double x, double y) {
		positions.push_back(Position(id, x, y));
	}


    void add_velocity(int id, double dx, double dy) {
    	velocities.push_back(Velocity(id, dx, dy));
    }


    void add_health(int id, int hp) {
    	healths.push_back(Health(id, hp));
    }


    const Position* get_position(int id) const {
    	for (const auto& pos : positions) {
    		if (pos.entity_id == id) {
    			return &pos;
    		}
    	}
    	return nullptr;
    }

    Position* get_position(int id) { 
    	for (auto& pos : positions) {
    		if (pos.entity_id == id) {
    			return &pos;
    		}
    	}
    	return nullptr;
    }

    const Velocity* get_velocity(int id) const {
		for (const auto& vel : velocities) {
    		if (vel.entity_id == id) {
    			return &vel;
    		}
    	}
    	return nullptr;
    }

    Velocity* get_velocity(int id) { 
    	for (auto& vel : velocities) {
    		if (vel.entity_id == id) {
    			return &vel;
    		}
    	}
    	return nullptr;
    }

    const Health* get_health(int id) const {
    	for (const auto& health : healths) {
    		if (health.entity_id == id) {
    			return &health;
    		}
    	}
    	return nullptr;
    }

    Health* get_health(int id) {
    	for (auto& health : healths) {
    		if (health.entity_id == id) {
    			return &health;
    		}
    	}
    	return nullptr;
    }

};



// System functions
void movement_system(World& world) {

//     — For every entity that has both Position and Velocity,
//       update position: x += dx, y += dy

	for (const Entity& e : world.entities) {
		// for each id -> determine if it has a pos and vel
		Position* pos = world.get_position(e.id);
		Velocity* vel = world.get_velocity(e.id);

		if (pos && vel) {
			pos->x += vel->dx;
			pos->y += vel->dy;
		}
	}


}


void damage_system(World& world, int entity_id, int damage) {

//     — Reduce the entity's health by damage (min 0)
	Health* health = world.get_health(entity_id);

	if (health) {
		health->current -= damage;
	}
}


void print_world(const World& world) {


	for (const Entity& e : world.entities) {
		// for each id -> determine if it has a pos and vel
		const Position* pos = world.get_position(e.id);
		const Velocity* vel = world.get_velocity(e.id);
		const Health* health = world.get_health(e.id);

		// print the entity
		e.print();

		// print the entities components
		if (pos) {
			pos->print();
		}

		if (vel) {
			vel->print();
		}

		if (health) {
			health->print();
		}

		std::cout << std::endl;
	}



}


int main() {

	World world;

	// Create entities
	int player = world.create_entity("Hero", EntityType::Player);
	int enemy1 = world.create_entity("Goblin", EntityType::Enemy);
	int enemy2 = world.create_entity("Skeleton", EntityType::Enemy);
	int item   = world.create_entity("Health Potion", EntityType::Item);

	// Add components — Player: position, velocity, health
	world.add_position(player, 0.0, 0.0);
	world.add_velocity(player, 1.5, 2.0);
	world.add_health(player, 100);

	// Enemy 1: position, health
	world.add_position(enemy1, 10.0, 5.0);
	world.add_health(enemy1, 50);

	// Enemy 2: position, health
	world.add_position(enemy2, -3.0, 8.0);
	world.add_health(enemy2, 30);

	// Item: position only
	world.add_position(item, 7.0, 7.0);

	// Print initial state
	std::cout << "=== Initial World State ===" << std::endl;
	print_world(world);

	// Run movement system 3 times
	for (int i = 0; i < 3; ++i) {
		movement_system(world);
	}

	std::cout << "=== After 3 Movement Ticks ===" << std::endl;
	print_world(world);

	// Damage an enemy
	damage_system(world, enemy1, 20);
	damage_system(world, enemy2, 50);  // should kill skeleton (30 hp - 50 = 0)

	std::cout << "=== After Combat ===" << std::endl;
	print_world(world);

}

