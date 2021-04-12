#include "Beeline.h"
namespace csci3081 {

std::vector<std::vector<float>> Beeline::GetPath(std::vector<float> source, std::vector<float> destination) {
	std::vector<std::vector<float>> path;
	source[1] += 200;
	destination[1] += 200;
	Vector3D s(source);
	Vector3D d(destination);
	Vector3D distance = d - s; 
	for (int  i = 1; i <= 100; i++) {
		std::vector<float> vector_distance = distance.ConvertToVector(distance);
		vector_distance[0] = (vector_distance[0] / 100 ) * i;
		vector_distance[1] = (vector_distance[1] / 100 ) * i;
		vector_distance[2] = (vector_distance[2] / 100 ) * i;
		Vector3D dist(vector_distance);
		dist = s + dist;
		std::vector<float> new_coordinate = dist.ConvertToVector(dist);
		path.push_back(new_coordinate);
	}
	std::vector<float> last =  {path[path.size()-1][0], path[path.size()-1][1] -200, path[path.size()-1][2]};
	path.push_back(last);
	return path;
}

} //close namespace 