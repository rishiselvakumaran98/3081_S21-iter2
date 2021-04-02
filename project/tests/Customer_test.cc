#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
//#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <vector>

#include <iostream>
#include "Customer.h"
#include "Vector3D.h"

namespace csci3081 {

using entity_project::IEntity;

class CustomerTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
      
object = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(object, "type", "customer");
      JsonHelper::AddStringToJsonObject(object, "name", "testCustomer");
      JsonHelper::AddFloatToJsonObject(object, "radius", 100);
      JsonHelper::AddFloatToJsonObject(object, "speed", 0);
      JsonHelper::AddStdFloatVectorToJsonObject(object, "position", {5, 0, 0});
      JsonHelper::AddStdFloatVectorToJsonObject(object, "direction", {100, 650, 0});
	    customer = new Customer(object);
}

  virtual void TearDown() {}
  Customer *customer;
  picojson::object object;
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(CustomerTest, GetLocation_tests) {
//JsonHelper::Add<Customer>(testingCustomer, "position", "std::vector<float>(5, 0)")
	std::vector<float> v = {5,0,0};
	std::vector<float> cust_pos = customer->GetPosition();
	EXPECT_EQ(v, cust_pos);
}//end function

TEST_F(CustomerTest, constr_test) {
	Customer cust(object);
	ASSERT_EQ(picojson::value(object).serialize(), picojson::value(cust.GetDetails()).serialize() );
}


//};// end class
} //close namespace

