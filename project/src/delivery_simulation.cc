#include "delivery_simulation.h"
#include "entity_base.h"
#include "json_helper.h"
#include "drone.h"

namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
	comp_fact = CompositeFactory();

	AddFactory(new DroneFactory());
	AddFactory(new PackageFactory());
	AddFactory(new CustomerFactory());
}

DeliverySimulation::~DeliverySimulation() {}

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
		IEntity* temp =  comp_fact.CreateEntity(val);
		if (temp != nullptr) {
			EntityBase* tempBase = dynamic_cast<EntityBase*>(temp);
			tempBase->SetId(NewId());
			tempBase->SetDeliverySimulation(*this);
			return tempBase;
		}//close if
		return nullptr;
}

void DeliverySimulation::AddFactory(IEntityFactory* factory) {
	comp_fact.AddFactory(factory);
}

void DeliverySimulation::AddEntity(IEntity* entity) { 
	if (dynamic_cast<Drone*>(entity)) {
		std::cout << "Added Drone" << std::endl;
	} else if (dynamic_cast<Package*>(entity)) {
		std::cout << "Added Package" << std::endl;
	} else if (dynamic_cast<Customer*>(entity)) {
		std::cout << "Added Customer" << std::endl;
	}
	entities_.push_back(entity);
}

void DeliverySimulation::SetGraph(const IGraph* graph) {
	graph_ = graph;
}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
	for (int i = 0; i < entities_.size(); i++) {
		const picojson::object& temp = entities_[i]->GetDetails();
		if (JsonHelper::GetString(temp, "type") == "drone") {
			Drone* nextDrone   = dynamic_cast<Drone*>(entities_[i]);
//			nextDrone->Scheduled_drone(package, dest, graph_);
			manager.schedule_mover(nextDrone, package, dest, graph_);
		}
	}//close for loop
}//close function

void DeliverySimulation::AddObserver(IEntityObserver* observer) {
	
	observers_.push_back(observer_to_be_added);
}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {
	
	for (int i = 0; i < observers_.size(); i++) {
		if (observers_[i] = observer_to_be_removed) {
			observers_.erase(observers_.begin()+i);
			break;
		}//close if
	}//close for loop
	
}

void DeliverySimulation::OnEvent(const picojson::value& object, const IEntity& entity_) {
	for (int i = 0; i < observers_.size(); i++) {
		(observers_[i])->OnEvent(object, entity_);
}	// close for loop 
} // close method 


const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

void DeliverySimulation::Update(float dt) {
	for (int i = 0; i < entities_.size(); i++) {
		const picojson::object& temp = entities_[i]->GetDetails();
		if (JsonHelper::GetString(temp, "type") == "drone") {
			Drone* nextDrone   = dynamic_cast<Drone*>(entities_[i]);
//			nextDrone->update_drone_movement(dt);
			manager.update_movement(nextDrone, dt);
		} //close type check for entity
	} //close for loop
} //end function

// DO NOT MODIFY THE FOLLOWING UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
  JsonHelper::PrintArray(script);
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
					IEntity* pkg = deliverySystem->GetEntities()[pkg_index];
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						IEntity* cst = system->GetEntities()[dest_index];
						if (pkg && cst) {
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
		}
	}
}

}
