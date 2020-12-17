#include "delivery_simulation.h"
#include "entity_base.h"

namespace csci3081 {

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
    return NULL;
}

void DeliverySimulation::AddEntity(IEntity* entity) {}

void DeliverySimulation::SetGraph(const IGraph* graph) {}

void DeliverySimulation::ScheduleDelivery(IPackage* package, ICustomer* dest) {}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

void DeliverySimulation::Update(float dt) {}

void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
    std::cout << picojson::value(script).serialize() << std::endl;
    IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(system);
	if (deliverySystem) {
		
	    // To store the unadded entities_
	    std::vector<IEntity*> created_entities;
	
		for (unsigned int i=0; i < script.size(); i++) {
			const picojson::object& object = script[i].get<picojson::object>();
			const std::string cmd = object.find("command")->second.get<std::string>();
			const picojson::object& params = object.find("params")->second.get<picojson::object>();
			// May want to replace the next few if-statements with an enum
			if (cmd == "createEntity") {
				IEntity* entity = NULL;
				entity = deliverySystem->CreateEntity(params);
				if (entity) {
					created_entities.push_back(entity);
				} else {
					std::cout << "Null entity" << std::endl;
				}
			}
			else if (cmd == "addEntity") {
				int ent_index = static_cast<int>(params.find("index")->second.get<double>());
				if (ent_index >= 0 && ent_index < created_entities.size()) {
					deliverySystem->AddEntity(created_entities[ent_index]);
				}
			}
			else if (cmd == "scheduleDelivery" ) {
				int pkg_index = static_cast<int>(params.find("pkg_index")->second.get<double>());
				int dest_index = static_cast<int>(params.find("dest_index")->second.get<double>());
				if (pkg_index >= 0 && pkg_index < system->GetEntities().size()) {
					IPackage* pkg = dynamic_cast<IPackage*>(deliverySystem->GetEntities()[pkg_index]);
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						ICustomer* cst = dynamic_cast<ICustomer*>(system->GetEntities()[dest_index]);
						if (pkg && cst) {
							// TODO: move into MyDeliverySystem::scheduleDelivery
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
			else {
				std::cout << "Unknown command: " << cmd << std::endl;
			}
		}

	}	
}

}
