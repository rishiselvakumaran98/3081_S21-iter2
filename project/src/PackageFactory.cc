#include "PackageFactory.h"

namespace csci3081 {

	IEntity* PackageFactory::CreateEntity(const picojson::object& object) {
		if  (JsonHelper::GetString(object, "type") == "package") {
			std::cout << "Created Package" << std::endl;
			return new Package(object);
		}
		return nullptr;
	} //end function 
} //end namespace 