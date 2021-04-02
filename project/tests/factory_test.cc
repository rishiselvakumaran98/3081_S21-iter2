#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "CompositeFactory.h"
#include "DroneFactory.h"
#include "PackageFactory.h"
#include "CustomerFactory.h"
#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class FactoryTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(FactoryTest, DroneCreated) {
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "drone");
  std::vector<float> position_to_add;
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  JsonHelper::AddStringToJsonObject(obj, "name", "nam");
  JsonHelper::AddFloatToJsonObject(obj, "radius", 10.0);
JsonHelper::AddFloatToJsonObject(obj, "speed", 100.0);
  IEntity* entity = system->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  system->AddEntity(entity);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[2], direction_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());
}

picojson::object make_pjs(std::string type_of_entity) {

    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", type_of_entity);
    std::vector<float> position_to_add;
    position_to_add.push_back(498.292);
    position_to_add.push_back(253.883);
    position_to_add.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    std::vector<float> direction_to_add;
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddStringToJsonObject(obj, "name", "nam");
    JsonHelper::AddFloatToJsonObject(obj, "radius", 10.0);
	JsonHelper::AddFloatToJsonObject(obj, "speed", 100.0);
	return obj;
}

TEST_F(FactoryTest, composite_test) {
	picojson::object drone1 = make_pjs("drone");
	picojson::object package1 = make_pjs("package");
	picojson::object customer1 = make_pjs("customer");
	CompositeFactory comp_fact;
	DroneFactory* dFact = new DroneFactory();
	PackageFactory* pFact = new PackageFactory();
	CustomerFactory* cFact = new CustomerFactory();

	comp_fact.AddFactory(dFact);
	comp_fact.AddFactory(pFact);
		comp_fact.AddFactory(cFact);
//	ASSERT_NE(comp_fact, nullptr);

	IEntity* d1 = comp_fact.CreateEntity(drone1);
	IEntity* p1 = comp_fact.CreateEntity(package1);
	IEntity* c1 = comp_fact.CreateEntity(customer1);
	
	ASSERT_NE(d1, nullptr);
	ASSERT_NE(p1, nullptr);
	ASSERT_NE(c1, nullptr);
}

TEST_F(FactoryTest, drone_fact_test) {
	picojson::object d1 = make_pjs("drone");
	DroneFactory dFact;
	IEntity* dTest1 = dFact.CreateEntity(d1);
	ASSERT_NE(dTest1, nullptr);
}


TEST_F(FactoryTest, package_fact_test) {
	picojson::object p1 = make_pjs("package");
	PackageFactory pFact;
	IEntity* pTest1 = pFact.CreateEntity(p1);
	ASSERT_NE(pTest1, nullptr);
}


TEST_F(FactoryTest, customer_fact_test) {
	picojson::object c1 = make_pjs("customer");
	CustomerFactory cFact;
	IEntity* cTest1 = cFact.CreateEntity(c1);
	ASSERT_NE(cTest1, nullptr);
}

}  // namespace csci3081
