
/**
 * @file CustomerFactory.h
 */
#ifndef CUSTOMER_FACTORY_H_
#define CUSTOMER_FACTORY_H_

/**
 * includes
 */
#include <EntityProject/facade/delivery_system.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "json_helper.h"
#include <vector>
#include "Customer.h"


namespace csci3081 {
	/**
	 * @brief The factory to create customers entities.
	 */
	class CustomerFactory : public IEntityFactory  {
		public:
			/**
			* @brief Function to generate customers entities.
			* @param object picojson object from the simulation to make the entity 
			*/
			IEntity* CreateEntity(const picojson::object& object);
	}; //close class
}//close of the namespace

#endif 