#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <vector>
#include <iostream>
#include "Customer.h"
#include "Vector3D.h"
#include "robot.h"

namespace csci3081 {

using entity_project::IEntity;

class Robottest : public ::testing::Test {

 protected:
  virtual void SetUp() {
	  
	  object = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(object, "type", "customer");
      JsonHelper::AddStringToJsonObject(object, "name", "testCustomer");
      JsonHelper::AddFloatToJsonObject(object, "radius", 100);
      JsonHelper::AddFloatToJsonObject(object, "speed", 0);
      JsonHelper::AddStdFloatVectorToJsonObject(object, "position", {5, 0, 0});
      JsonHelper::AddStdFloatVectorToJsonObject(object, "direction", {100, 650, 0});
	    robot  = new Robot(object);
		
		float sp = 200.0;
		Battery* power_source =  new Battery();
		robutConstr = new Robot(sp, power_source, object);
		
		std::vector<float> pos;
		std::vector<float> dir;
		
		pos.push_back(50);
		pos.push_back(0);

		dir.push_back(0);
		dir.push_back(30);

		robot2 = new Robot(pos, dir, object);
}

  virtual void TearDown() {}
  Robot* robot;
  Robot* robot2;
  Robot* robutConstr;
  picojson::object object;
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(Robottest, default_constr_tests) {
	
				ASSERT_NE(nullptr,  robot);
	}//end function

	TEST_F(Robottest, pos_dir_constr_tests) {
		std::vector<float> v;
		v.push_back(50);
		v.push_back(0);

		ASSERT_EQ(v, robot2->GetPosition());
		std::vector<float> d;
		d.push_back(0);
		d.push_back(30);
		ASSERT_EQ(d, robot2->GetDirection());

		ASSERT_NE(nullptr, robot2);
	} //close test for the constructor with a direction and a position vector floats

	TEST_F(Robottest, within_range_test) {
		
		std::vector<float> v;
		v.push_back(1);
		v.push_back(0);
		v.push_back(3);
		
		std::vector<std::vector<float>> v_;
		v_.push_back(v);

		robot->SetRobotToPack(v_);
				robot->SetCurrRout("pack");
		ASSERT_EQ(Vector3D(1,3), robot->GetTargetPosition() );
	}
	TEST_F(Robottest, Incr_target_test) {
		std::vector<float> v;
		v.push_back(1);
		v.push_back(0);
		v.push_back(3);
		
		std::vector<float> v2;
		v2.push_back(4);
		v2.push_back(0);
		v2.push_back(6);

		std::vector<std::vector<float>> v_;
		v_.push_back(v);
		v_.push_back(v2);
		
		robot->SetRobotToPack(v_);
				robot->SetCurrRout("pack");
				robot->IncrTarget();
		// std::cout << "Actual Vector: " << Vector3D(4,6)[0] << "," << Vector3D(4,6)[1] << "," << Vector3D(4,6)[2] << std::endl;
		// std::cout << "Robot Vector: " << robot->GetTargetPosition()[0] << "," << robot->GetTargetPosition()[1] << "," << robot->GetTargetPosition()[2] << std::endl;
		ASSERT_EQ(Vector3D(4,6), robot->GetTargetPosition() );
	}
	TEST_F(Robottest, get_package_test) {
		Package pack(object);
		robot->SetPackage(&pack);
		ASSERT_NE(robot->GetPackage(), nullptr);
		ASSERT_EQ(robot->GetPackage(), &pack);
	}

	TEST_F(Robottest, set_package_test) {
		Package pack(object);
		robot->SetPackage(&pack);
		ASSERT_EQ(&pack, robot->GetPackage());
	}
	TEST_F(Robottest, set_robot_to_pack_test) {
		std::vector<float> v;
		v.push_back(1);
		v.push_back(0);
		v.push_back(3);
		
		std::vector<float> v2;
		v2.push_back(4);
		v2.push_back(0);
		v2.push_back(6);

		std::vector<std::vector<float>> v_;
		v_.push_back(v);
		v_.push_back(v2);
		
		robot->SetRobotToPack(v_);
				robot->SetCurrRout("pack");
//				Vector3D curR = Vector3D (robot->GetCurrRout() );
				for (int i = 0; i < v_.size(); i++) {
					// std::cout << "Actual Vector: " << Vector3D (v_[i][0], v_[i][2])[0] << "," << Vector3D (v_[i][0], v_[i][2])[1] << "," << Vector3D (v_[i][0], v_[i][2])[2] << std::endl;
					// std::cout << "Robot Vector: " << robot->GetTargetPosition()[0] << "," << robot->GetTargetPosition()[1] << "," << robot->GetTargetPosition()[2] << std::endl;
					ASSERT_EQ(Vector3D (v_[i][0], v_[i][2]), robot->GetTargetPosition() );
					robot->IncrTarget();
				}
	}
	TEST_F(Robottest, set_pack_to_customer_test) {
		std::vector<float> v;
		v.push_back(1);
		v.push_back(0);
		v.push_back(3);
		
		std::vector<float> v2;
		v2.push_back(4);
		v2.push_back(0);
		v2.push_back(6);

		std::vector<std::vector<float>> v_;
		v_.push_back(v);
		v_.push_back(v2);
		
		robot->SetPackToCustomer(v_);
				robot->SetCurrRout("customer");
//				Vector3D curR = Vector3D (robot->GetCurrRout() );
				
				for (int i = 0; i < v_.size(); i++) {
					// std::cout << "Actual Vector: " << Vector3D (v_[i][0], v_[i][1])[0] << "," << Vector3D (v_[i][0], v_[i][1])[1] << "," << Vector3D (v_[i][0], v_[i][1])[2] << std::endl;
					// std::cout << "Robot Vector: " << robot->GetTargetPosition()[0] << "," << robot->GetTargetPosition()[1] << "," << robot->GetTargetPosition()[2] << std::endl;
					ASSERT_EQ(Vector3D (v_[i][0], v_[i][2]), robot->GetTargetPosition());
					// ASSERT_EQ(Vector3D (v_[i][0], v_[i][1])[1], robot->GetTargetPosition()[1]);
					// ASSERT_EQ(Vector3D (v_[i][0], v_[i][1])[2], robot->GetTargetPosition()[2]);
					robot->IncrTarget();
				}

	}

	TEST_F(Robottest, Within_range_test) {
		Vector3D v(1000, 20);
		
		ASSERT_EQ(false, robot->Within_range(v));
		
			Vector3D v1 (6, 0);
		ASSERT_EQ(true, robot->Within_range(v1) );
	}
	TEST_F(Robottest, get_speed_test) {
		ASSERT_EQ(0, robot->GetSpeed() );
	}

	TEST_F(Robottest, has_picked_getter_test) {
		Package pack(object);
		robot->SetPackage(&pack);
		
		ASSERT_EQ(false, robot->has_picked_up_getter());
		

		ASSERT_EQ(false, robot->has_picked_up_getter() );
	}

	TEST_F(Robottest, get_cur_index_test) {
		Package pack(object);
		robot->SetPackage(&pack);
	
		
		std::vector<float> v;
		v.push_back(1);
		v.push_back(0);
		v.push_back(3);
		
		std::vector<float> v2;
		v2.push_back(4);
		v2.push_back(0);
		v2.push_back(6);

		std::vector<std::vector<float>> v_;
		v_.push_back(v);
		v_.push_back(v2);
		
		robot->SetRobotToPack(v_);
				robot->SetCurrRout("pack");
//				Vector3D curR = Vector3D (robot->GetCurrRout() );
				for (int i = 0; i < v_.size(); i++) {
					std::cout << "Actual Vector: " << Vector3D (v_[i][0], v_[i][2])[0] << "," << Vector3D (v_[i][0], v_[i][2])[1] << "," << Vector3D (v_[i][0], v_[i][2])[2] << std::endl;
					std::cout << "Robot Vector: " << robot->GetTargetPosition()[0] << "," << robot->GetTargetPosition()[1] << "," << robot->GetTargetPosition()[2] << std::endl;
					ASSERT_EQ(Vector3D (v_[i][0], v_[i][2]), robot->GetTargetPosition() );
					ASSERT_EQ(robot->GetCurIndex(), i);
					robot->IncrTarget();
				}
	}

	TEST_F(Robottest, get_distance_traveled) {
		ASSERT_EQ(robot->GetDistanceTraveled(), 0);
	}
}
