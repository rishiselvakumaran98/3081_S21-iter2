#include "Parabolic.h"

namespace csci3081 {

	std::vector<std::vector<float>> Parabolic::GetPath(std::vector<float> source, std::vector<float> destination) {
		Vector3D vo (source);
		Vector3D ve (destination);
		Vector3D vm = ((vo+ve)*0.5);
		double t = 30.0; // 8.0
		// for loop to have maybe 10 points
		// 0 to 1 in discreet increments
		Vector3D vt = ((ve-vo)*(1.0/t));
		Vector3D v;
		std::vector<std::vector<float>> path;
		double offset = 20.0;
		for (int i = 0; i < t; i++) {
			v = vo+vt*i;
		double y = 1-pow( (v.DistanceBetween(vm)), 2)/pow( vo.DistanceBetween(vm), 2);
		double j = 150.0; 
		y = y*j;
		Vector3D temp (v[0], v[1]+y+offset, v[2]);
		path.push_back(Vector3D::ConvertToVector(temp));
	} //close for loop
	
	std::vector<float> vert = {float(ve[0]), float(ve[1]+offset), float(ve[2])};
	path.push_back(vert);
	path.push_back(destination);
	return path;
	} //close method 

}//end of namespace 