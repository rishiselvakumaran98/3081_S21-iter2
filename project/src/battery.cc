#include "Battery.h"
#include <iostream>


namespace csci3081 {

bool Battery::Is_dead() {
	if (battery_level == 0) {
		return true;
	}
	return false;
}

int Battery::GetLevel() {
	return battery_level;
}

void Battery::change_level(float delta) {
	battery_level -= delta;
	// if (battery_level+delta <= 10000 && battery_level+delta >= 0) {
	// 	battery_level+=delta;
	// } //close if
	// else if (battery_level+delta > 10000) {
	// 	battery_level = 10000;
	// }//close max else if
	// else if( battery_level+delta  < 0) {
	// 	battery_level = 0;
	// } //close minimum if
}//end of function

bool Battery::Is_charged() {
	if (battery_level == 10000) {
		return true;
	}
			return false;
	}




}//end of namespace 
