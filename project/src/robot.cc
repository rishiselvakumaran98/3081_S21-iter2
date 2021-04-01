#include "robot.h"

namespace csci3081 {


void Robot::Pick_order() {
	package_currently_delivering->OnPickUp();	currentIndex = 0;
	has_picked_up = true;
	currentRout = &pack_to_customer;
}//end of function

void Robot::Drop_order() {
	package_currently_delivering->OnDropOff();
	has_picked_up = false;
		package_currently_delivering->SetPosition(Vector3D(0, -1000, 0));
	package_currently_delivering = nullptr;
	currentIndex = 0;
	distance_traveled = 0;
}//close function 

Vector3D  Robot::GetTargetPosition() {
	return Vector3D ( currentRout->at(currentIndex));
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

bool Robot::Within_range(Vector3D v) {
	if (Vector3D (GetPosition()) .DistanceBetween(v) < GetRadius() ) {
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
		OnMove();
	} // close  if
}

void Robot::update_Robot_movement(float dt) {
	if (GetPackage() != nullptr) {
		if (Within_range(GetTargetPosition())) {
			std::cout << "Within Range" << std::endl;
			if (IncrTarget()) {
				if (has_picked_up_getter()) {
					Drop_order();
					OnIdle();
				}
				else {
					std::cout << "Picked orders Robot" << std::endl;
					OnIdle();
					Pick_order();
					OnMove();
				}
			} //close if statement 4
		} //close within range
		else { //we know we have a package 
			Vector3D v = GetTargetPosition()-GetPosition();
			v.Normalize();
			v = v*dt*GetSpeed();
			if (v.Magnitude() > ( Vector3D (GetPosition())- GetTargetPosition() ).Magnitude() ) {
				SetPosition(GetTargetPosition());
			}//close if for overshooting the target 
			else {						
				Vector3D positionToMove = Vector3D ( GetPosition())+v;
				std::cout << "Robot position" << positionToMove.ToString() << std::endl;
				SetPosition(positionToMove);
			} //close else for overshooting target
			Update_Package();
		} //close else of the within range if
		
	} //close get package check
	
	
}//close function 

void Robot::OnIdle() {
	picojson::object obj = JsonHelper::CreateJsonObject();
	JsonHelper::AddStringToJsonObject(obj, "type", "notify");
	JsonHelper::AddStringToJsonObject(obj, "value", "idle");
	const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
	entity_sub->OnEvent(val, *this);
}

void Robot::OnMove() {
	picojson::object obj = JsonHelper::CreateJsonObject();
	JsonHelper::AddStringToJsonObject(obj, "type", "notify");
	JsonHelper::AddStringToJsonObject(obj, "value", "moving");
	JsonHelper::AddStdVectorVectorFloatToJsonObject(obj, "path", *currentRout);
	const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
	entity_sub->OnEvent(val, *this);
}

}//close namespace 