#include "kinematics/RoboKinematicModel.hpp"

#include "gtest/gtest.h"

namespace test_kinematics {

// Tests that Foo does Xyz.
TEST(KinematicsTest, ForwardKinematics1) {
  // this test sets up a forward configuration where the end effectrs for the
  // legs specified should all be at 0, -0.65, 0 relative to the shoulder
  double pitch = -15 * M_PI / 180;
  double roll = 0;
  double yaw = 0;

  std::unordered_map<int, float> joint_angle_mapping;

  joint_angle_mapping[RoboDog::joint_str_to_id_mapping.at(
      RoboDog::back_left_leg_prefix + RoboDog::shoulder_str)] =
      7.5883 * M_PI / 180;
  joint_angle_mapping[RoboDog::joint_str_to_id_mapping.at(
      RoboDog::back_left_leg_prefix + RoboDog::elbow_str)] =
      28.7493 * M_PI / 180;
  joint_angle_mapping[RoboDog::joint_str_to_id_mapping.at(
      RoboDog::back_left_leg_prefix + RoboDog::wrist_str)] =
      -29.7695 * M_PI / 180;

  joint_angle_mapping[RoboDog::joint_str_to_id_mapping.at(
      RoboDog::front_right_leg_prefix + RoboDog::shoulder_str)] =
      11.5735 * M_PI / 180;
  joint_angle_mapping[RoboDog::joint_str_to_id_mapping.at(
      RoboDog::front_right_leg_prefix + RoboDog::elbow_str)] =
      33.0804 * M_PI / 180;
  joint_angle_mapping[RoboDog::joint_str_to_id_mapping.at(
      RoboDog::front_right_leg_prefix + RoboDog::wrist_str)] =
      -100.5692 * M_PI / 180;

  Vector3d robo_location = {0, 0, 0};
  Vector3d robo_orientation = {roll, yaw, pitch};

  Robomodel result_model = RoboDog::getForwardKinematics(
      robo_location, robo_orientation, joint_angle_mapping);

  for (int i = 0; i < result_model.end_effectors.size(); i++) {
    if (result_model.end_effectors[i].name ==
            RoboDog::back_left_leg_prefix + RoboDog::end_effector_str ||
        result_model.end_effectors[i].name ==
            RoboDog::front_right_leg_prefix + RoboDog::end_effector_str) {
      EXPECT_NEAR(result_model.end_effectors[i].location_shoulder[0], 0,
                  0.0001);
      EXPECT_NEAR(result_model.end_effectors[i].location_shoulder[1], -0.65,
                  0.0001);
      EXPECT_NEAR(result_model.end_effectors[i].location_shoulder[2], 0,
                  0.0001);
    }
  }
}

} // namespace test_kinematics

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
