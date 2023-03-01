#include <iostream>
#include <math.h>
#include <string>
#include <vector>

#include <Eigen/Dense>

using namespace Eigen;

struct Joint {

  int number;
  std::string name;
  Eigen::Vector3d location;
};

struct Link {

  int number;
  std::string name;
  Eigen::Vector3d start_location;
  Eigen::Vector3d end_location;
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

private:
  int id_;
  std::string name_;
  std::vector<Link> links_;
  std::vector<Joint> joints_;
  std::vector<Joint> end_effectors_;
};

class RoboDog : public RoboModel {
public:
  RoboDog(const int &id, const std::string &name,
          const Eigen::Vector3d &starting_rotation,
          const Eigen::Vector3d &starting_location);
  void setRoboPosition(const float &x, const float &y, const float &z,
                       const float &roll, const float &pitch, const float &yaw);

private:
  float l1_ = 0.1;
  float l2_ = 0.4;
  float l3_ = 0.4;

  float body_length_ = 1;
  float body_width_ = 0.4;
};