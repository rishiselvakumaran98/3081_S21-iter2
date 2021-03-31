#ifndef DELIVERY_MANAGER_H_
#define DELIVERY_MANAGER_H_

#include <EntityProject/facade/delivery_system.h>
#include "drone.h"
#include "Package.h"

namespace csci3081 {

class DeliveryManager {
public:
	void schedule_mover(Drone* nextDrone, IEntity* package, IEntity* dest, const IGraph* graph_);
	void update_movement(Drone* nextDrone, float dt);
}; //close class 
} //close namespace 

#endif
