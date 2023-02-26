#include "AssetLoader.hpp"

bool AssetLoader::loadLevel(int &t_level) {
  std::string path =
    "../Game/CreateEntities/levels/level" + std::to_string(t_level) + ".json";
  Json::Value level_data;

  try {
    std::ifstream level_file(path, std::ifstream::binary);
    if (level_file.fail()) {
      std::cout << "Could not load level " << std::to_string(t_level)
                << std::endl;
      return false;
    }
    level_file >> level_data;
    if (level_file.is_open()) level_file.close();
  } catch (std::exception &e) {
    std::cout << "Could not load level: " << e.what() << std::endl;
    return false;
  }

  if (level_data.empty()) {
    std::cout << "Could not load level data" << std::endl;
    return false;
  } else if (level_data["backgrounds"].empty()) {
    std::cout << "Could not load backgrounds" << std::endl;
    return false;
  } else if (level_data["enemies"].empty()) {
    std::cout << "Could not load enemies" << std::endl;
    return false;
  } else if (level_data["music"].empty()) {
    std::cout << "Could not load music" << std::endl;
    return false;
  }
  m_level_data = level_data;
  return true;
}

Json::Value AssetLoader::getBackgroundData() {
  return m_level_data["backgrounds"];
}

Json::Value AssetLoader::getEnemyData() { return m_level_data["enemies"]; }

std::string AssetLoader::getMusicPath() {
  return m_level_data["music"].asString();
}
