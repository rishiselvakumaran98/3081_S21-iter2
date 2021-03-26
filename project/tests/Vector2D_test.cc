#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include "../include/Vector2D.h"
namespace csci3081 {

using entity_project::IEntity;

class Vector2DTest : public ::testing::Test {

 protected:
  virtual void SetUp() {  }

  virtual void TearDown() {}
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(Vector2DTest, Magnitude_tests) {
	Vector2D v1(5, 0);
	Vector2D v2(0, 3);
	Vector2D v3(-5, -6);
	Vector2D v4(-4, -2);
	Vector2D v5(0, 0);
	
	EXPECT_EQ(5, v1.Magnitude());
	EXPECT_EQ(3, v2.Magnitude());
	EXPECT_EQ(sqrt(61), v3.Magnitude());
	EXPECT_EQ(sqrt(20), v4.Magnitude());
	EXPECT_EQ(0, v5.Magnitude());
}//end test for Magnitude


TEST_F(Vector2DTest, Normalized_tests) {
	Vector2D v1(5, 0);
	Vector2D v2(0, 3);
	Vector2D v3(0, -4);
	Vector2D v4(0, 0);


	EXPECT_EQ(Vector2D(1, 0), v1.Normalized());
	EXPECT_EQ(Vector2D(0, 1), v2.Normalized());
	EXPECT_EQ(Vector2D(0, -1), v3.Normalized());

	EXPECT_EQ(Vector2D(0, 0), v4.Normalized());
	std::cout << v4.ToString();

}//close test for normalized

TEST_F(Vector2DTest, Normalize_tests) {
	Vector2D v1(5, 0);
	Vector2D v2(0, 3);
	Vector2D v3(0, -4);
	Vector2D v4(0, 0);

	v1.Normalize();
	
	EXPECT_EQ(1.0, v1[0]);
	EXPECT_EQ(0.0, v1[1]);


	v2.Normalize();
	
	EXPECT_EQ(0.0, v2[0]);
	EXPECT_EQ(1.0, v2[1]);


	v3.Normalize();
	
	EXPECT_EQ(0.0, v3[0]);
	EXPECT_EQ(-1.0, v3[1]);

	try{
		v4.Normalize();
	}
	catch(std::exception zero_vector) {
		EXPECT_EQ(0.0, v4[0]);
		EXPECT_EQ(0.0, v4[1]);
	} //close catch 
}//close test for normalize


TEST_F(Vector2DTest, DotProd_tests) {
	Vector2D v1(5, 0);
	Vector2D v2(0, 3);
	Vector2D v3(0, -4);
	Vector2D v4(0, 0);

	EXPECT_EQ(0, v1.DotProd(v2));
	EXPECT_EQ(0, v1.DotProd(v3));
	EXPECT_EQ(0, v1.DotProd(v4));
	EXPECT_EQ(25, v1.DotProd(v1));
	EXPECT_EQ(9, v2.DotProd(v2));
}//close the test for dot product

TEST_F(Vector2DTest, ToString_tests) {
	Vector2D v1(5, 0);
	Vector2D v2(0, 3);
	Vector2D v3(0, -4);
	Vector2D v4(0, 0);

	EXPECT_EQ(std::string("(5.000000, 0.000000)"), v1.ToString());

	EXPECT_EQ(std::string("(0.000000, 3.000000)"), v2.ToString());

	EXPECT_EQ(std::string("(0.000000, -4.000000)"), v3.ToString());


	EXPECT_EQ(std::string("(0.000000, 0.000000)"), v4.ToString());
}//close test for ToString

TEST_F(Vector2DTest, operatorplus_tests) {
	Vector2D v1(5, 0);
	Vector2D v2(0, 3);
	Vector2D v3(0, -4);
	Vector2D v4(0, 0);

	EXPECT_EQ(Vector2D(5, 3), v1+v2);
	EXPECT_EQ(Vector2D(0, -1), v2+v3);
	EXPECT_EQ(Vector2D(0, -4), v3+v4);
	EXPECT_EQ(Vector2D(10, 0), v1+v1);
} //close the test for the operator plus 

TEST_F(Vector2DTest, operatorminus_tests) {
	Vector2D v1(5, 0);
	Vector2D v2(0, 3);
	Vector2D v3(0, -4);
	Vector2D v4(0, 0);

	EXPECT_EQ(Vector2D(5, -3), v1-v2);
	EXPECT_EQ(Vector2D(0, 7), v2-v3);
	EXPECT_EQ(Vector2D(5, 0), v1-v4);
	EXPECT_EQ(Vector2D(0, 0), v1-v1);
}//close the test for the minus operator

TEST_F(Vector2DTest, operatormultiplication_tests) {
	Vector2D v1(5, 0);
	Vector2D v2(0, 3);
	Vector2D v3(0, -4);
	Vector2D v4(0, 0);

	EXPECT_EQ(Vector2D(20, 0), v1*4);
	EXPECT_EQ(Vector2D(0, -20), v3*5);
	EXPECT_EQ(Vector2D(0, -27), v2*(-9));
	EXPECT_EQ(Vector2D(0, 0), v4*3);
}// close tests for the multiplication

TEST_F(Vector2DTest, distancebetween_tests) {
	Vector2D v1(100, 6);
	Vector2D v2(100, 10);
	Vector2D v3(100, -10);
	Vector2D v4(0, 0);

	EXPECT_EQ(4, v1.DistanceBetween(v2));
	EXPECT_EQ(16, v1.DistanceBetween(v3));
	EXPECT_FLOAT_EQ(v1.Magnitude(), v1.DistanceBetween(v4));
}//end of test for distance between 

TEST_F(Vector2DTest, operatorequality_tests) {
	Vector2D v1(5, 0);
	Vector2D v2(0, 3);
	Vector2D v3(0, -4);
	Vector2D v4(0, 0);

	EXPECT_EQ(true, v1== Vector2D(5, 0));
	EXPECT_EQ(false, v1==v2);
	EXPECT_EQ(false, v1==v4);
}//close equality test

TEST_F(Vector2DTest, operatorindex_tests) {
	Vector2D v1(5, 0);
	Vector2D v2(0, 3);
	Vector2D v3(0, -4);
	Vector2D v4(0, 0);

	EXPECT_EQ(5, v1[0]);
	EXPECT_EQ(0, v1[1]);


	v4[0] = 1;
	v4[1] = 2;
	EXPECT_EQ(Vector2D(1, 2), v4);
}//close tests for the index operator overload

TEST_F(Vector2DTest, constructor_default_tests) {
	Vector2D v;
	EXPECT_DOUBLE_EQ(v[0], 0);
	EXPECT_DOUBLE_EQ(v[1], 0);
}//close test for the default constructor


TEST_F(Vector2DTest, constructor_two_par_tests) {
	Vector2D v(1, 2);
	EXPECT_DOUBLE_EQ(v[0], 1);
	EXPECT_DOUBLE_EQ(v[1], 2);
}//close test for the  constr with three parameters

/*
TEST_F(Vector2DTest, constructor_vector_float_tests) {
	std::vector<float> vf;


	vf.push_back(1);
	vf.push_back(2);
	vf.push_back(3);

	Vector3D v(vf);
	EXPECT_DOUBLE_EQ(v[0], vf.at(0));

	EXPECT_DOUBLE_EQ(v[1], vf.at(1));
	EXPECT_DOUBLE_EQ(v[2], vf.at(2));
}//close test for the constructor that takes a vector float and makes a vector3d
*/
//}; //close class for Vector2D
}  // namespace csci3081
