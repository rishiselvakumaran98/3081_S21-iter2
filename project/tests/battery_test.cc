#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <vector>
#include <iostream>
#include "Vector3D.h"
#include "Battery.h"
namespace csci3081 {

using entity_project::IEntity;

class BatteryTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
	  
	  b1 = new Battery();
	  
	  b2 = new Battery(5000, "power_source");
}

  virtual void TearDown() {}
  Battery* b1;
  Battery* b2;
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(BatteryTest, Is_Dead_tests) {
	EXPECT_EQ(false, b1->Is_dead());
	std::cout << "failing b1 on is_dead" << std::endl;

	EXPECT_EQ(false, b2->Is_dead());
	std::cout << "failing b2 on is_dead" << std::endl;
}//end function

TEST_F(BatteryTest, get_level_tests) {
	EXPECT_EQ(10000, b1->GetLevel());
	EXPECT_EQ(5000, b2->GetLevel());
}


TEST_F(BatteryTest, Change_level_tests) {
b2->change_level(6000);
	EXPECT_EQ(-1000, b2->GetLevel());

b2->change_level(-12000);
	EXPECT_EQ(11000, b2->GetLevel());

b1->change_level(-1000);
	EXPECT_EQ(11000, b1->GetLevel());
}

TEST_F(BatteryTest, constructor_test) {
	Battery bDefault;
	ASSERT_EQ(bDefault.GetLevel(), 10000);
	ASSERT_EQ(bDefault.GetModel(), "standard battery");
	
	Battery bComplex(5000, "new battery");
	
	ASSERT_EQ(bComplex.GetLevel(), 5000);
	ASSERT_EQ(bComplex.GetModel(), "new battery");
}

TEST_F(BatteryTest, GetModel_test) {
	Battery b(5000, "testing model");
	ASSERT_EQ("testing model", b.GetModel());
	}


TEST_F(BatteryTest, Is_Charged_test) {
	Battery b;
	ASSERT_EQ(true, b.Is_charged());
	}

//};// end class
} //close namespace

