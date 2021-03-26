#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include "../include/Vector3D.h"
namespace csci3081 {

using entity_project::IEntity;

class Vector3DTest : public ::testing::Test {
public:
	Vector3D v1;
	Vector3D v2;
	Vector3D v3;
	Vector3D v4;
	Vector3D v5;

 protected:
	 
  virtual void SetUp() {
  	v1= Vector3D(5, 0, 0);
  	v2 = Vector3D(0, 3, 4);
  	v3 = Vector3D(-5, -6, -1);
  	v4 = Vector3D(-4, -2, 0);
  	v5 = Vector3D(0, 0, 0);
    }

  virtual void TearDown() {}
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(Vector3DTest, Magnitude_tests) {

	EXPECT_EQ(5, v1.Magnitude());
	EXPECT_EQ(5, v2.Magnitude());
	EXPECT_EQ(sqrt(62), v3.Magnitude());
	EXPECT_EQ(sqrt(20), v4.Magnitude());
	EXPECT_EQ(0, v5.Magnitude());
}//end test for Magnitude


TEST_F(Vector3DTest, Normalized_tests) {
	EXPECT_EQ(Vector3D(1, 0, 0), v1.Normalized());
	EXPECT_EQ(Vector3D(0, 1, 0), v2.Normalized());
	EXPECT_EQ(Vector3D(0, 0, -1), v3.Normalized());
	EXPECT_EQ(Vector3D(0, 0, 0), v4.Normalized());
}//close test for normalized

 TEST_F(Vector3DTest, Normalize_test) {

	v1.Normalize();
	EXPECT_EQ(Vector3D(1, 0, 0), v1);
	
 	v2.Normalize();
	
	
	EXPECT_EQ(Vector3D(0, 0.6, 0.8), v2);
	/*;
 	v3.Normalize();
 	EXPECT_DOUBLE_EQ(-0.635001, v3[0]); 
	EXPECT_EQ(-0.762001, v3[1]); 
	EXPECT_EQ(-0.127, v3[2]); 
	std::cout << "failed on v3 of normalize" << std::endl;
	*/
 	try{ 
		v5.Normalize(); 
	} 
	catch(std::exception zero_vector) {
		EXPECT_EQ(Vector3D(0, 0, 0), v5);
 	} //close catch 

	 }//close test for normalize



TEST_F(Vector3DTest, DotProd_tests) {
	Vector3D v10 = Vector3D(5, 0, 0);
	Vector3D v11 = Vector3D(0, 3, 0);
	Vector3D v13 = Vector3D(0, 0, -4);
	Vector3D v14 = Vector3D(0, 0, 0);

	EXPECT_EQ(0, v10.DotProd(v11));
	EXPECT_EQ(0, v10.DotProd(v13));
	EXPECT_EQ(0, v10.DotProd(v14));
	EXPECT_EQ(25, v10.DotProd(v10));
	EXPECT_EQ(9, v11.DotProd(v11));
}//close the test for dot product

TEST_F(Vector3DTest, ToString_tests) {
//  	v1= Vector3D(5, 0, 0);
//  	v2 = Vector3D(0, 3, 4);
////  	v3 = Vector3D(-5, -6, -1);
//  	v4 = Vector3D(-4, -2, 0);
//  	v5 = Vector3D(0, 0, 0);

	EXPECT_EQ(std::string("(5.000000, 0.000000, 0.000000)"), v1.ToString());

	EXPECT_EQ(std::string("(0.000000, 3.000000, 4.000000)"), v2.ToString());

	EXPECT_EQ(std::string("(-5.000000, -6.000000, -1.000000)"), v3.ToString());


	EXPECT_EQ(std::string("(0.000000, 0.000000, 0.000000)"), v5.ToString());
}//close test for ToString

TEST_F(Vector3DTest, operatorplus_tests) {

  	v1= Vector3D(5, 0, 0);
  	v2 = Vector3D(0, 3, 4);
  	v3 = Vector3D(-5, -6, -1);
  	v4 = Vector3D(-4, -2, 0);
  	v5 = Vector3D(0, 0, 0);

	EXPECT_EQ(Vector3D(5, 3, 4), v1+v2);

	EXPECT_EQ(Vector3D(-5, -3, 3), v2+v3);
	EXPECT_EQ(Vector3D(-5, -6, -1), v3+v5);
	EXPECT_EQ(Vector3D(10, 0, 0), v1+v1);
} //close the test for the operator plus 

TEST_F(Vector3DTest, operatorminus_tests) {

	EXPECT_EQ(Vector3D(5, -3, -4), v1-v2);
	EXPECT_EQ(Vector3D(5, 9, 5), v2-v3);
	EXPECT_EQ(Vector3D(5, 0, 0), v1-v5);
	EXPECT_EQ(Vector3D(0, 0, 0), v1-v1);
}//close the test for the minus operator

TEST_F(Vector3DTest, operatormultiplication_tests) {
	EXPECT_EQ(Vector3D(20, 0, 0), v1*4);
	EXPECT_EQ( Vector3D(-25, -30, -5), v3*5);
	EXPECT_EQ(Vector3D(0, -27, -36), v2*(-9));
	EXPECT_EQ(Vector3D(0, 0, 0), v5*3);
}// close tests for the multiplication

 TEST_F(Vector3DTest, Cross_tests) {
	 Vector3D v10 = Vector3D(5, 0, 0);
	 Vector3D v11 = Vector3D(0, 3, 0);
	 Vector3D v13 = Vector3D(0, 0, -4);
	 Vector3D v14 = Vector3D(0, 0, 0);

Vector3D v10_(0, 0, 15);
Vector3D v10_11 = v10.Cross(v11);

	 	ASSERT_DOUBLE_EQ(v10_[0], v10_11[0]);
	 	ASSERT_DOUBLE_EQ(v10_[1], v10_11[1]);
	 	ASSERT_DOUBLE_EQ(v10_[2], v10_11[2]);
		

		ASSERT_EQ( Vector3D(0, -20, 0), v10.Cross(v13));
		ASSERT_EQ(Vector3D(0, 20, 0), v13.Cross(v10));
		ASSERT_EQ(Vector3D(0, 0, 0), v10.Cross(v14));
				 } //close tests for cross product

TEST_F(Vector3DTest, distancebetween_tests) {
	EXPECT_TRUE((v1.DistanceBetween(v2) >= 7.07-0.05) && (v1.DistanceBetween(v2) <= 7.07+0.05)); // test for the range since exact values are difficult in floats
	EXPECT_TRUE((v1.DistanceBetween(v3) >= 11.7-0.05) && (v1.DistanceBetween(v3) <= 11.7+0.05)); // test for the range since exact values are difficult in floats

//	EXPECT_EQ(v1.Magnitude(), v1.DistanceBetween(v4));
}//end of test for distance between 

TEST_F(Vector3DTest, operatorequality_tests) {
	EXPECT_EQ(true, v1 == (Vector3D(5, 0, 0)));
	EXPECT_EQ(false, v1 == v2);
	EXPECT_EQ(false, v1 == v4);
}//close equality test

TEST_F(Vector3DTest, operatorindex_tests) {
	EXPECT_EQ(5, v1[0]);
	EXPECT_EQ(0, v1[1]);
	EXPECT_EQ(0, v1[2]);

	v4[0] = 1;
	v4[1] = 2;
	v4[2] = 3;
	EXPECT_EQ(Vector3D(1, 2, 3), v4);
}//close tests for the index operator overload

TEST_F(Vector3DTest, constructor_default_tests) {
	Vector3D v;
	EXPECT_DOUBLE_EQ(v[0], 0);
	EXPECT_DOUBLE_EQ(v[1], 0);
	EXPECT_DOUBLE_EQ(v[2], 0);

}//close test for the default constructor


TEST_F(Vector3DTest, constructor_three_par_tests) {
	Vector3D v(1, 2, 3);
	EXPECT_DOUBLE_EQ(v[0], 1);
	EXPECT_DOUBLE_EQ(v[1], 2);
	EXPECT_DOUBLE_EQ(v[2], 3);
}//close test for the  constr with three parameters


TEST_F(Vector3DTest, constructor_vector_float_tests) {
	std::vector<float> vf;


	vf.push_back(1);
	vf.push_back(2);
	vf.push_back(3);

	Vector3D v(vf);
	EXPECT_DOUBLE_EQ(v[0], vf.at(0));

	EXPECT_DOUBLE_EQ(v[1], vf.at(1));
	EXPECT_DOUBLE_EQ(v[2], vf.at(2));
}//close test for the constructor that takes a vector float and makes a vector3d

//}; //close test class

}  // namespace csci3081
