#ifndef R_TYPE_CLIENT_ASSETLOADER_HPP
#define R_TYPE_CLIENT_ASSETLOADER_HPP

#include <iostream>
#include <fstream>
#include <json/json.h>

class AssetLoader {
 public:
  AssetLoader() = default;
  ~AssetLoader() = default;

  bool loadLevel(int &t_level);

  Json::Value getBackgroundData();
  Json::Value getEnemyData();
  std::string getMusicPath();

 private:
  Json::Value m_level_data;
};

#endif  //R_TYPE_CLIENT_ASSETLOADER_HPP
