#pragma once
#include <core/engine.hpp>

#include <functional>
#include <list>
#include <unordered_map>

namespace Engine {
namespace Input {
struct Key {
  int key;
  int action;
  bool operator==(const Key &other) const {
    return (key == other.key) && (action == other.action);
  }
};

struct KeyHasher {
  std::size_t operator()(const Key &k) const {
    using std::hash;
    using std::size_t;
    return (hash<int>()(k.action) ^ (hash<int>()(k.key) << 1));
  }
};
void proceed_input();

extern std::unordered_map<Key, std::list<std::function<void()>>, KeyHasher>
    key_mapping;
void create_mapping(Key key, std::function<void()> callback);
} // namespace Input
namespace Callbacks {
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);
} // namespace Callbacks
} // namespace Engine