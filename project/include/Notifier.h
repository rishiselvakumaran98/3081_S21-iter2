#ifndef NOTIFIER_H_
#define NOTIFIER_H_

#include "delivery_simulation.h"


namespace csci3081 {
	//this class will be responsible for dealing with Delivery simulation
	class Notifier {

	    void SetDeliverySimulation(DeliverySimulation* simu) {
	  	  simulation = simu;
	    }

	private:

	}; //close class
	
}//close namespace 

#endif