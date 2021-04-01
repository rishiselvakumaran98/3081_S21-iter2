/**
  * @file DroneFactory.h
 */
#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

/**
 * include
 */
#include <EntityProject/facade/delivery_system.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "json_helper.h"
#include <vector>
#include "drone.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Drone factory. This class is responsible for the creation of Drones entity.
*/
class DroneFactory : public IEntityFactory {
public:
	/**
	 * @brief override function from IEntityFactory to create Drones.
	 * @param  details_ the picojson to be analysed and possibly made into a drone.
	 */
	IEntity* CreateEntity(const picojson::object& object);
}; //close class
}//close of the namespace 

#endif 