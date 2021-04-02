/**
  * @file RobotFactory.h
 */
#ifndef Robot_FACTORY_H_
#define Robot_FACTORY_H_

/**
 * include
 */
#include <EntityProject/facade/delivery_system.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "json_helper.h"
#include <vector>
#include "robot.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Robot factory. This class is responsible for the creation of Robots entity.
*/
class RobotFactory : public IEntityFactory {
public:
	/**
	 * @brief override function from IEntityFactory to create Robots.
	 * @param  object the picojson to be analysed and possibly made into a Robot.
	 */
	IEntity* CreateEntity(const picojson::object& object);
}; //close class
}//close of the namespace 

#endif 