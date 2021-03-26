#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>

#include <EntityProject/entity.h>
#include "json_helper.h"
#include <vector>

#include <iostream>
#include "Package.h"
#include "Vector3D.h"
#include "Customer.h"

namespace csci3081 {

using entity_project::IEntity;

class PackageTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
      
	  object = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(object, "type", "package");
      JsonHelper::AddStringToJsonObject(object, "name", "testPackage");
      JsonHelper::AddFloatToJsonObject(object, "radius", 100);
      JsonHelper::AddFloatToJsonObject(object, "speed", 0);
      JsonHelper::AddStdFloatVectorToJsonObject(object, "position", {50, 0, 0});
      JsonHelper::AddStdFloatVectorToJsonObject(object, "direction", {100, 650, 200});
	    package = new Package(object);
		
		double w = 10.0;
		Customer* cust = nullptr;
		Vector3D v(50, 0, 0);
		p2 = new Package(w, cust, v, object);
}

  virtual void TearDown() {}
    Package* package;
	Package* p2;
	picojson::object object;
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(PackageTest, GetLocation_tests) {
//JsonHelper::Add<Customer>(testingCustomer, "position", "std::vector<float>(5, 0)")
	std::vector<float> v = {50,0,0};
	std::vector<float> pack_pos = package->GetPosition();
	EXPECT_EQ(v, pack_pos);
}//end function

TEST_F(PackageTest, GetWeight_tests) {
	double w1 = 10.0;
		EXPECT_DOUBLE_EQ(w1, p2->GetWeight());
} //close test for getweight

TEST_F(PackageTest, GetRecipient_tests) {
	Customer* cust1 = nullptr;
	EXPECT_EQ(cust1, p2->GetRecipient());
} //close test for get recipient

TEST_F(PackageTest, SetWeight_tests) {
	p2-> SetWeight(50.0);
	EXPECT_DOUBLE_EQ(50.0, p2->GetWeight());
} //close test for setweight

TEST_F(PackageTest, SetCustomer_tests) {
	Customer recipient(object);
	p2->SetCustomer(&recipient);
	EXPECT_EQ(&recipient, p2->GetRecipient());
} //close test for recipient setter

TEST_F(PackageTest, constr_test) {
	Package p1(object);

	ASSERT_EQ(picojson::value(object).serialize(), picojson::value( p1.GetDetails() ).serialize() ); //test for the default constructor
	ASSERT_DOUBLE_EQ(0.0, p1.GetWeight());
	ASSERT_EQ(p1.GetRecipient(), nullptr);
//	ASSERT_EQ(Vector3D(0, 0, 0), p1.GetVDir());
	/*
	Vector3D pos = p1.GetVDir();
	ASSERT_DOUBLE_EQ(0, pos[0]);

	ASSERT_DOUBLE_EQ(0, pos[1]);

		ASSERT_DOUBLE_EQ(0, pos[02]);
	*/
	}
	
TEST_F(PackageTest, constr_complex_test) {
	Customer* cust;
	Package pack(20.0, cust, Vector3D (40, 30, 10), object);
	

	ASSERT_EQ(picojson::value(object).serialize(), picojson::value( pack.GetDetails() ).serialize() ); //test for the  constructor
	ASSERT_DOUBLE_EQ(20.0, pack.GetWeight());
	ASSERT_EQ(pack.GetRecipient(), cust);


	Vector3D d = pack.GetVDir();
	ASSERT_DOUBLE_EQ(40, d[0]);
	ASSERT_DOUBLE_EQ(30, d[1]);
	ASSERT_DOUBLE_EQ(10, d[2]);

	}


	//};// end class
} //close namespace

