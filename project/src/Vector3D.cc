#include<iostream>
#include<cmath>
#include "Vector3D.h"
#include<cstdio>
#include <stdexcept>
#include <vector>
#include <cstring>

namespace csci3081 {

double Vector3D::Magnitude() {
	double temp  = sqrt(pow(x_, 2)+pow(y_, 2)+pow(z_, 2));
	return temp;
} //implementation of the function where the distance between each point is calculated and returned as the magnitude of the 3d vector


Vector3D Vector3D::Normalized() {
	double mag = Magnitude(); //get the magnitude of the current vector
	if (mag == 0.0) {
		std::cout << "division by zero" << std::endl;
		return Vector3D(0, 0, 0);
	} //close if
	Vector3D temp;
	temp.x_ = (x_) / mag;
	temp.y_ = y_ / mag;
	temp.z_ = z_ / mag;
	//set up the current values of temp to the values of the current vector devided by the magnitude
	return temp;
} //end of the function normalized 

void Vector3D::Normalize() {	
	double mag = Magnitude(); //get the magnitude of the current vector
	if (mag == 0.0) {
		std::perror("division by 0 error");
	}//close if 
	x_ = x_ / mag;
	y_ = y_ / mag;
	z_ = z_ / mag;
	//set the current values of the vector to their value devided by the magnitude without returning anything
}//end of function normalize

double  Vector3D::DotProd(Vector3D v) {
	double temp = (x_*v.x_)+(y_*v.y_)+(z_*v.z_);
	return temp;
} //end of the dot product function

std::string  Vector3D::ToString() {
	char buff[50];
	std::memset(buff, 0, sizeof(buff));
	sprintf(buff, "(%f, %f, %f)", x_, y_, z_);
	std::string temp(buff);
	return temp;
} //end of ToString function 


Vector3D Vector3D::operator+(Vector3D v) {
	Vector3D temp;
	temp.x_ = x_+v.x_;
	temp.y_ = y_+v.y_;
	temp.z_ = z_+v.z_;
	return temp;
} //operator plus for Vector3D

Vector3D Vector3D::operator-(Vector3D v) {
	Vector3D temp;
	temp.x_ = x_-v.x_;
	temp.y_ = y_-v.y_;
	temp.z_ = z_-v.z_;
	return temp;
} //subtraction of two vectors 

Vector3D Vector3D::operator*(float multi) {
	Vector3D temp;
	temp.x_ = x_*multi;
	temp.y_ = y_*multi;
	temp.z_ = z_*multi;
	return temp;
} //multiplication by a float and a vector

Vector3D Vector3D::Cross(Vector3D v) {
	Vector3D temp;
	temp.x_ = ((y_*v.z_)-(z_*v.y_));
	temp.y_ = ((x_*v.z_)-(z_*v.x_));
	temp.z_ = ((x_*v.y_)-(y_*v.x_));
	return temp;
}

float Vector3D::DistanceBetween(Vector3D v) {
	Vector3D temp1;
	temp1 = (*this)-v;
	return temp1.Magnitude();
} //calculate the distance between two vectors by taking the magnitude of the direction vector

bool Vector3D::operator==(const Vector3D v) const  {
	double limit = 0.05;
	if (abs(v.x_-x_)  < limit  && abs(v.y_-y_) < limit && abs(v.z_-z_) < limit) {
		return true;
	} // close if
	return false;
} //close function

double& Vector3D::operator[](int index_of_vector) {
	if (index_of_vector == 0) {
		return x_;
	}
	else if (index_of_vector == 1) {
		return y_;
	}
	else if (index_of_vector == 2) {
		return z_;
	}
	std::perror("not a valid index for a Vector3D");
}//overload operator for the index

 std::vector<float> Vector3D::ConvertToVector(const Vector3D v) {
	 std::vector<float> temp(3);
	 temp[0] = v.x_;
	 temp[1] = v.y_;
	 temp[2] = v.z_;
	 return temp;
 }

} //end of the namespace 