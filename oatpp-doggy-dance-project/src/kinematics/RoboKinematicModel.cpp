#include "RoboKinematicModel.hpp"

Matrix4d getXRotationMatrix(double x_rotation) {
  Matrix4d m{{1, 0, 0, 0},
             {0, cos(x_rotation), -sin(x_rotation), 0},
             {0, sin(x_rotation), cos(x_rotation), 0},
             {0, 0, 0, 1}};
  return m;
}

Matrix4d getYRotationMatrix(double y_rotation) {
  Matrix4d m{{cos(y_rotation), 0, sin(y_rotation), 0},
             {0, 1, 0, 0},
             {-sin(y_rotation), 0, cos(y_rotation), 0},
             {0, 0, 0, 1}};
  return m;
}

Matrix4d getZRotationMatrix(double z_rotation) {
  Matrix4d m{{cos(z_rotation), -sin(z_rotation), 0, 0},
             {sin(z_rotation), cos(z_rotation), 0, 0},
             {0, 0, 1, 0},
             {0, 0, 0, 1}};
  return m;
}

Matrix4d getRotationMatrix(double x_rotation, double y_rotation,
                           double z_rotation) {
  Matrix4d x_m = getXRotationMatrix(x_rotation);
  Matrix4d y_m = getYRotationMatrix(y_rotation);
  Matrix4d z_m = getZRotationMatrix(z_rotation);
  return x_m * y_m * z_m;
}

Matrix4d getTranslationMatrix(double x_translation, double y_translation,
                              double z_translation) {
  Matrix4d m{{1, 0, 0, x_translation},
             {0, 1, 0, y_translation},
             {0, 0, 1, z_translation},
             {0, 0, 0, 1}};
  return m;
}

Matrix4d getTransformMatrix(double x_rotation, double y_rotation,
                            double z_rotation, double x_translation,
                            double y_translation, double z_translation) {
  Matrix4d rotation_m = getRotationMatrix(x_rotation, y_rotation, z_rotation);
  Matrix4d translation_m =
      getTranslationMatrix(x_translation, y_translation, z_translation);
  return rotation_m * translation_m;
}

RoboModel::RoboModel(const int &id, const std::string &name)
    : id_(id), name_(name) {}

void RoboModel::setJoints(const std::vector<Joint> &joints) {
  joints_ = joints;
}

int RoboModel::getId() { return id_; }
std::string RoboModel::getName() { return name_; }

std::vector<Joint> RoboModel::getJoints() { return joints_; }

void RoboModel::setLinks(const std::vector<Link> &links) { links_ = links; }

std::vector<Link> RoboModel::getLinks() { return links_; }

RoboDog::RoboDog(const int &id, const std::string &name,
                 const Eigen::Vector3d &starting_rotation,
                 const Eigen::Vector3d &starting_location)
    : RoboModel(id, name) {

  std::vector<Link> links;
  std::vector<Joint> joints;

  // do body first
  Matrix4d transform_matrix = getTransformMatrix(
      starting_rotation[0], starting_rotation[1], starting_rotation[2],
      starting_location[0], starting_location[1], starting_location[2]);

  Matrix4d front_left_matrix =
      transform_matrix *
      (getYRotationMatrix(-M_PI / 2) + Matrix4d{{0, 0, 0, body_length_ / 2},
                                                {0, 0, 0, 0},
                                                {0, 0, 0, -body_width_ / 2},
                                                {0, 0, 0, 0}});

  Matrix4d front_right_matrix =
      transform_matrix *
      (getYRotationMatrix(M_PI / 2) + Matrix4d{{0, 0, 0, body_length_ / 2},
                                               {0, 0, 0, 0},
                                               {0, 0, 0, body_width_ / 2},
                                               {0, 0, 0, 0}});

  Matrix4d back_right_matrix =
      transform_matrix *
      (getYRotationMatrix(M_PI / 2) + Matrix4d{{0, 0, 0, -body_length_ / 2},
                                               {0, 0, 0, 0},
                                               {0, 0, 0, body_width_ / 2},
                                               {0, 0, 0, 0}});

  Matrix4d back_left_matrix =
      transform_matrix *
      (getYRotationMatrix(-M_PI) + Matrix4d{{0, 0, 0, -body_length_ / 2},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, -body_width_ / 2},
                                            {0, 0, 0, 0}});

  Eigen::Vector3d link1_starting_coordinate = {front_left_matrix(0, 3),
                                               front_left_matrix(1, 3),
                                               front_left_matrix(2, 3)};
  Eigen::Vector3d link1_ending_coordinate = {front_right_matrix(0, 3),
                                             front_right_matrix(1, 3),
                                             front_right_matrix(2, 3)};

  Link link1{1, "front_body", link1_starting_coordinate,
             link1_ending_coordinate};

  Eigen::Vector3d link2_starting_coordinate = {front_right_matrix(0, 3),
                                               front_right_matrix(1, 3),
                                               front_right_matrix(2, 3)};
  Eigen::Vector3d link2_ending_coordinate = {back_right_matrix(0, 3),
                                             back_right_matrix(1, 3),
                                             back_right_matrix(2, 3)};

  Link link2{2, "right_body", link2_starting_coordinate,
             link2_ending_coordinate};

  Eigen::Vector3d link3_starting_coordinate = {back_right_matrix(0, 3),
                                               back_right_matrix(1, 3),
                                               back_right_matrix(2, 3)};
  Eigen::Vector3d link3_ending_coordinate = {
      back_left_matrix(0, 3), back_left_matrix(1, 3), back_left_matrix(2, 3)};

  Link link3{3, "back_body", link3_starting_coordinate,
             link3_ending_coordinate};

  Eigen::Vector3d link4_starting_coordinate = {
      back_left_matrix(0, 3), back_left_matrix(1, 3), back_left_matrix(2, 3)};
  Eigen::Vector3d link4_ending_coordinate = {front_left_matrix(0, 3),
                                             front_left_matrix(1, 3),
                                             front_left_matrix(2, 3)};

  Link link4{4, "left_body", link4_starting_coordinate,
             link4_ending_coordinate};

  links.push_back(link1);
  links.push_back(link2);
  links.push_back(link3);
  links.push_back(link4);
  setLinks(links);

  Joint joint1{1, "front_left_shoulder", link1_starting_coordinate};
  Joint joint2{2, "front_right_shoulder", link2_starting_coordinate};
  Joint joint3{3, "back_right_shoulder", link3_starting_coordinate};
  Joint joint4{4, "back_left_shoulder", link4_starting_coordinate};
  joints.push_back(joint1);
  joints.push_back(joint2);
  joints.push_back(joint3);
  joints.push_back(joint4);
  setJoints(joints);
}
// setLinks(links);