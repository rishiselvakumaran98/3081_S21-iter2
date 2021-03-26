#include "CompositeFactory.h"
namespace csci3081 {
void CompositeFactory::AddFactory(IEntityFactory* factory_entity) {
	componentFactories.push_back(factory_entity);
}

IEntity* CompositeFactory::CreateEntity(const picojson::object& object) {
	for (int i = 0; i < componentFactories.size(); i++) {
		IEntity* factory_return = componentFactories.at(i)->CreateEntity(object);
		if (factory_return != nullptr) {
//			CompositeFactory::Id+=1;
			return factory_return;
		} //end if statement 
	}// end for loop
	std::cout << "Returned null entity from factories" << std::endl;
	return nullptr;
} //end function

//int CompositeFactory::Id = 0;
//add a distructor 
CompositeFactory::~CompositeFactory() {
	for (int i = 0; i < componentFactories.size(); i++) {
		delete componentFactories[i];
	} //close loop
	std::cout << "calling distructor for composite factory" << std::endl;
//	componentFactories = nullptr;
	}//close function


} 