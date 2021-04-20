#include "IStrategy.h"

namespace csci3081 {
	/*******************************************************************************
    * Class Definitions
    ******************************************************************************/
    /**
    * @brief The base class for creating Smart route for the drone entities
    */
	class Smart : public IStrategy  {
		public:
			/**
			 * @brief The GetPath method that formulates the coordinates for the Smart movement of the drone from the IGraph method
			 */
			std::vector<std::vector<float>> GetPath(std::vector<float> source, std::vector<float> destination);
		}; //close class
}//close namespace 
