#include "RobotFactory.h"

namespace csci3081 {

	IEntity* RobotFactory::CreateEntity(const picojson::object& object) {
		if  (JsonHelper::GetString(object, "type") == "robot") {
			std::cout << "Created Robot" << std::endl;
			return new Robot(object);
		}
		return nullptr;
	} //end function 
} //end namespace 