#ifndef PARABOLIC_H_
#define PARABOLIC_H_


#include "IStrategy.h"
#include <vector>
#include "Vector3D.h"
#include <cmath>

namespace csci3081 {
	/*******************************************************************************
    * Class Definitions
    ******************************************************************************/
    /**
    * @brief The base class for creating Parabolic route for the drone entities
    */
	class Parabolic : public IStrategy {
		public:
			/**
			 * @brief The GetPath method that formulates the coordinates for the Parabolic movement of the drone
			 */
			std::vector<std::vector<float>> GetPath(std::vector<float> source, std::vector<float> destination); 
		}; //close class
} //end of namespace 

#endif