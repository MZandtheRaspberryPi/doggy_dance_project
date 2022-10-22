#include "MyController.hpp"

auto getSharedPtrFromModel(RoboModel *model) {
  auto robo_model = RoboModel::createShared();

  oatpp::List<oatpp::Object<JointDTO>> joints;
  oatpp::List<oatpp::Object<LinkDTO>> links;

  for (const Joint &joint : model->getJoints()) {
    auto dto_joint = JointDTO::createShared();

    auto joint_location = CoordinateDTO::createShared();
    joint_location->x = joint.location.x;
    joint_location->y = joint.location.y;
    joint_location->z = joint.location.z;

    dto_joint->location = joint.location;
    dto_joint->name = joint.name;
    dto_joint->number = joint.number;
    joints.push_back(dto_joint);
  }

  for (const Link &link : model->getLinks()) {
    auto dto_link = LinkDTO::createShared();
    auto dto_coordinate_start = CoordinateDTO::createShared();
    auto dto_coordinate_end = CoordinateDTO::createShared();

    dto_coordinate_start->x = link.start_location.x;
    dto_coordinate_start->y = link.start_location.y;
    dto_coordinate_start->z = link.start_location.z;

    dto_coordinate_end->x = link.end_location.x;
    dto_coordinate_end->y = link.end_location.y;
    dto_coordinate_end->z = link.end_location.z;

    dto_link->number = link.number;
    dto_link->name = link.name;
    dto_link->start_location = dto_coordinate_start;
    dto_link->end_location = dto_coordinate_end;
  }
}