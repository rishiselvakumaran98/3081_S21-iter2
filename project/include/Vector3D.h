/**
 * @file Vector3D.h
 */
#ifndef VECTOR3D_H_
#define VECTOR3D_H_


/**
 * include
 */
#include <vector>
#include <string>

namespace csci3081 {
class Vector3D {
	/**
	 * @brief this class controls the functionality of the Vector3D objects. Mainly used for calculations, this class has many of the most common vector operations.
	 */
public:
	/**
	 * @brief  constructor for a vector3d
	 * @param x x-value of the vector
	 * @param y y-value of the vector
	 * @param z z-value of the vector
	 */
	Vector3D (double x, double  y, double  z)  {
		x_ = x; //set the private variable x_ to x;
		y_ = y; //set the private variable y_ to y;
		z_ = z; //set the private variable z_ to z
	}// constructor

	/**
	 * @brief default constructor setting all of the elements of the Vector3D to 0.
	 */
	Vector3D () {
		x_ = 0;
		y_ = 0;
		z_ = 0;
	} //default constructor setting the parameters of the vector to 0

	/**
	 * @brief this constructor takes in a std::vector<float> of size 3 and makes it into a Vector3D.
	 * @param v std::vector<float> of three elements to be converted to a Vector3D
	 */
	Vector3D( std::vector<float> v ) {
		x_ = v[0];
		y_ = v[1];
		z_ = v[2];
	} //constructor that takes a float vector and makes  a Vector3D

	/**
	 * @brief method to calculate the magnitude of the vector3d.
	 */
	double Magnitude();
	
	/**
	 * @brief returns a normalized version of the same vector3D
	 */
	Vector3D Normalized();
	/**
	 * @brief  normalizes the current vector3d
	 */
	void Normalize();
	/**
	 * @brief returns the dot product between the current vector3d and the argument passed
	 * @param v vector to be used on the Dot product calculation
	 */
	double  DotProd(Vector3D v);
	/**
	 * @brief returns the current vector in string format
	 */
	std::string ToString();

	/**
	 * @brief operator overload for addition
	 * @param v vector to be added to current vector
	 */
	Vector3D operator+(Vector3D v);

	/**
	 * @brief operator overload for subtraction of vectors
	 * @param v vector to be subtracted from current vector
	 */
	Vector3D operator-(Vector3D v);

	/**
	 * @brief multiplies the current vector by an float passed by the user
	 * @param multi float that will multiply the intire vector3d
	 */
	Vector3D operator*(float multi);
	/**
	 * @brief Takes the cross product between the current vector and the Vector3D passed by the user.
	 * @param v Vector3D to be crossed with current vector
	 */
	Vector3D Cross(Vector3D v); //

	/**
	 * @brief calculates the distance between two vectors
	 * @param v vector3d far from current vector3d that the user is trying to find the distance
	 */
	float DistanceBetween(Vector3D v); //

	/**
	 * @brief overload the equality operator
	 * @param v Vector3D to be compared with current Vector3D
	 */
	bool operator==( const Vector3D v) const ;
	/**
	 * @brief overload the index operator
	 * @param index_of_vector integer between 0 and 2 that correspond to a specific index on the Vector3D
	 */
	double& operator[](int index_of_vector);

	/**
	 * @brief function to convert from std::vector<float> to a Vector3D
	 * @param v std::vector<float> of size 3 to be converted into a Vector3D
	 */
static std::vector<float> ConvertToVector(const Vector3D v);
private:
	double x_;
	double y_;
	double z_;

}; //end of the class 
} //end of the name space 


#endif
