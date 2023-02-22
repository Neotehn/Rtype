#ifndef CLIENT_SRC_SYSTEMS_RANDOMENEMYGENERATORSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_RANDOMENEMYGENERATORSYSTEM_HPP_

#include <memory>
#include <string>

#include "../ECS/ISystem.hpp"
#include "../ECS/DataTypesECS.hpp"
#include "../../Server/Protocol/UdpServer.hpp"
#include "../Encapsulation/SFML/RectangleShape.hpp"

class RandomEnemyGeneratorSystem : public ISystem {
 public:
  RandomEnemyGeneratorSystem(std::shared_ptr<EntityManager> t_em,
                             UdpServer *t_serverCom);
  ~RandomEnemyGeneratorSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  std::shared_ptr<EntityManager> m_em;
  UdpServer *m_serverCom;

  void generateEnemy(int random);
  void generatePowerUp(int random);
  void createCoin();
  void createItem(std::string t_path, rtype::ItemType t_type, int t_value);
};

#endif  // CLIENT_SRC_SYSTEMS_RANDOMENEMYGENERATORSYSTEM_HPP_
