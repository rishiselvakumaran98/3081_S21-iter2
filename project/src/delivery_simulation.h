#ifndef DELIVERY_SIMULATION_H_
#define DELIVERY_SIMULATION_H_

#include <EntityProject/facade/delivery_system.h>
#include <vector>
#include <string>

namespace csci3081 {

class DeliverySimulation : public IDeliverySystem {
 public:

  void RunScript(const picojson::array& script, IEntitySystem* system) const;
  IEntity* CreateEntity(const picojson::object& val) const;
  void AddFactory(IEntityFactory* factory);
  void AddEntity(IEntity* entity);
  void SetGraph(const IGraph* graph);
  void ScheduleDelivery(IEntity* package, IEntity* dest);
  void AddObserver(IEntityObserver* observer);
  void RemoveObserver(IEntityObserver* observer);
  const std::vector<IEntity*>& GetEntities() const;
  void Update(float dt);

 private:
  std::vector<IEntity*> entities_;
};

}  // namespace csci3081


#endif  // DELIVERY_SIMULATION_H_
