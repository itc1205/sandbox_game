#include "core/engine.hpp"
#include <core/input.hpp>

namespace Engine {
namespace Input {

std::unordered_map<Key, std::list<std::function<void()>>, KeyHasher>
    key_mapping;
void create_mapping(Key key, std::function<void()> callback) {
  if (auto keymap = key_mapping.find(key); keymap != key_mapping.end()) {
    Logger::info("Found key");
    keymap->second.push_back(callback);
  } else {
    Logger::info("Creating new mapping for key");
    std::list<std::function<void()>> new_key_list;
    new_key_list.push_back(callback);
    key_mapping.insert_or_assign(key, new_key_list);
  }
}

void proceed_input() {
  for (const auto &key : Input::key_mapping) {
    auto keymap = &key.first;
    auto callback_list = &key.second;
    if (glfwGetKey(window, keymap->key) == keymap->action) {
      for (const auto callback : *callback_list) {
        callback();
      }
    }
  }
}

} // namespace Input
namespace Callbacks {
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {

  auto key_struct = Input::Key{key, action};

  if (auto keymap = Input::key_mapping.find(key_struct);
      keymap != Input::key_mapping.end()) {

    for (auto callback : keymap->second) {
      callback();
    }
  }
}
} // namespace Callbacks
} // namespace Engine