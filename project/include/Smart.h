#include "IStrategy.h"

namespace csci3081 {
	
	class Smart : public IStrategy  {
	public:
		std::vector<std::vector<float>> GetPath(std::vector<float> source, std::vector<float> destination);
	}; //close class
}//close namespace 
