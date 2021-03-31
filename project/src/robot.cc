#include "robot.h"

namespace csci3081 {


void Robot::Pick_order() {
	currentIndex = 0;
	has_picked_up = true;
	currentRout = &pack_to_customer;
}//end of function

void Robot::Drop_order() {
	has_picked_up = false;
		package_currently_delivering->SetPosition(Vector3D(0, -1000, 0));
	package_currently_delivering = nullptr;
	currentIndex = 0;
	distance_traveled = 0;
}//close function 

Vector2D  Robot::GetTargetPosition() {
	return Vector2D (currentRout->at(currentIndex)[0], currentRout->at(currentIndex)[1]);
}//close function

bool Robot::IncrTarget() {
	if (currentIndex+1 == currentRout->size()) {
		return true;
	} //
	currentIndex +=1;
	return false;
}

Package* Robot::GetPackage() {
	return package_currently_delivering;
}

void Robot::SetPackage(Package* pack) {
	package_currently_delivering = pack;
}

void Robot::SetRobotToPack(std::vector<std::vector<float>> v) {
	Robot_to_pack = v;
}

void Robot::SetPackToCustomer(std::vector<std::vector<float>> v) {
	pack_to_customer   = v;
}

bool Robot::Within_range(Vector2D v) {
	if (Vector2D (GetPosition()[0], GetPosition()[1]) .DistanceBetween(v) < GetRadius() ) {
		return true;
	}
	else {
		return false;
	}
}

float Robot::GetSpeed() {
	return speed;
}//

bool Robot::has_picked_up_getter() {
	return has_picked_up;
}

void Robot::SetCurrRout(std::string rout) {
	if (rout == "pack") {
	currentRout = &Robot_to_pack;
}
else if (rout == "customer") {
	currentRout = &pack_to_customer;
}
}

void Robot::Update_Package() {
	Vector3D initial_position = Vector3D (package_currently_delivering->GetPosition());
	// std::cout << "initial package position" << initial_position.ToString() << std::endl;
	if (has_picked_up == true) {
//		std::cout << "package flying around!!!!" << std::endl;
		package_currently_delivering->SetPosition(Vector3D (this->GetPosition() ));
		Vector3D temp = Vector3D (package_currently_delivering->GetPosition());
		std::cout << "package position is: " << temp.ToString() << std::endl;
	}
}

void Robot::Scheduled_Robot(IEntity* package, IEntity* dest, const IGraph* graph_) {
	if (GetPackage() == nullptr) {
		SetRobotToPack( graph_->GetPath(GetPosition(), package->GetPosition() ) );
		SetPackage(dynamic_cast<Package*>(package));
		SetCurrRout("pack");
		SetPackToCustomer ( graph_->GetPath(package->GetPosition(), dest->GetPosition() ));
		Package* pack = dynamic_cast<Package*>(package);
		pack->SetCustomer(dynamic_cast<Customer*>(dest));
	} // close  if
}

void Robot::update_Robot_movement(float dt) {
	if (GetPackage() != nullptr) {
		if (Within_range(GetTargetPosition())) {
			std::cout << "Within Range" << std::endl;
			if (IncrTarget()) {
				if (has_picked_up_getter()) {
					Drop_order();				
				}
				else {
					std::cout << "Picked orders Robot" << std::endl;
					Pick_order();
				}
			} //close if statement 4
		} //close within range
		else { //we know we have a package 
			Vector2D v = GetTargetPosition()-Vector2D(GetPosition()[0], GetPosition()[1]);
			v.Normalize();
			v = v*dt*GetSpeed();
			if (v.Magnitude() > ( Vector2D (GetPosition()[0], GetPosition()[1])- GetTargetPosition() ).Magnitude() ) {
				SetPosition(Vector3D(GetTargetPosition()[0], GetTargetPosition()[1], 0));
			}//close if for overshooting the target 
			else {						
				Vector2D positionToMove = Vector2D ( GetPosition()[0], GetPosition()[1])+v;
				std::cout << positionToMove.ToString()<< std::endl;
				SetPosition(Vector3D(positionToMove[0], positionToMove[1], 0));
			} //close else for overshooting target
			Update_Package();
		} //close else of the within range if
		
	} //close get package check
	
}//close function 

}//close namespace 