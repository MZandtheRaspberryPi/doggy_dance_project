#include "MyController.hpp"

oatpp::data::mapping::type::DTOWrapper<RoboModelDTO>
getRoboModelDTOSharedPtrFromModel(std::shared_ptr<RoboModel> model) {

  auto robo_model = RoboModelDTO::createShared();

  robo_model->joints = {};
  robo_model->links = {};

  for (const Joint &joint : model->getJoints()) {
    auto dto_joint = JointDTO::createShared();

    auto joint_location = CoordinateDTO::createShared();
    joint_location->x = joint.location[0];
    joint_location->y = joint.location[1];
    joint_location->z = joint.location[2];

    dto_joint->location = joint_location;
    dto_joint->name = joint.name;
    dto_joint->number = joint.number;
    robo_model->joints->push_back(dto_joint);
  }

  for (const Link &link : model->getLinks()) {
    auto dto_link = LinkDTO::createShared();
    auto dto_coordinate_start = CoordinateDTO::createShared();
    auto dto_coordinate_end = CoordinateDTO::createShared();

    dto_coordinate_start->x = link.start_location[0];
    dto_coordinate_start->y = link.start_location[1];
    dto_coordinate_start->z = link.start_location[2];

    dto_coordinate_end->x = link.end_location[0];
    dto_coordinate_end->y = link.end_location[1];
    dto_coordinate_end->z = link.end_location[2];

    dto_link->number = link.number;
    dto_link->name = link.name;
    dto_link->start_location = dto_coordinate_start;
    dto_link->end_location = dto_coordinate_end;
    robo_model->links->push_back(dto_link);
  }

  robo_model->id = model->getId();
  robo_model->name = model->getName();
  return robo_model;
}

oatpp::data::mapping::type::DTOWrapper<RoboModelDescriptionDTO>
getRoboModelDescDTOSharedPtrFromModel(std::shared_ptr<RoboModel> model) {

  auto robo_model_desc = RoboModelDescriptionDTO::createShared();

  robo_model_desc->id = model->getId();
  robo_model_desc->name = model->getName();
  robo_model_desc->num_joints = model->getJoints().size();
  robo_model_desc->num_links = model->getLinks().size();
  return robo_model_desc;
}
