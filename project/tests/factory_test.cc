#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"


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
  IEntity* entity = system->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(entity->GetDetails()).serialize(), picojson::value(obj).serialize());

}
}  // namespace csci3081
