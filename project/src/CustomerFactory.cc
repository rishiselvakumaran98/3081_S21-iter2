#include "CustomerFactory.h"

namespace csci3081 {

	IEntity* CustomerFactory::CreateEntity(const picojson::object& object) {
		if  (JsonHelper::GetString(object, "type") == "customer") {
			std::cout << "Created Customer" << std::endl;
			return new Customer(object);
		}
		return nullptr;
	} //end function 
} //end namespace 