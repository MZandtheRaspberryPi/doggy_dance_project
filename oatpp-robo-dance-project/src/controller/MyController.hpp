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
  ENDPOINT("GET", "/robomodels", getRoboModels) {

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
  ENDPOINT("GET", "/robomodels/{roboModelId}", getRoboModelById,
           PATH(Int64, roboModelId, "roboModelId")) {

    auto robo_model = RoboModelDTO::createShared();

    Robomodel robomodel_result;
    Vector3d body_location{0, 0, 0};
    Vector3d body_rotation{0, 0, 0};
    std::unordered_map<int, float> joint_angle_mapping;

    bool model_found = false;
    switch (roboModelId) {
    case 0:
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
      return createDtoResponse(Status::CODE_500, robo_model);
    }
  }
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */