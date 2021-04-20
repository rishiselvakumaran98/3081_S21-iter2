#include "Battery.h"
#include <iostream>


namespace csci3081 {
	bool Battery::Is_dead() {
		if (battery_level == 0) {
			return true;
		}
		return false;
	}

	float Battery::GetLevel() {
		return battery_level;
	}

	void Battery::change_level(float delta) {
		battery_level -= delta;
	}//end of function

	bool Battery::Is_charged() {
		if (battery_level == 10000) {
			return true;
		}
		return false;
	}
}//end of namespace 
