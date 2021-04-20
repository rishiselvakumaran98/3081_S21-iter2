#include "Smart.h"

namespace csci3081 {

	std::vector<std::vector<float>> Smart::GetPath(std::vector<float> source, std::vector<float> destination) {
		return graph->GetPath(source, destination);
	}//close method
}//close namespace 
	