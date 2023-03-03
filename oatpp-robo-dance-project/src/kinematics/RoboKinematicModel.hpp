#include <iostream>
#include <math.h>
#include <string>
#include <vector>

#include <Eigen/Dense>

using namespace Eigen;

enum JointType { FIXED, ROTATING, PRISMATIC };

struct Joint {

  int number;
  std::string name;
  Eigen::Vector3d location;
  JointType joint_type;
  float min;
  float max;
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

class RoboModel {
public:
  RoboModel(const int &id, const std::string &name);

  std::vector<Joint> getJoints();
  std::vector<Link> getLinks();
  std::vector<Joint> getEndEffectors();
  Vector3d getBodyLocation();
  Vector3d getBodyRotation();
  Matrix4d getBodyTransform();

  /*
  virtual void setRoboPosition(const float &x, const float &y, const float &z,
                               const float &roll, const float &pitch,
                               const float &yaw) = 0;
  */

  std::string getName();
  int getId();

protected:
  void setEndEffectors(const std::vector<Joint> &joints);
  void setJoints(const std::vector<Joint> &joints);
  void setLinks(const std::vector<Link> &links);
  void setBodyLocation(const Vector3d &location, bool recalc = true);
  void setBodyRotation(const Vector3d &rotation, bool recalc = true);
  void setBodyTransform(const Matrix4d &transform);
  virtual void recalcJointsAndLinks() = 0;

private:
  int id_;
  std::string name_;
  std::vector<Link> links_;
  std::vector<Joint> joints_;
  std::vector<Joint> end_effectors_;
  Matrix4d body_transform_matrix_;
  Vector3d body_location_;
  Vector3d body_rotation_;
};

class RoboDog : public RoboModel {
public:
  RoboDog(const int &id, const std::string &name,
          const Eigen::Vector3d &starting_rotation,
          const Eigen::Vector3d &starting_location);
  void setRoboPosition(const float &x, const float &y, const float &z,
                       const float &roll, const float &pitch, const float &yaw);

protected:
  void recalcJointsAndLinks();

private:
  const static float l1;
  const static float l2;
  const static float l3;

  const static float body_length;
  const static float body_width;
};