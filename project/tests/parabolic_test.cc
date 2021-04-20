#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <vector>
#include <iostream>
#include "Customer.h"
#include "Vector3D.h"
#include "IStrategy.h"
#include "Parabolic.h"

namespace csci3081 {
    using entity_project::IEntity;
    class Parabolic_test : public ::testing::Test {
        protected:
        virtual void SetUp() {
            strategy = new Parabolic();
        }
        virtual void TearDown() {}
        IStrategy *strategy;
    };

    TEST_F(Parabolic_test,parabolic_path) {
        std::vector<float> source = {0,0,0};
        std::vector<float> destination = {100,0,150};
        std::vector<std::vector<float>> path = strategy->GetPath(source, destination);
		Vector3D vo (source);
		Vector3D ve (destination);
		Vector3D vm = ((vo+ve)*0.5);
		double t = 30.0; // 8.0
		// for loop to have maybe 10 points
		// 0 to 1 in discreet increments
		Vector3D vt = ((ve-vo)*(1.0/t));
		Vector3D v;
		double offset = 20.0;
        int i;
		for (i = 0; i < t; i++) {
			v = vo+vt*i;
            double y = 1-pow( (v.DistanceBetween(vm)), 2)/pow( vo.DistanceBetween(vm), 2);
            double j = 150.0; 
            y = y*j;
            Vector3D temp (v[0], v[1]+y+offset, v[2]);
            std::vector<float> temp_vector = Vector3D::ConvertToVector(temp);
            EXPECT_EQ(path[i], temp_vector);
        }
        std::vector<float> vert = {float(ve[0]), float(ve[1]+offset), float(ve[2])};
        EXPECT_EQ(path[i], vert);
        EXPECT_EQ(path[i+1],destination);
    }
}