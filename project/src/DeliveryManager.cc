#include "DeliveryManager.h"

namespace csci3081 {


void DeliveryManager::schedule_mover(Drone* nextDrone, IEntity* package, IEntity* dest, const IGraph* graph_) {
	if (nextDrone->GetPackage() == nullptr) {
		nextDrone->SetDroneToPack( graph_->GetPath(GetPosition(), package->GetPosition() ) );
		nextDrone->SetPackage(dynamic_cast<Package*>(package));
		nextDrone->("pack");
		nextDrone->SetPackToCustomer ( graph_->GetPath(package->GetPosition(), dest->GetPosition() ));
		Package* pack = dynamic_cast<Package*>(package);
		pack->SetCustomer(dynamic_cast<Customer*>(dest));
	} // close  if
}

void DeliveryManager::update_movement(Drone* nextDrone, float dt) {
	if (nextDrone->GetPackage() != nullptr) {
		if (nextDrone->Within_range(nextDrone->GetTargetPosition())) {
			if (nextDrone->IncrTarget()) {
				if (nextDrone->has_picked_up_getter()) {
					nextDrone->Drop_order();				
				}
				else {
					nextDrone->Pick_order();
				}
			} //close if statement 4
		} //close within range
		else { //we know we have a package 
			Vector3D v = nextDrone->GetTargetPosition()-nextDrone->GetPosition();
			v.Normalize();
			v = v*dt*nextDrone->GetSpeed();
			if (v.Magnitude() > ( Vector3D (nextDrone->GetPosition() )- nextDrone->GetTargetPosition() ).Magnitude() ) {
				nextDrone->SetPosition(GetTargetPosition());
			}//close if for overshooting the target 
			else {						
				Vector3D positionToMove = Vector3D ( nextDrone->GetPosition())+v;
				nextDrone->SetPosition(positionToMove);
			} //close else for overshooting target
			nextDrone->Update_Package();
		} //close else of the within range if
		
	} //close get package check
}//close function 

}//close namespace 