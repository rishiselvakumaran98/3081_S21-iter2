#ifndef PARABOLIC_H_
#define PARABOLIC_H_


#include "IStrategy.h"
#include <vector>
#include "Vector3D.h"
#include <cmath>

namespace csci3081 {
	class Parabolic : public IStrategy {
	public:
		std::vector<std::vector<float>> GetPath(std::vector<float> source, std::vector<float> destination); 
	}; //close class
} //end of namespace 

#endif