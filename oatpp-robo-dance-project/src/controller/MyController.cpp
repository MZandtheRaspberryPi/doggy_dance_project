#include "MyController.hpp"

oatpp::data::mapping::type::DTOWrapper<RoboModelDTO>
getRoboModelDTOSharedPtrFromModel(const Robomodel &robomodel) {

  auto robo_model = RoboModelDTO::createShared();

  robo_model->joints = {};
  robo_model->links = {};
  robo_model->end_effectors = {};

  for (const Joint &joint : robomodel.joints) {
    auto dto_joint = JointDTO::createShared();

    auto joint_location = CoordinateDTO::createShared();
    joint_location->x = joint.location[0];
    joint_location->y = joint.location[1];
    joint_location->z = joint.location[2];

    dto_joint->location = joint_location;
    dto_joint->name = joint.name;
    dto_joint->number = joint.number;
    dto_joint->joint_type = joint.joint_type;
    dto_joint->current_angle_radians = joint.current_angle_radians;
    dto_joint->min_angle_radians = joint.min_angle_radians;
    dto_joint->max_angle_radians = joint.max_angle_radians;
    robo_model->joints->push_back(dto_joint);
  }

  for (const Link &link : robomodel.links) {
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

  for (const EndEffector &end_effector : robomodel.end_effectors) {
    auto dto_end_effector = EndEffectorDTO::createShared();

    auto end_effector_location_global = CoordinateDTO::createShared();

    end_effector_location_global->x = end_effector.location_global[0];
    end_effector_location_global->y = end_effector.location_global[1];
    end_effector_location_global->z = end_effector.location_global[2];

    dto_end_effector->location_global = end_effector_location_global;

    auto end_effector_location_shoulder = CoordinateDTO::createShared();

    end_effector_location_shoulder->x = end_effector.location_shoulder[0];
    end_effector_location_shoulder->y = end_effector.location_shoulder[1];
    end_effector_location_shoulder->z = end_effector.location_shoulder[2];

    dto_end_effector->location_shoulder = end_effector_location_shoulder;

    dto_end_effector->name = end_effector.name;
    dto_end_effector->number = end_effector.number;

    dto_end_effector->min_x = end_effector.min_x;
    dto_end_effector->min_y = end_effector.min_y;
    dto_end_effector->min_z = end_effector.min_z;

    dto_end_effector->max_x = end_effector.max_x;
    dto_end_effector->max_y = end_effector.max_y;
    dto_end_effector->max_z = end_effector.max_z;

    robo_model->end_effectors->push_back(dto_end_effector);
  }

  robo_model->id = robomodel.id;
  robo_model->name = robomodel.name;
  return robo_model;
}
