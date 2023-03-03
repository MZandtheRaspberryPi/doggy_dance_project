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

Vector3d getCoordinateFromTransformMatrix(const Matrix4d &matrix) {
  Eigen::Vector3d coordinates = {matrix(0, 3), matrix(1, 3), matrix(2, 3)};
  return coordinates;
}

const float RoboDog::l1 = 0.1;
const float RoboDog::l2 = 0.4;
const float RoboDog::l3 = 0.4;

const float RoboDog::body_length = 1;
const float RoboDog::body_width = 0.4;

const int RoboDog::num_joints = 12;
const int RoboDog::num_links = 16;
const int RoboDog::num_end_effectors = 4;

const int RoboDog::id = 0;
const std::string RoboDog::name = "robo_dog";

const std::string RoboDog::front_left_leg_prefix = "legfl_";
const std::string RoboDog::front_right_leg_prefix = "legfr_";
const std::string RoboDog::back_left_leg_prefix = "legbr_";
const std::string RoboDog::back_right_leg_prefix = "legbl_";

const std::string RoboDog::body_prefix = "body_";

const std::string RoboDog::shoulder_str = "shoulder";
const std::string RoboDog::elbow_str = "elbow";
const std::string RoboDog::wrist_str = "wrist";
const std::string RoboDog::end_effector_str = "end_effector";

const std::unordered_map<std::string, int> RoboDog::joint_str_to_id_mapping = {
    {RoboDog::front_left_leg_prefix + RoboDog::shoulder_str, 1},
    {RoboDog::front_left_leg_prefix + RoboDog::elbow_str, 2},
    {RoboDog::front_left_leg_prefix + RoboDog::wrist_str, 3},
    {RoboDog::front_left_leg_prefix + RoboDog::end_effector_str, 4},
    {RoboDog::front_right_leg_prefix + RoboDog::shoulder_str, 5},
    {RoboDog::front_right_leg_prefix + RoboDog::elbow_str, 6},
    {RoboDog::front_right_leg_prefix + RoboDog::wrist_str, 7},
    {RoboDog::front_right_leg_prefix + RoboDog::end_effector_str, 8},
    {RoboDog::back_left_leg_prefix + RoboDog::shoulder_str, 9},
    {RoboDog::back_left_leg_prefix + RoboDog::elbow_str, 10},
    {RoboDog::back_left_leg_prefix + RoboDog::wrist_str, 11},
    {RoboDog::back_left_leg_prefix + RoboDog::end_effector_str, 12},
    {RoboDog::back_right_leg_prefix + RoboDog::shoulder_str, 13},
    {RoboDog::back_right_leg_prefix + RoboDog::elbow_str, 14},
    {RoboDog::back_right_leg_prefix + RoboDog::wrist_str, 15},
    {RoboDog::back_right_leg_prefix + RoboDog::end_effector_str, 16},
};

std::unordered_map<std::string, Matrix4d>
RoboDog::getBaseToShoulderTransforms(const Vector3d &body_location,
                                     const Vector3d &body_rotation) {
  Matrix4d transform_matrix = getTransformMatrix4d(
      body_location[0], body_location[1], body_location[2], body_rotation[0],
      body_rotation[1], body_rotation[2]);

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

  std::unordered_map<std::string, Matrix4d> shoulder_transform_map;
  shoulder_transform_map[front_left_leg_prefix] = front_left_matrix;
  shoulder_transform_map[front_right_leg_prefix] = front_right_matrix;
  shoulder_transform_map[back_left_leg_prefix] = back_right_matrix;
  shoulder_transform_map[back_right_leg_prefix] = back_left_matrix;

  return shoulder_transform_map;
}

std::unordered_map<std::string, Joint>
RoboDog::getJointsForLeg(const Matrix4d &base_to_leg_matrix,
                         const std::string &leg_prefix, const float &theta1,
                         const float &theta2, const float &theta3) {
  std::unordered_map<std::string, Joint> joints_map;

  std::string joint_name = leg_prefix + shoulder_str;
  int id = joint_str_to_id_mapping.at(joint_name);
  Joint shoulder_joint{id,
                       joint_name,
                       getCoordinateFromTransformMatrix(base_to_leg_matrix),
                       JointType::ROTATING,
                       theta1,
                       -2 * M_PI,
                       2 * M_PI};
  joints_map[joint_name] = shoulder_joint;

  // here t01 indicates matrix to transform from 0 to 1 joint
  Matrix4d t01{{cos(theta1), -sin(theta1), 0, -l1 * cos(theta1)},
               {sin(theta1), cos(theta1), 0, -l1 * sin(theta1)},
               {1, 0, 0, 0},
               {0, 0, 0, 1}};
  Matrix4d intermediate_matrix = base_to_leg_matrix * t01;

  joint_name = leg_prefix + elbow_str;
  id = joint_str_to_id_mapping.at(joint_name);
  Joint elbow_joint{id,
                    joint_name,
                    getCoordinateFromTransformMatrix(intermediate_matrix),
                    JointType::ROTATING,
                    theta2,
                    -2 * M_PI,
                    2 * M_PI};

  joints_map[joint_name] = elbow_joint;

  Matrix4d t12{{0, 0, -1, 0}, {-1, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

  intermediate_matrix = intermediate_matrix * t12;

  Matrix4d t23{{cos(theta2), -sin(theta2), 0, l2 * cos(theta2)},
               {sin(theta2), cos(theta2), 0, l2 * sin(theta2)},
               {0, 0, 1, 0},
               {0, 0, 0, 1}};
  intermediate_matrix = intermediate_matrix * t23;

  joint_name = leg_prefix + wrist_str;
  id = joint_str_to_id_mapping.at(joint_name);
  Joint wrist_joint{id,
                    joint_name,
                    getCoordinateFromTransformMatrix(intermediate_matrix),
                    JointType::ROTATING,
                    theta3,
                    -2 * M_PI,
                    2 * M_PI};
  joints_map[joint_name] = wrist_joint;

  Matrix4d t34{{cos(theta3), -sin(theta3), 0, l3 * cos(theta3)},
               {sin(theta3), cos(theta3), 0, l3 * sin(theta3)},
               {0, 0, 1, 0},
               {0, 0, 0, 1}};

  intermediate_matrix = intermediate_matrix * t34;

  joint_name = leg_prefix + end_effector_str;
  id = joint_str_to_id_mapping.at(joint_name);
  Joint end_effector_joint{
      id,
      joint_name,
      getCoordinateFromTransformMatrix(intermediate_matrix),
      JointType::FIXED,
      0,
      0,
      0};
  joints_map[joint_name] = end_effector_joint;

  return joints_map;
}

std::vector<Joint> RoboDog::getZeroJoints(const Vector3d &body_location,
                                          const Vector3d &body_rotation) {
  std::vector<Joint> joints;

  std::unordered_map<std::string, Matrix4d> shoulder_transform_matrices =
      getBaseToShoulderTransforms(body_location, body_rotation);

  std::vector<std::string> joint_link_names = {
      front_left_leg_prefix, front_right_leg_prefix, back_left_leg_prefix,
      back_right_leg_prefix};

  for (int i = 0; i < joint_link_names.size(); i++) {

    const std::string &joint_link_name = joint_link_names[i];

    const Matrix4d &base_matrix = shoulder_transform_matrices[joint_link_name];

    int theta1, theta2, theta3;
    theta1 = theta2 = theta3 = 0;

    std::unordered_map<std::string, Joint> leg_joints =
        getJointsForLeg(base_matrix, joint_link_name, theta1, theta2, theta3);

    joints.push_back(leg_joints[joint_link_name + shoulder_str]);
    joints.push_back(leg_joints[joint_link_name + elbow_str]);
    joints.push_back(leg_joints[joint_link_name + wrist_str]);
    joints.push_back(leg_joints[joint_link_name + end_effector_str]);
  }
  return joints;
}

std::vector<Link> RoboDog::getLinksFromJoints(
    const std::unordered_map<std::string, Matrix4d>
        &shoulder_transform_matrices,
    const std::unordered_map<std::string, Joint> &joints,
    const std::unordered_map<std::string, Joint> &end_effectors) {
  std::vector<Link> links;
  int link_id_counter = 1;
  // make body links first
  std::vector<std::string> joint_link_names = {
      front_left_leg_prefix, front_right_leg_prefix, back_left_leg_prefix,
      back_right_leg_prefix};
  for (int i = 0; i < joint_link_names.size(); i++) {
    const std::string &starting_joint_name = joint_link_names[i];
    const Matrix4d &starting_transform_matrix =
        shoulder_transform_matrices.at(starting_joint_name);

    const std::string &ending_joint_name = joint_link_names[(i + 1) % 4];
    const Matrix4d &ending_transform_matrix =
        shoulder_transform_matrices.at(ending_joint_name);

    Eigen::Vector3d link_starting_coordinates = {
        starting_transform_matrix(0, 3), starting_transform_matrix(1, 3),
        starting_transform_matrix(2, 3)};
    Eigen::Vector3d link_ending_coordinates = {ending_transform_matrix(0, 3),
                                               ending_transform_matrix(1, 3),
                                               ending_transform_matrix(2, 3)};

    Link link{link_id_counter, body_prefix + std::to_string(link_id_counter),
              link_starting_coordinates, link_ending_coordinates};
    link_id_counter += 1;
    links.push_back(link);
  }

  for (const std::string &leg_prefix : joint_link_names) {

    float theta1, theta2, theta3;
    std::string shoulder_joint_name, elbow_joint_name, wrist_joint_name,
        end_effector_name;

    shoulder_joint_name = leg_prefix + shoulder_str;
    elbow_joint_name = leg_prefix + elbow_str;
    wrist_joint_name = leg_prefix + wrist_str;
    end_effector_name = leg_prefix + end_effector_str;

    Link shoulder_to_elbow_link{link_id_counter,
                                leg_prefix + shoulder_str + "_" + elbow_str,
                                joints.at(shoulder_joint_name).location,
                                joints.at(elbow_joint_name).location};
    link_id_counter++;
    links.push_back(shoulder_to_elbow_link);

    Link elbow_to_wrist_joint_link{link_id_counter,
                                   leg_prefix + elbow_str + "_" + wrist_str,
                                   joints.at(elbow_joint_name).location,
                                   joints.at(wrist_joint_name).location};
    link_id_counter++;
    links.push_back(elbow_to_wrist_joint_link);

    Link wrist_to_end_effector_link{
        link_id_counter, leg_prefix + wrist_str + "_" + end_effector_str,
        joints.at(wrist_joint_name).location,
        end_effectors.at(end_effector_name).location};
    link_id_counter++;
    links.push_back(wrist_to_end_effector_link);
  }
  return links;
}

Robomodel RoboDog::getForwardKinematics(
    const Vector3d &body_location, const Vector3d &body_rotation,
    const std::unordered_map<int, float> &joint_angle_mapping) {
  std::vector<Link> links;
  std::vector<Joint> joints_vect;
  std::vector<Joint> end_effectors_vect;

  // we get a struct or map of id to angle

  // then we go leg by leg. we check if we were given all the IDs for one leg.
  // if we werent given them all, default the missing angles to 0.
  // get leg.

  // when have legs, draw links

  // first draw body links
  // then draw links for each leg

  std::unordered_map<std::string, Joint> joints;
  std::unordered_map<std::string, Joint> end_effectors;

  std::unordered_map<std::string, Matrix4d> shoulder_transform_matrices =
      getBaseToShoulderTransforms(body_location, body_rotation);

  std::vector<std::string> joint_link_names = {
      front_left_leg_prefix, front_right_leg_prefix, back_left_leg_prefix,
      back_right_leg_prefix};

  for (const std::string &leg_prefix : joint_link_names) {

    float theta1, theta2, theta3;
    std::string shoulder_joint_name, elbow_joint_name, wrist_joint_name;
    int shoulder_id, elbow_id, wrist_id;
    shoulder_joint_name = leg_prefix + shoulder_str;
    shoulder_id = joint_str_to_id_mapping.at(shoulder_joint_name);
    if (joint_angle_mapping.find(shoulder_id) != joint_angle_mapping.end()) {
      theta1 = joint_angle_mapping.at(shoulder_id);
    } else {
      theta1 = 0.0;
    }

    elbow_joint_name = leg_prefix + elbow_str;
    elbow_id = joint_str_to_id_mapping.at(elbow_joint_name);
    if (joint_angle_mapping.find(elbow_id) != joint_angle_mapping.end()) {
      theta2 = joint_angle_mapping.at(elbow_id);
    } else {
      theta2 = 0.0;
    }

    wrist_joint_name = leg_prefix + wrist_str;
    wrist_id = joint_str_to_id_mapping.at(wrist_joint_name);
    if (joint_angle_mapping.find(wrist_id) != joint_angle_mapping.end()) {
      theta3 = joint_angle_mapping.at(wrist_id);
    } else {
      theta3 = 0.0;
    }

    std::unordered_map<std::string, Joint> leg_joints =
        getJointsForLeg(shoulder_transform_matrices[leg_prefix], leg_prefix,
                        theta1, theta2, theta3);

    joints[shoulder_joint_name] = leg_joints[shoulder_joint_name];
    joints[elbow_joint_name] = leg_joints[elbow_joint_name];
    joints[wrist_joint_name] = leg_joints[wrist_joint_name];

    end_effectors[leg_prefix + end_effector_str] =
        leg_joints[leg_prefix + end_effector_str];
  }

  links =
      getLinksFromJoints(shoulder_transform_matrices, joints, end_effectors);

  for (auto &it : joints) {
    joints_vect.push_back(it.second);
  }

  for (auto &it : end_effectors) {
    end_effectors_vect.push_back(it.second);
  }

  Robomodel robomodel{id, name, links, joints_vect, end_effectors_vect};

  return robomodel;
}
