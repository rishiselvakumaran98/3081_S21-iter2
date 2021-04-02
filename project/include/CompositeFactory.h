/**
 * @file CompositeFactory.h
 */
#ifndef COMPOSITE_FACTORY_H_
#define COMPOSITE_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "json_helper.h"
#include <vector>


namespace csci3081 {
	/**
	 * @brief This class is the composite factory that controls the generation of entities. Depending on the type of entity to be created either calling DroneFactory, CustomerFactory or PackageFactory.
	 */
	class CompositeFactory : public IEntityFactory  {
	private:
		std::vector<IEntityFactory*> componentFactories;

	public:
		/**
		 * @brief Constructor that initialize the componentFactories vector. This is the vector where the other factories, DroneFactory, CustomerFactory and PackageFactory will be stored during the execution of the program.
		 */
		CompositeFactory () {
			//componentFactories = std::vector<IEntityFactory*>(0);
		}
		
		/**
		 * @brief function that implements the pure virtual function fron IEntityFactory. This function has the goal of create entities based on their picojson type.
		 */
		IEntity* CreateEntity(const picojson::object& object);

		/**
		 * @brief this function adds the DroneFactory, PackageFactory and CustomerFactory to the componentFactories vector.
		 */
		void AddFactory(IEntityFactory* factory_entity);

		/**
		 * @brief distructor for the composite factory. Iterates through componentFactories vectors distroying its elements.
		 */
				~CompositeFactory();

	}; //close class
}//close namespace 

#endif