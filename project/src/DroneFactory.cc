#include "DroneFactory.h"

namespace csci3081 {

	IEntity* DroneFactory::CreateEntity(const picojson::object& object) {
		if  (JsonHelper::GetString(object, "type") == "drone") {
			std::cout << "Created Drone" << std::endl;
			return new Drone(object);
		}
		return nullptr;
	} //end function 
} //end namespace 