#ifndef MyController_hpp
#define MyController_hpp

#include <memory>

#include <Eigen/Dense>

#include "dto/DTOs.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include "kinematics/RoboKinematicModel.hpp"

oatpp::data::mapping::type::DTOWrapper<RoboModelDTO>
getRoboModelDTOSharedPtrFromModel(const Robomodel &robomodel);

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

public:
  ADD_CORS(getRoboModels)
  ENDPOINT("GET", "/v1/descriptions", getRoboModels) {

    auto robo_model_desc_list_dto = RoboModelDescriptionListDTO::createShared();

    robo_model_desc_list_dto->descriptions = {};

    auto dog_model_desc = RoboModelDescriptionDTO::createShared();
    dog_model_desc->id = RoboDog::id;
    dog_model_desc->name = RoboDog::name;
    dog_model_desc->num_links = RoboDog::num_links;
    dog_model_desc->num_joints = RoboDog::num_joints;
    dog_model_desc->num_end_effectors = RoboDog::num_end_effectors;

    robo_model_desc_list_dto->descriptions->push_back(dog_model_desc);

    return createDtoResponse(Status::CODE_200, robo_model_desc_list_dto);
  }

  ADD_CORS(getRoboModelById)
  ENDPOINT("GET", "/v1/forward_kinematics/", getRoboModelById,
           QUERY(Int32, robo_model_id, "robo_model_id", 0),
           QUERY(Float32, body_x_meters, "body_x_meters", 0.0),
           QUERY(Float32, body_y_meters, "body_y_meters", 0.0),
           QUERY(Float32, body_z_meters, "body_z_meters", 0.0),
           QUERY(Float32, body_pitch_rad, "body_pitch_rad", 0.0),
           QUERY(Float32, body_yaw_rad, "body_yaw_rad", 0.0),
           QUERY(Float32, body_roll_rad, "body_roll_rad", 0.0),
           QUERIES(QueryParams, queryParams)) {
    std::unordered_map<int, float> joint_angle_mapping;

    auto robo_model_list = RoboModelListDTO::createShared();
    robo_model_list->robo_models = {};

    auto robo_model = RoboModelDTO::createShared();

    Robomodel robomodel_result;
    Vector3d body_location{body_x_meters, body_y_meters, body_z_meters};
    Vector3d body_rotation{body_roll_rad, body_pitch_rad, body_yaw_rad};
    std::cout << body_x_meters << std::endl;

    bool model_found = false;
    switch (robo_model_id) {
    case 0:
      for (int i = 1; i <= RoboDog::num_joints; i++) {
        const oatpp::data::share::StringKeyLabel label(std::to_string(i));

        if (queryParams.get(label) != nullptr) {
          std::string joint_val_str = queryParams.get(label);
          float joint_val_flt = std::stof(joint_val_str);
          joint_angle_mapping[i] = joint_val_flt;
        }
      }

      robomodel_result = RoboDog::getForwardKinematics(
          body_location, body_rotation, joint_angle_mapping);
      robo_model = getRoboModelDTOSharedPtrFromModel(robomodel_result);
      model_found = true;
      break;
    default:
      break;
    }

    if (model_found) {

      return createDtoResponse(Status::CODE_200, robo_model);
    } else {
      return createResponse(
          Status::CODE_400,
          "given model id of '" + std::to_string(robo_model_id.getValue(0)) +
              "' not in supported models. Supported models are: 0.");
    }
  }
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */