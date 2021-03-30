/**
 *@file multi_package.h
 */
#ifndef MULTI_PACKAGE_H_
#define MULTI_PACKAGE_H_

/**
 * include
 */
#include "entity_base.h"
#include "Vector3D.h"
#include "Package.h"
#include "drone.h"
#include "ISubject.h"
namespace csci3081 {
	/**
	 * @brief class responsible for the generation of packages.
	 */
class Multi_package{

public:
    void Schedule_Multiple_Delivery_Robot(IEntity* deliverer, vector<Package*> packages, const IGraph* graph);
    void Schedule_Multiple_Delivery_Drone(IEntity* deliverer, vector<Package*> packages, const IGraph* graph);
};

}  // namespace

#endif