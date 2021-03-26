#include<iostream>
#include<cmath>
#include "Vector3D.h"
#include "Vector2D.h"
#include<cstdio>
#include <cstring>

namespace csci3081 {

double Vector2D::Magnitude() {
	double temp  = sqrt(pow(x_, 2)+pow(y_, 2));
	return temp;
} //implementation of the function where the distance between each point is calculated and returned as the magnitude of the 2d vector

Vector2D Vector2D::Normalized() {

	double mag = Magnitude(); //get the magnitude of the current vector
	if (mag == 0.0) {
		return(Vector2D (0,0));
	}
	else {
	Vector2D temp;
	temp.x_ = (x_) / mag;
	temp.y_ = y_ / mag;
	//set up the current values of temp to the values of the current vector devided by the magnitude
		return temp;
}
} //end of the function normalized 

void Vector2D::Normalize() {	
	double mag = Magnitude(); //get the magnitude of the current vector
	if (mag != 0.0) {
	x_ = x_ / mag;
	y_ = y_ / mag;
}
	//set the current values of the vector to their value devided by the magnitude without returning anything
}//end of function normalize

double  Vector2D::DotProd(Vector2D v) {
	double temp = (x_*v.x_)+(y_*v.y_);
	return temp;
} //end of the dot product function

std::string  Vector2D::ToString() {
	char buff[50];
	std::memset(buff, 0, sizeof(buff));
	sprintf(buff, "(%f, %f)", x_, y_);
	std::string temp(buff);

	return temp;
} //end of ToString function 

Vector2D Vector2D::operator+(Vector2D v) {
	Vector2D temp;
	temp.x_ = x_+v.x_;
	temp.y_ = y_+v.y_;
	return temp;
} //add each member of the vector to a temp vector returning it

Vector2D Vector2D::operator-(Vector2D v) {
	Vector2D temp;
	temp.x_ = x_-v.x_;
	temp.y_ = y_-v.y_;
	return temp;
} //subtract each member of v and the current vector adding the result to temp and returning it at the end

Vector2D Vector2D::ConvertTo3D() {
	Vector2D temp;

	temp[0] = x_;
	temp[1]=0;
	temp[2]=y_;
	return temp;
} //convert Vector2D into a Vector3D as (x 0 y) as the coordinates.

Vector2D Vector2D::operator*(float multi) {
	Vector2D temp;
	temp.x_ = x_*multi;
	temp.y_ = y_*multi;
	return temp;
}

float Vector2D::DistanceBetween(Vector2D v) {
	Vector2D temp;
	temp = (*this)-v;
	return temp.Magnitude();
}//function to calculate distance between vectors 

bool Vector2D::operator==(const Vector2D v) const {
	if (v.x_ == x_ && v.y_ == y_) {
		return true;
	} // close if
	return false;
} //close function

double& Vector2D::operator[](int index_of_vector) {
	if (index_of_vector == 0) {
		return x_;
	}
	else if (index_of_vector == 1) {
		return y_;
	}
	std::perror("not a valid index for a Vector3D");
}//overload operator for the index


} //end of the namespace 
