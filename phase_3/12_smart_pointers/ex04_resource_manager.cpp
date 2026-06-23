// Exercise 4: Resource Manager with shared_ptr and weak_ptr
//
// Task: Build a texture/resource cache that demonstrates when shared_ptr
//       and weak_ptr are useful in practice.
//
// Scenario: A game loads textures. Multiple game objects can share the
// same texture. When no objects use a texture, it should be freed.
// But we want a cache so we don't reload it if something asks for it again.
//
// Define:
//
//   class Texture {
//   public:
//       explicit Texture(const std::string& filename)
//           : filename_(filename) {
//           std::cout << "Loading texture: " << filename_ << "\n";
//       }
//       ~Texture() {
//           std::cout << "Unloading texture: " << filename_ << "\n";
//       }
//       void bind() const {
//           std::cout << "Binding texture: " << filename_ << "\n";
//       }
//       const std::string& filename() const { return filename_; }
//   private:
//       std::string filename_;
//   };
//
//   class TextureCache {
//   public:
//       std::shared_ptr<Texture> get(const std::string& filename);
//         — If the texture is in the cache AND still alive, return it
//         — If not, load it, store a weak_ptr in the cache, return shared_ptr
//         — The cache uses weak_ptr so it doesn't keep textures alive
//
//   private:
//       std::map<std::string, std::weak_ptr<Texture>> cache_;
//       // (you'll need #include <map> — we'll cover it properly in step 14,
//       //  but it's just a key-value dictionary like Go's map or Python's dict)
//       // Usage: cache_[key] = value; auto it = cache_.find(key);
//   };
//
// Implementation of TextureCache::get:
//   - Check if filename exists in cache_
//   - If yes, try cache_[filename].lock()
//     - If lock succeeds (texture still alive), return it
//   - If no or lock failed, create new shared_ptr<Texture>
//   - Store weak_ptr in cache
//   - Return the shared_ptr
//
// In main():
//   TextureCache cache;
//
//   {
//       auto t1 = cache.get("wall.png");     // loads
//       auto t2 = cache.get("wall.png");     // cache hit — same texture
//       auto t3 = cache.get("floor.png");    // loads new texture
//       t1->bind();
//       std::cout << "t1 use_count: " << t1.use_count() << "\n";  // 2
//   }   // t1, t2, t3 destroyed → textures unloaded
//
//   auto t4 = cache.get("wall.png");  // cache miss — reloads (was freed)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_resource_manager.cpp

// YOUR CODE HERE
