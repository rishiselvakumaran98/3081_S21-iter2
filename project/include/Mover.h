#ifndef MOVER_H
#define MOVER_H

#include <EntityProject/facade/delivery_system.h>
#include "entity_base.h"
#include <vector>
#include <string>
#include "ISubject.h"




namespace csci3081 {

	class Mover : public csci3081::EntityBase{

	public:
		Mover(const picojson::object& details_):EntityBase(details_) {
			details = details_;
		}
	void OnIdle();
		void OnMove();
	protected:
			std::vector<std::vector<float>>* currentRout;
			
	}; //close class 
	
} //close namespace 

#endif