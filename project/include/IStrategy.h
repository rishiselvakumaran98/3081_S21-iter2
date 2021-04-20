#ifndef ISTRATEGY_H_
#define ISTRATEGY_H_

#include <EntityProject/facade/delivery_system.h>
#include <vector>

namespace csci3081 {
	class IStrategy {
		public:
			virtual std::vector<std::vector<float>> GetPath(std::vector<float> source, std::vector<float> destination) = 0; //this method will be overwritten in each class to return its pattern
			void SetGraph(const IGraph* graph_) { graph = graph_; };
		protected:
			const IGraph* graph;
	}; //close class 
}

#endif