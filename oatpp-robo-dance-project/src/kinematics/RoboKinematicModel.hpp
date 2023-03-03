#include <iostream>
#include <math.h>
#include <string>
#include <unordered_map>
#include <vector>

#include <Eigen/Dense>

using namespace Eigen;

enum JointType { FIXED, ROTATING, PRISMATIC };

struct Joint {

  int number;
  std::string name;
  Eigen::Vector3d location;
  JointType joint_type;
  float current_angle_radians;
  float min_angle_radians;
  float max_angle_radians;
};

struct Link {

  int number;
  std::string name;
  Eigen::Vector3d start_location;
  Eigen::Vector3d end_location;
};

struct Robomodel {
  int id;
  std::string name;
  std::vector<Link> links;
  std::vector<Joint> joints;
  std::vector<Joint> end_effectors;
};

Matrix4d getXRotationMatrix4d(double x_rotation);
Matrix4d getYRotationMatrix4d(double y_rotation);
Matrix4d getZRotationMatrix4d(double z_rotation);
Matrix4d getRotationMatrix4d(double x_rotation, double y_rotation,
                             double z_rotation);

Matrix4d getTranslationMatrix4d(double x_translation, double y_translation,
                                double z_translation);

Matrix4d getTransformMatrix4d(double x_translation, double y_translation,
                              double z_translation, double x_rotation,
                              double y_rotation, double z_rotation);

Vector3d getCoordinateFromTransformMatrix(const Matrix4d &matrix);

class RoboModel {
public:
  static Robomodel getForwardKinematics(
      const Vector3d &body_location, const Vector3d &body_rotation,
      const std::unordered_map<int, float> &joint_angle_mapping);
  static std::vector<Joint> getZeroJoints(const Vector3d &body_location,
                                          const Vector3d &body_rotation);

public:
  int id;
  std::string name;

  int num_joints;
  int num_links;
  int num_end_effectors;
};

class RoboDog : public RoboModel {
public:
  static Robomodel getForwardKinematics(
      const Vector3d &body_location, const Vector3d &body_rotation,
      const std::unordered_map<int, float> &joint_angle_mapping);
  const static int id;
  const static std::string name;
  const static int num_joints;
  const static int num_links;
  const static int num_end_effectors;

protected:
  static std::vector<Link> getLinksFromJoints(
      const std::unordered_map<std::string, Matrix4d>
          &shoulder_transform_matrices,
      const std::unordered_map<std::string, Joint> &joints,
      const std::unordered_map<std::string, Joint> &end_effectors);

  static std::unordered_map<std::string, Matrix4d>
  getBaseToShoulderTransforms(const Vector3d &body_location,
                              const Vector3d &body_rotation);

  static std::unordered_map<std::string, Joint>
  getJointsForLeg(const Matrix4d &base_to_leg_matrix,
                  const std::string &leg_prefix, const float &theta1,
                  const float &theta2, const float &theta3);

  static std::vector<Joint> getZeroJoints(const Vector3d &body_location,
                                          const Vector3d &body_rotation);

private:
  const static float l1;
  const static float l2;
  const static float l3;

  const static float body_length;
  const static float body_width;

  const static std::string front_left_leg_prefix;
  const static std::string front_right_leg_prefix;
  const static std::string back_left_leg_prefix;
  const static std::string back_right_leg_prefix;
  const static std::string body_prefix;

  const static std::string shoulder_str;
  const static std::string elbow_str;
  const static std::string wrist_str;
  const static std::string end_effector_str;
  const static std::unordered_map<std::string, int> joint_str_to_id_mapping;
};