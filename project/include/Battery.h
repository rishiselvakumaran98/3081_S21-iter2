/**
 * @file Battery.h
 */
#ifndef BATTERY_H_
#define BATTERY_H_

/**
 * include
 */
#include <iostream>
#include <string>

namespace csci3081 {
   /*******************************************************************************
    * Class Definitions
    ******************************************************************************/
   /**
    * @brief The base class for creatingbatteries
    */
class Battery {
public:

	/**
	 * @brief default constructor for a Battery object where the battery capacity is set to the fixed max capacity of 10000 and the model to "standard battery"
	 */
	Battery() {
		battery_level = max_capacity;
		model = "standard battery";
	}

	/**
	 * @brief more complex constructor for a battery object
	 * @param x the max capacity that the battery will support, 
	 * @param y the model of the battery.
	 */
	Battery(float x, std::string y) {
		battery_level = x;
		model = y;
	} //end of constructor

	/**
	 * @brief function to check if the battery has reached its 0 level and therefore is considered dead
	 */
	bool Is_dead();
	
	/**
	 * @brief function to check if the maximum capacity of the battery is achieved and its level is then at 100%
	 */
	bool Is_charged();

	/**
	 * @brief returns the battery level
	 */
	int GetLevel();


	/**
	 * @brief this function controls the battery level, changing it according to the value passed by the user
	 * @param delta is the amount by how much the battery level should be changed
	 */
	void change_level(int delta);

	/**
	 * @brief returns the model of the Battery in string format
	 */
	std::string GetModel() {
		return model;
	}
	
	
private:
	int battery_level;
			std::string model;
	const float max_capacity =10000;
};//end of class
}//end of the namespace 
#endif
