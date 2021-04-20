#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <vector>
#include <iostream>
#include "Customer.h"
#include "Vector3D.h"
#include "IStrategy.h"
#include "Beeline.h"

namespace csci3081 {
    using entity_project::IEntity;
    class Beeline_test: public ::testing::Test {
        protected:
        virtual void SetUp() {
            strategy = new Beeline();
        }
        virtual void TearDown() {}
        IStrategy *strategy;
    };

    TEST_F(Beeline_test, beeline_path) {
        std::vector<std::vector<float>> path = strategy->GetPath({0,0,0},{50,100,75});
        std::vector<float> point_1 = {0,200,0};
        std::vector<float> point_2 = {50,300,75};
        std::vector<float> point_3 = {50,100,75};
        EXPECT_EQ(path.size(),3);
        EXPECT_EQ(path[0],point_1);
        EXPECT_EQ(path[1],point_2);
        EXPECT_EQ(path[2],point_3);
    }
}