#include "RoboKinematicModel.hpp"

RoboModel::RoboModel(const int &id, const std::string &name)
    : id_(id), name_(name) {}

void RoboModel::setJoints(const std::vector<Joint> &joints) {
  joints_ = joints;
}

std::vector<Joint> RoboModel::getJoints() { return joints_; }

void RoboModel::setLinks(const std::vector<Link> &links) { links_ = links; }

std::vector<Link> RoboModel::getLinks() { return links_; }

Coordinate translate(const Coordinate &coordinate,
                     const Coordinate &translation) {
  Coordinate new_coordinate;
  new_coordinate.x = coordinate.x + translation.x;
  new_coordinate.y = coordinate.y + translation.y;
  new_coordinate.z = coordinate.z + translation.z;
}

RoboDog::RoboDog(const int &id, const std::string &name,
                 const Coordinate &starting_location)
    : RoboModel(id, name) {

  std::vector<Link> links;
  std::vector<Joint> joints;

  Coordinate link1_starting_translation{body_length_ / 2, body_width / 2, 0};
  Coordinate link1_ending_translation{body_length_ / 2, -body_width / 2, 0};
  Coordinate link1_starting_coordinate =
      translate(starting_location, link1_starting_translation);
  Coordinate link1_ending_coordinate =
      translate(starting_location, link1_ending_translation);

  Link link1{1, "front_body", link1_starting_coordinate,
             link1_ending_coordinate};
  links.push_back(link1);
  setLinks(links);

  Joint joint1{1, "front_left_shoulder", link1_starting_coordinate};
  joints.push_back(joint1);
  setJoints(joints);

  /*

  export const ROBOMODELS : Robomodel[] = [
    {
      id : 1,
      name : 'Dog',
      links : [
        {
          id : 1,
          name : "front_body",
          start_x : STARTING_XYZ.x + BODYLENGTH / 2,
          start_y : STARTING_XYZ.y + BODYWIDTH / 2,
          start_z : STARTING_XYZ.z,
          end_x : STARTING_XYZ.x + BODYLENGTH / 2,
          end_y : STARTING_XYZ.y - BODYWIDTH / 2,
          end_z : STARTING_XYZ.z
        },
        {
          id : 2,
          name : "right_body",
          start_x : STARTING_XYZ.x + BODYLENGTH / 2,
          start_y : STARTING_XYZ.y - BODYWIDTH / 2,
          start_z : STARTING_XYZ.z,
          end_x : STARTING_XYZ.x - BODYLENGTH / 2,
          end_y : STARTING_XYZ.y - BODYWIDTH / 2,
          end_z : STARTING_XYZ.z
        },
        {
          id : 3,
          name : "back_body",
          start_x : STARTING_XYZ.x - BODYLENGTH / 2,
          start_y : STARTING_XYZ.y - BODYWIDTH / 2,
          start_z : STARTING_XYZ.z,
          end_x : STARTING_XYZ.x - BODYLENGTH / 2,
          end_y : STARTING_XYZ.y + BODYWIDTH / 2,
          end_z : STARTING_XYZ.z
        },
        {
          id : 4,
          name : "left_body",
          start_x : STARTING_XYZ.x - BODYLENGTH / 2,
          start_y : STARTING_XYZ.y + BODYWIDTH / 2,
          start_z : STARTING_XYZ.z,
          end_x : STARTING_XYZ.x + BODYLENGTH / 2,
          end_y : STARTING_XYZ.y + BODYWIDTH / 2,
          end_z : STARTING_XYZ.z
        }
      ],
      joints : [
        {
          id : 1,
          name : "front_left_shoulder",
          axis : "y",
          x : STARTING_XYZ.x + BODYLENGTH / 2,
          y : STARTING_XYZ.y - BODYWIDTH / 2,
          z : STARTING_XYZ.z
        },
        {
          id : 2,
          name : "front_right_shoulder",
          axis : "y",
          x : STARTING_XYZ.x + BODYLENGTH / 2,
          y : STARTING_XYZ.y + BODYWIDTH / 2,
          z : STARTING_XYZ.z
        },
        {
          id : 3,
          name : "back_left_shoulder",
          axis : "y",
          x : STARTING_XYZ.x - BODYLENGTH / 2,
          y : STARTING_XYZ.y - BODYWIDTH / 2,
          z : STARTING_XYZ.z
        },
        {
          id : 4,
          name : "back_right_shoulder",
          axis : "y",
          x : STARTING_XYZ.x - BODYLENGTH / 2,
          y : STARTING_XYZ.y + BODYWIDTH / 2,
          z : STARTING_XYZ.z
        }
      ]
    },
    {
      id : 2,
      name : 'HandWave',
      links : [
        {
          id : 1,
          name : "upper_arm",
          start_x : 0,
          start_y : 0.0,
          start_z : 0,
          end_x : 0.1,
          end_y : 0.0,
          end_z : 1
        },
        {
          id : 2,
          name : "lower_arm",
          start_x : 0.1,
          start_y : 0.0,
          start_z : 1,  setLinks(links);
          end_z : 1.6
        },
        {
          id : 3,
          name : "hand",
          start_x : 0.2,
          start_y : 0.0,
          start_z : 1.6,
          end_x : 0.3,
          end_y : 0.0,
          end_z : 2.0
        }
      ],
      joints : [
        {id : 1, name : "shoulder", axis : "x", x : 0, y : 0, z : 0},
        {id : 2, name : "elbow", axis : "x", x : 0.1, y : 0, z : 1},
        {id : 3, name : "wrist", axis : "x", x : 0.2, y : 0, z : 1.6}
      ]
    }

  ];
  */
}
setLinks(links);