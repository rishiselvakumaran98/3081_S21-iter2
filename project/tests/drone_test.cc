#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <vector>
#include <iostream>
#include "Customer.h"
#include "Vector3D.h"
#include "drone.h"

namespace csci3081 {

using entity_project::IEntity;

class DroneTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
	  
	  object = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(object, "type", "customer");
      JsonHelper::AddStringToJsonObject(object, "name", "testCustomer");
      JsonHelper::AddFloatToJsonObject(object, "radius", 100);
      JsonHelper::AddFloatToJsonObject(object, "speed", 0);
      JsonHelper::AddStdFloatVectorToJsonObject(object, "position", {5, 0, 0});
      JsonHelper::AddStdFloatVectorToJsonObject(object, "direction", {100, 650, 0});
	    drone  = new Drone(object);
		
		float sp = 200.0;
		Battery* power_source =  new Battery();
		droneConstr = new Drone(sp, power_source, object);
		
		std::vector<float> pos;
		std::vector<float> dir;
		
		pos.push_back(50);
		pos.push_back(0);
		pos.push_back(0);

		dir.push_back(0);
		dir.push_back(20);
		dir.push_back(30);

		drone2 = new Drone(pos, dir, object);
}

  virtual void TearDown() {}
  Drone* drone;
  Drone* droneConstr;
  Drone* drone2;
  picojson::object object;
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(DroneTest, default_constr_tests) {
	
				ASSERT_NE(nullptr,  drone);
	}//end function

	TEST_F(DroneTest, pos_dir_constr_tests) {
		std::vector<float> v;
		v.push_back(50);
		v.push_back(0);
		v.push_back(0);

		ASSERT_EQ(v, drone2->GetPosition());
		std::vector<float> d;
		d.push_back(0);
		d.push_back(20);
		d.push_back(30);
		ASSERT_EQ(d, drone2->GetDirection());

		ASSERT_NE(nullptr, drone2);
	} //close test for the constructor with a direction and a position vector floats
	

	TEST_F(DroneTest, pick_order) {
		drone->Pick_order();
		ASSERT_EQ(0, drone->GetCurIndex() );
		ASSERT_EQ(true, drone->has_picked_up_getter() );
		ASSERT_NE(drone->GetCurRout(), nullptr);
	}

	TEST_F(DroneTest, drop_order_test) {

		Package pack(object);
		
		drone->SetPackage(&pack);
		drone->Drop_order();
		ASSERT_EQ(drone->has_picked_up_getter(), false);
		ASSERT_EQ(0, drone->GetCurIndex() );
		ASSERT_EQ(0, drone->GetDistanceTraveled() );
				ASSERT_EQ(Vector3D(0, -1000, 0),  pack.GetVPos() );
	}

	TEST_F(DroneTest, within_range_test) {
		
		std::vector<float> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		
		std::vector<std::vector<float>> v_;
		v_.push_back(v);

		drone->SetDroneToPack(v_);
				drone->SetCurrRout("pack");
		ASSERT_EQ(Vector3D(1, 2, 3), drone->GetTargetPosition() );
	}

	TEST_F(DroneTest, Incr_target_test) {
		std::vector<float> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		
		std::vector<float> v2;
		v2.push_back(4);
		v2.push_back(5);
		v2.push_back(6);

		std::vector<std::vector<float>> v_;
		v_.push_back(v);
		v_.push_back(v2);
		
		drone->SetDroneToPack(v_);
				drone->SetCurrRout("pack");
				drone->IncrTarget();
		ASSERT_EQ(Vector3D(4, 5, 6), drone->GetTargetPosition() );
	}

	TEST_F(DroneTest, get_package_test) {
		Package pack(object);
		drone->SetPackage(&pack);
		ASSERT_NE(drone->GetPackage(), nullptr);
		ASSERT_EQ(drone->GetPackage(), &pack);
	}

	TEST_F(DroneTest, set_package_test) {
		Package pack(object);
		drone->SetPackage(&pack);
		ASSERT_EQ(&pack, drone->GetPackage());
	}

	TEST_F(DroneTest, set_drone_to_pack_test) {
		std::vector<float> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		
		std::vector<float> v2;
		v2.push_back(4);
		v2.push_back(5);
		v2.push_back(6);

		std::vector<std::vector<float>> v_;
		v_.push_back(v);
		v_.push_back(v2);
		
		drone->SetDroneToPack(v_);
				drone->SetCurrRout("pack");
//				Vector3D curR = Vector3D (drone->GetCurrRout() );
				for (int i = 0; i < v_.size(); i++) {
					ASSERT_EQ(Vector3D (v_[i]), drone->GetTargetPosition() );
					drone->IncrTarget();
				}
	}


	TEST_F(DroneTest, set_pack_to_customer_test) {
		std::vector<float> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		
		std::vector<float> v2;
		v2.push_back(4);
		v2.push_back(5);
		v2.push_back(6);

		std::vector<std::vector<float>> v_;
		v_.push_back(v);
		v_.push_back(v2);
		
		drone->SetPackToCustomer(v_);
				drone->SetCurrRout("customer");
//				Vector3D curR = Vector3D (drone->GetCurrRout() );
				for (int i = 0; i < v_.size(); i++) {
					ASSERT_EQ(Vector3D (v_[i]), drone->GetTargetPosition() );
					drone->IncrTarget();
				}

	}

	TEST_F(DroneTest, Within_range_test) {
		Vector3D v(1000, 20, 30);
		
		ASSERT_EQ(false, drone->Within_range(v));
		
			Vector3D v1 (6, 0, 0);
		ASSERT_EQ(true, drone->Within_range(v1) );
	}

	TEST_F(DroneTest, get_speed_test) {
		ASSERT_EQ(0, drone->GetSpeed() );
	}

	TEST_F(DroneTest, has_picked_getter_test) {
		Package pack(object);
		drone->SetPackage(&pack);
		
		drone->Pick_order();
		ASSERT_EQ(true, drone->has_picked_up_getter());
		
		drone->Drop_order();
		ASSERT_EQ(false, drone->has_picked_up_getter() );
	}

	TEST_F(DroneTest, set_cur_rout_test) {
		Package pack(object);
		drone->SetPackage(&pack);
		drone->Pick_order();
		
		std::vector<float> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		
		std::vector<float> v2;
		v2.push_back(4);
		v2.push_back(5);
		v2.push_back(6);

		std::vector<std::vector<float>> v_;
		v_.push_back(v);
		v_.push_back(v2);
		
		drone->SetDroneToPack(v_);
				drone->SetCurrRout("pack");
//				Vector3D curR = Vector3D (drone->GetCurrRout() );
				for (int i = 0; i < v_.size(); i++) {
					ASSERT_EQ(Vector3D (v_[i]), drone->GetTargetPosition() );
					drone->IncrTarget();
				}
	
				drone->Drop_order();
		std::vector<float> v10;
		v10.push_back(10);
		v10.push_back(20);
		v10.push_back(30);
		
		std::vector<float> v20;
		v20.push_back(40);
		v20.push_back(50);
		v20.push_back(60);

		std::vector<std::vector<float>> v20_;
		v20_.push_back(v10);
		v20_.push_back(v20);
		
		drone->SetPackToCustomer(v20_);
				drone->SetCurrRout("customer");
//				Vector3D curR = Vector3D (drone->GetCurrRout() );
				for (int i = 0; i < v20_.size(); i++) {
					ASSERT_EQ(Vector3D (v20_[i]), drone->GetTargetPosition() );
					drone->IncrTarget();
				}
	}

	TEST_F(DroneTest, update_package_test) {
		Package pack(object);
		drone->SetPackage(&pack);
		drone->SetPosition(Vector3D (10, 20, 30));
		drone->Update_Package();
//		ASSERT_NE(drone->GetVPos(), pack.GetVPos() );
		ASSERT_EQ(Vector3D(5, 0, 0), pack.GetVPos() );
		
		drone->Pick_order();
		drone->Update_Package();
		ASSERT_EQ(Vector3D(10, 20, 30), pack.GetVPos() );
	}


	TEST_F(DroneTest, get_cur_index_test) {
		Package pack(object);
		drone->SetPackage(&pack);
		drone->Pick_order();
		
		std::vector<float> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		
		std::vector<float> v2;
		v2.push_back(4);
		v2.push_back(5);
		v2.push_back(6);

		std::vector<std::vector<float>> v_;
		v_.push_back(v);
		v_.push_back(v2);
		
		drone->SetDroneToPack(v_);
				drone->SetCurrRout("pack");
//				Vector3D curR = Vector3D (drone->GetCurrRout() );
				for (int i = 0; i < v_.size(); i++) {
					ASSERT_EQ(Vector3D (v_[i]), drone->GetTargetPosition() );
					ASSERT_EQ(drone->GetCurIndex(), i);
					drone->IncrTarget();
				}
		
		
	}

	TEST_F(DroneTest, cur_rout_getter_test) {
		Package pack(object);
		drone->SetPackage(&pack);
		drone->Pick_order();
		
		std::vector<float> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		
		std::vector<float> v2;
		v2.push_back(4);
		v2.push_back(5);
		v2.push_back(6);

		std::vector<std::vector<float>> v_;
		v_.push_back(v);
		v_.push_back(v2);
		
		drone->SetDroneToPack(v_);
				drone->SetCurrRout("pack");
				
				std::vector<std::vector<float>> rout = *(drone->GetCurRout() );
				for (int i = 0; i < v_.size(); i++) {
					ASSERT_EQ(Vector3D(v_[i]),Vector3D (rout[i]));
				}
	
				drone->Drop_order();
		std::vector<float> v10;
		v10.push_back(10);
		v10.push_back(20);
		v10.push_back(30);
		
		std::vector<float> v20;
		v20.push_back(40);
		v20.push_back(50);
		v20.push_back(60);

		std::vector<std::vector<float>> v20_;
		v20_.push_back(v10);
		v20_.push_back(v20);
		std::vector<std::vector<float>> rout2;
		
		
		drone->SetPackToCustomer(v20_);
				drone->SetCurrRout("customer");
//				Vector3D curR = Vector3D (drone->GetCurrRout() );
				rout2 = *(drone->GetCurRout() );
				for (int i = 0; i < v20_.size(); i++) {
					ASSERT_EQ(Vector3D (rout2[i]), Vector3D ( v20_[i] ));
				}
	}

	TEST_F(DroneTest, get_distance_traveled) {
		ASSERT_EQ(drone->GetDistanceTraveled(), 0);
	}
		
	
//   	float GetDistanceTraveled() { return distance_traveled; }

//};// end class
} //close namespace

