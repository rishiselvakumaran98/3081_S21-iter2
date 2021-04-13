#include "drone.h"

namespace csci3081 {


void Drone::Pick_order() {
	package_currently_delivering->OnPickUp();
	currentIndex = 0;
	has_picked_up = true;
	currentRout = &pack_to_customer;
}//end of function

void Drone::Drop_order() {
	package_currently_delivering->OnDropOff();
	has_picked_up = false;
		package_currently_delivering->SetPosition(Vector3D(0, -1000, 0));
	package_currently_delivering = nullptr;
	currentIndex = 0;
	distance_traveled = 0;
}//close function 

Vector3D  Drone::GetTargetPosition() {
	return Vector3D ( currentRout->at(currentIndex) );
}//close function

bool Drone::IncrTarget() {
	if (currentIndex+1 == currentRout->size()) {
		return true;
	} //
	currentIndex +=1;
	return false;
}

Package* Drone::GetPackage() {
	return package_currently_delivering;
}

void Drone::SetPackage(Package* pack) {
	package_currently_delivering = pack;
}

void Drone::SetDroneToPack(std::vector<std::vector<float>> v) {
	drone_to_pack = v;
}

void Drone::SetPackToCustomer(std::vector<std::vector<float>> v) {
	pack_to_customer   = v;
}

bool Drone::Within_range(Vector3D v) {
	if (Vector3D (GetPosition()) .DistanceBetween(v) < GetRadius() ) {
		return true;
	}
	else {
		return false;
	}
}

float Drone::GetSpeed() {
	return speed;
}//

bool Drone::has_picked_up_getter() {
	return has_picked_up;
}

void Drone::SetCurrRout(std::string rout) {
	if (rout == "pack") {
	currentRout = &drone_to_pack;
}
else if (rout == "customer") {
	currentRout = &pack_to_customer;
}
}

void Drone::Update_Package() {
	Vector3D initial_position = Vector3D (package_currently_delivering->GetPosition());
	// std::cout << "initial package position" << initial_position.ToString() << std::endl;
	if (has_picked_up == true) {
		// std::cout << "package flying around!!!!" << std::endl;
		package_currently_delivering->SetPosition(Vector3D (this->GetPosition() ));
		// std::cout << "drone: " << GetId() << "'s package is: " << JsonHelper::GetString(package_currently_delivering->GetDetails(), "name") << std::endl;
		Vector3D temp = Vector3D (package_currently_delivering->GetPosition());
		// std::cout << "drone: " << GetId() << " package position is: " << temp.ToString() << std::endl;
	}
}

std::vector<std::vector<float>> get_beeline(std::vector<float> source, std::vector<float> destination) {
	std::vector<std::vector<float>> path;
	source[1] += 200;
	destination[1] += 200;
	Vector3D s(source);
	Vector3D d(destination);
	Vector3D distance = d - s; 
	for (int  i = 1; i <= 100; i++) {
		std::vector<float> vector_distance = distance.ConvertToVector(distance);
		vector_distance[0] = (vector_distance[0] / 100 ) * i;
		vector_distance[1] = (vector_distance[1] / 100 ) * i;
		vector_distance[2] = (vector_distance[2] / 100 ) * i;
		Vector3D dist(vector_distance);
		dist = s + dist;
		std::vector<float> new_coordinate = dist.ConvertToVector(dist);
		path.push_back(new_coordinate);
	}
	std::vector<float> last =  {path[path.size()-1][0], path[path.size()-1][1] -200, path[path.size()-1][2]};
	path.push_back(last);
	return path;
}
void Drone::Scheduled_drone(IEntity* package, IEntity* dest, const IGraph* graph_) {
	if (GetPackage() == nullptr) {

		SetDroneToPack( get_beeline(GetPosition(), package->GetPosition() ) );
		SetPackage(dynamic_cast<Package*>(package));
		SetCurrRout("pack");
		SetPackToCustomer ( get_beeline(package->GetPosition(), dest->GetPosition() ));
		Package* pack = dynamic_cast<Package*>(package);
		pack->SetCustomer(dynamic_cast<Customer*>(dest));
		package_currently_delivering->OnSchedule();
				OnMove();
	} // close  if
}

void Drone::update_drone_movement(float dt) {
	if (GetPackage() != nullptr && GetPackage() != NULL) {
		if (Within_range(GetTargetPosition())) {
			if (IncrTarget()) {
				if (has_picked_up_getter()) {
					Drop_order();
					OnIdle();
				}
				else {
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
			if (v.Magnitude() > ( Vector3D (GetPosition() )- GetTargetPosition() ).Magnitude() ) {
				this->SetPosition(GetTargetPosition());
			}//close if for overshooting the target 
			else {						
				Vector3D positionToMove = Vector3D ( GetPosition())+v;
				this->SetPosition(positionToMove);
			} //close else for overshooting target
			Update_Package();
		} //close else of the within range if
		
	} //close get package check
}//close function 

void Drone::OnIdle() {
	picojson::object obj = JsonHelper::CreateJsonObject();
	JsonHelper::AddStringToJsonObject(obj, "type", "notify");
	JsonHelper::AddStringToJsonObject(obj, "value", "idle");
	const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
	entity_sub->OnEvent(val, *this);
}

void Drone::OnMove() {
	picojson::object obj = JsonHelper::CreateJsonObject();
	JsonHelper::AddStringToJsonObject(obj, "type", "notify");
	JsonHelper::AddStringToJsonObject(obj, "value", "moving");
	JsonHelper::AddStdVectorVectorFloatToJsonObject(obj, "path", *currentRout);
	const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
	entity_sub->OnEvent(val, *this);
}
}//close namespace 