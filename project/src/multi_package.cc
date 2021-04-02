#include "multi_package.h"

namespace csci3081 {
    void Multi_package::Schedule_Multiple_Delivery_Drone(IEntity* deliverer, vector<Package*> packages, const IGraph* graph){
        // 1. Should the entity be checked in this method 
        const picojson::object& temp = deliverer->GetDetails();
		if (JsonHelper::GetString(temp, "type") == "drone") {
            Drone* nextDrone   = dynamic_cast<Drone*>(deliverer);
            // nextDrone->Scheduled_drone();
        }
    }
}