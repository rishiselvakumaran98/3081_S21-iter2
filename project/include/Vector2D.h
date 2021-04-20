/**
 * @file Vector2D.h
 */
#ifndef VECTOR2D_H_
#define VECTOR2D_H_

namespace csci3081 {
	/**
	 * @brief this class is very simular to Vector3D.h, however it works for Vectors of size 2.
	 */
	class Vector2D {
		public:
			/**
			 * @brief constructor for Vector2D with two parameters
			 * @param x x-value of the vector
			 * @param y y-value of the vector
			 */
			Vector2D (double x, double  y)  {
				x_ = x; //set the private variable x_ to x;
				y_ = y; //set the private variable y_ to y;
			}// constructor

			/**
			 * @brief default constructor where all of the elements of Vector2D are set to 0.
			 */
			Vector2D () {
				x_ = 0;
				y_ = 0;
			} //default constructor setting the parameters of the vector to 0
			/**
			 * @brief calculates the magnitude of the vector2d
			 */
			double Magnitude();

			/**
			 * @brief returns a normalized version of the same vector2d 
			 */
			Vector2D Normalized();

			/**
			 * @brief normalizes the current Vector2D
			 */
			void Normalize();

			/**
			 * @brief returns the dot product between the current vector2d and v
			 * @param  v vector 2d to be used on the dot product with current Vector2D.
			 */
			double  DotProd(Vector2D v);


			/**
			 * @brief returns the current vector in string format
			 */
			std::string ToString();

			/**
			 * @brief operator overload for addition
			 * @param v Vector2D to be added with current Vector2D
			 */
			Vector2D operator+(Vector2D v);

			/**
			 * @brief operator overload for subtraction of vectors
			 * @param v Vector2D to be subtracted from current Vector2D.
			 */
			Vector2D operator-(Vector2D v);

			/**
			 * @brief convert the current Vector2D in Vector3D by adding an extra coordinate in the format (x, 0, z) where z in the new vector was y in the Vector2D
			 */
			Vector3D ConvertTo3D();

			/**
			 * @brief function that multiplies intire Vector2D by an float.
			 * @param   multi value that that will multiply the elements of te current Vector2D
			 */
			Vector2D operator*(float multi);

			/**
			 * @brief calculates the distance between two vectors
			 * @param v Vector2D which the user is trying to find the distance to current Vector2D
			 */
			float DistanceBetween(Vector2D v);

			/**
			 * @brief overload the equality operator
			 * @param v Vector2D to be compared with the current Vector2D
			 */
			bool operator==(const Vector2D v) const;

			/**
			 * @brief overload the index operator 
			 * @param index_of_vector integer either 0 or 1 to return either the first or second element of the Vector2D respectivaly
			 */
			double& operator[](int index_of_vector);

		private:
			double x_;
			double y_;
		}; //end of the class 
} //end of the name space 


#endif
