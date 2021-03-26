/**
 * @file Package.h
 */
#ifndef PACKAGE_FACTORY_H_
#define PACKAGE_FACTORY_H_


/**
 * include
 */#include <EntityProject/facade/delivery_system.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "json_helper.h"
#include <vector>
#include "Package.h"

namespace csci3081 {


   /*******************************************************************************
    * Class Definitions
    ******************************************************************************/
   /**
    * @brief Package factory. This class is responsible for the creation of packages entity.
   */
class PackageFactory : public IEntityFactory {
public:

/**
 * @brief override function from IEntityFactory to create packages.
 * @param object the picojson to be analysed and possibly made into a package.
 */
	IEntity* CreateEntity(const picojson::object& object);
}; //close class
}//close of the namespace 

#endif 