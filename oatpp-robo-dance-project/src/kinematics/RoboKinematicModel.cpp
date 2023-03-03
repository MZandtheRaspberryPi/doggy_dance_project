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

Matrix4d getTransformMatrix4d(double x_rotation, double y_rotation,
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

std::vector<Joint> RoboModel::getEndEffectors() { return end_effectors_; }

void RoboModel::setEndEffectors(const std::vector<Joint> &joints) {
  end_effectors_ = joints;
}

void RoboModel::setLinks(const std::vector<Link> &links) { links_ = links; }

std::vector<Link> RoboModel::getLinks() { return links_; }

void RoboModel::setBodyLocation(const Vector3d &location, bool recalc) {
  body_location_ = location;
  if (recalc) {
    Vector3d rotation = getBodyRotation();
    body_transform_matrix_ =
        getTransformMatrix4d(location[0], location[1], location[2], rotation[0],
                             rotation[1], rotation[2]);
    recalcJointsAndLinks();
  }
}

void RoboModel::setBodyTransform(const Matrix4d &transform) {
  body_transform_matrix_ = transform;
}

void RoboModel::setBodyRotation(const Vector3d &rotation, bool recalc) {
  Vector3d location = getBodyLocation();
  if (recalc) {

    body_rotation_ = rotation;
    body_transform_matrix_ =
        getTransformMatrix4d(location[0], location[1], location[2], rotation[0],
                             rotation[1], rotation[2]);
    recalcJointsAndLinks();
  }
}

const float RoboDog::l1 = 0.1;
const float RoboDog::l2 = 0.4;
const float RoboDog::l3 = 0.4;

const float RoboDog::body_length = 1;
const float RoboDog::body_width = 0.4;

void RoboDog::recalcJointsAndLinks() {
  std::vector<Link> links;
  std::vector<Joint> joints;
  std::vector<Joint> end_effectors;

  Vector3d rotation = getBodyRotation();
  Vector3d location = getBodyLocation();
  Matrix4d transform_matrix =
      getTransformMatrix4d(location[0], location[1], location[2], rotation[0],
                           rotation[1], rotation[2]);

  setBodyTransform(transform_matrix);

  // do body first

  Matrix4d front_left_matrix =
      transform_matrix *
      (getYRotationMatrix(-M_PI / 2) + Matrix4d{{0, 0, 0, body_length / 2},
                                                {0, 0, 0, 0},
                                                {0, 0, 0, -body_width / 2},
                                                {0, 0, 0, 0}});

  Matrix4d front_right_matrix =
      transform_matrix *
      (getYRotationMatrix(M_PI / 2) + Matrix4d{{0, 0, 0, body_length / 2},
                                               {0, 0, 0, 0},
                                               {0, 0, 0, body_width / 2},
                                               {0, 0, 0, 0}});

  Matrix4d back_right_matrix =
      transform_matrix *
      (getYRotationMatrix(M_PI / 2) + Matrix4d{{0, 0, 0, -body_length / 2},
                                               {0, 0, 0, 0},
                                               {0, 0, 0, body_width / 2},
                                               {0, 0, 0, 0}});

  Matrix4d back_left_matrix =
      transform_matrix *
      (getYRotationMatrix(-M_PI / 2) + Matrix4d{{0, 0, 0, -body_length / 2},
                                                {0, 0, 0, 0},
                                                {0, 0, 0, -body_width / 2},
                                                {0, 0, 0, 0}});

  Eigen::Vector3d link1_starting_coordinate = {front_left_matrix(0, 3),
                                               front_left_matrix(1, 3),
                                               front_left_matrix(2, 3)};
  Eigen::Vector3d link1_ending_coordinate = {front_right_matrix(0, 3),
                                             front_right_matrix(1, 3),
                                             front_right_matrix(2, 3)};

  Link link1{1, "body_front", link1_starting_coordinate,
             link1_ending_coordinate};

  Eigen::Vector3d link2_starting_coordinate = {front_right_matrix(0, 3),
                                               front_right_matrix(1, 3),
                                               front_right_matrix(2, 3)};
  Eigen::Vector3d link2_ending_coordinate = {back_right_matrix(0, 3),
                                             back_right_matrix(1, 3),
                                             back_right_matrix(2, 3)};

  Link link2{2, "body_right", link2_starting_coordinate,
             link2_ending_coordinate};

  Eigen::Vector3d link3_starting_coordinate = {back_right_matrix(0, 3),
                                               back_right_matrix(1, 3),
                                               back_right_matrix(2, 3)};
  Eigen::Vector3d link3_ending_coordinate = {
      back_left_matrix(0, 3), back_left_matrix(1, 3), back_left_matrix(2, 3)};

  Link link3{3, "body_back", link3_starting_coordinate,
             link3_ending_coordinate};

  Eigen::Vector3d link4_starting_coordinate = {
      back_left_matrix(0, 3), back_left_matrix(1, 3), back_left_matrix(2, 3)};
  Eigen::Vector3d link4_ending_coordinate = {front_left_matrix(0, 3),
                                             front_left_matrix(1, 3),
                                             front_left_matrix(2, 3)};

  Link link4{4, "body_left", link4_starting_coordinate,
             link4_ending_coordinate};

  links.push_back(link1);
  links.push_back(link2);
  links.push_back(link3);
  links.push_back(link4);

  Joint joint1{1,
               "front_left_shoulder",
               link1_starting_coordinate,
               JointType::ROTATING,
               -2 * M_PI,
               2 * M_PI};
  Joint joint2{2,
               "front_right_shoulder",
               link2_starting_coordinate,
               JointType::ROTATING,
               -2 * M_PI,
               2 * M_PI};
  Joint joint3{3,
               "back_right_shoulder",
               link3_starting_coordinate,
               JointType::ROTATING,
               -2 * M_PI,
               2 * M_PI};
  Joint joint4{4,
               "back_left_shoulder",
               link4_starting_coordinate,
               JointType::ROTATING,
               -2 * M_PI,
               2 * M_PI};
  joints.push_back(joint1);
  joints.push_back(joint2);
  joints.push_back(joint3);
  joints.push_back(joint4);

  // orer here should be same as initial joints order so that we can index and
  // find starting location easily, by looking at index 0 in the joints array
  // for index 0 in the leg_matrix_vect
  std::vector<std::string> joint_link_names = {"legfl_", "legfr_", "legbr_",
                                               "legbl_"};
  std::vector<Matrix4d> leg_matrix_vect = {front_left_matrix,
                                           front_right_matrix,
                                           back_right_matrix, back_left_matrix};
  int theta1, theta2, theta3;
  theta1 = theta2 = theta3 = 0;
  theta2 = -M_PI / 8;
  theta3 = -M_PI / 4;
  int joint_counter, link_counter;
  joint_counter = link_counter = 5;
  for (int i = 0; i < leg_matrix_vect.size(); i++) {
    const Matrix4d &base_to_leg_matrix = leg_matrix_vect[i];
    const std::string &joint_link_name = joint_link_names[i];
    // here t01 indicates matrix to transform from 0 to 1 joint
    Matrix4d t01{{cos(theta1), -sin(theta1), 0, -l1 * cos(theta1)},
                 {sin(theta1), cos(theta1), 0, -l1 * sin(theta1)},
                 {1, 0, 0, 0},
                 {0, 0, 0, 1}};
    Matrix4d intermediate_matrix = base_to_leg_matrix * t01;
    Eigen::Vector3d elbow_joint_coordinates = {intermediate_matrix(0, 3),
                                               intermediate_matrix(1, 3),
                                               intermediate_matrix(2, 3)};

    Joint elbow_joint{joint_counter,
                      joint_link_name + "elbow_joint",
                      elbow_joint_coordinates,
                      JointType::ROTATING,
                      -2 * M_PI,
                      2 * M_PI};
    joint_counter++;
    Link shoulder_to_elbow_link{link_counter,
                                joint_link_name + "shoulder_to_elbow",
                                joints[i].location, elbow_joint_coordinates};
    link_counter++;
    joints.push_back(elbow_joint);
    links.push_back(shoulder_to_elbow_link);

    Matrix4d t12{{0, 0, -1, 0}, {-1, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

    intermediate_matrix = intermediate_matrix * t12;

    Matrix4d t23{{cos(theta2), -sin(theta2), 0, l2 * cos(theta2)},
                 {sin(theta2), cos(theta2), 0, l2 * sin(theta2)},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}};
    intermediate_matrix = intermediate_matrix * t23;

    Eigen::Vector3d wrist_joint_coordinates = {intermediate_matrix(0, 3),
                                               intermediate_matrix(1, 3),
                                               intermediate_matrix(2, 3)};

    Joint wrist_joint{joint_counter,
                      joint_link_name + "wrist_joint",
                      wrist_joint_coordinates,
                      JointType::ROTATING,
                      -2 * M_PI,
                      2 * M_PI};
    joint_counter++;
    Link elbow_to_wrist_joint_link{
        link_counter, joint_link_name + "elbow_to_wrist", elbow_joint.location,
        wrist_joint_coordinates};
    link_counter++;
    joints.push_back(wrist_joint);
    links.push_back(elbow_to_wrist_joint_link);
    Matrix4d t34{{cos(theta3), -sin(theta3), 0, l3 * cos(theta3)},
                 {sin(theta3), cos(theta3), 0, l3 * sin(theta3)},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}};

    intermediate_matrix = intermediate_matrix * t34;

    Eigen::Vector3d end_effector_coordinates = {intermediate_matrix(0, 3),
                                                intermediate_matrix(1, 3),
                                                intermediate_matrix(2, 3)};

    Joint end_effector_joint{joint_counter,
                             joint_link_name + "end_effector",
                             end_effector_coordinates,
                             JointType::FIXED,
                             0,
                             0};
    joint_counter++;
    Link wrist_to_end_effector_link{
        link_counter, joint_link_name + "wrist_to_end_effector",
        wrist_joint.location, end_effector_coordinates};
    link_counter++;
    end_effectors.push_back(end_effector_joint);
    links.push_back(wrist_to_end_effector_link);
  }

  setLinks(links);
  setJoints(joints);
  setEndEffectors(end_effectors);
}

Vector3d RoboModel::getBodyLocation() { return body_location_; }
Vector3d RoboModel::getBodyRotation() { return body_rotation_; }
Matrix4d RoboModel::getBodyTransform() { return body_transform_matrix_; }

RoboDog::RoboDog(const int &id, const std::string &name,
                 const Eigen::Vector3d &starting_rotation,
                 const Eigen::Vector3d &starting_location)
    : RoboModel(id, name) {
  setBodyLocation(starting_location, false);
  setBodyRotation(starting_rotation, false);
  recalcJointsAndLinks();
}
// setLinks(links);