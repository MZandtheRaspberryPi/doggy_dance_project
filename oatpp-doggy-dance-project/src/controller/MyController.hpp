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
getRoboModelDTOSharedPtrFromModel(std::shared_ptr<RoboModel> model);

oatpp::data::mapping::type::DTOWrapper<RoboModelDescriptionDTO>
getRoboModelDescDTOSharedPtrFromModel(std::shared_ptr<RoboModel> model);

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
      : oatpp::web::server::api::ApiController(objectMapper) {

    Eigen::Vector3d starting_location{0, 0, 1};
    std::string robo_dog_name("Robot Dog");
    robo_models_.push_back(std::shared_ptr<RoboModel>(
        new RoboDog(0, robo_dog_name, starting_location)));
  }

public:
  ADD_CORS(getRoboModels)
  ENDPOINT("GET", "/robomodels", getRoboModels) {

    auto robo_model_desc_list_dto = RoboModelDescriptionListDTO::createShared();

    robo_model_desc_list_dto->descriptions = {};
    for (std::shared_ptr<RoboModel> model : robo_models_) {
      auto robo_model_desc_dto = getRoboModelDescDTOSharedPtrFromModel(model);
      robo_model_desc_list_dto->descriptions->push_back(robo_model_desc_dto);
    }

    return createDtoResponse(Status::CODE_200, robo_model_desc_list_dto);
  }

  ADD_CORS(getRoboModelById)
  ENDPOINT("GET", "/robomodels/{roboModelId}", getRoboModelById,
           PATH(Int64, roboModelId, "roboModelId")) {

    auto robo_model = RoboModelDTO::createShared();

    bool model_found = false;
    for (std::shared_ptr<RoboModel> model : robo_models_) {

      if (model->getId() != roboModelId) {
        continue;
      }
      robo_model = getRoboModelDTOSharedPtrFromModel(model);
      model_found = true;
      break;
    }
    if (model_found) {

      return createDtoResponse(Status::CODE_200, robo_model);
    } else {
      return createDtoResponse(Status::CODE_500, robo_model);
    }
  }

  /*
    ENDPOINT("GET", "/robomodels", getRoboModels) {
      auto dto_robomodel = RoboModel::createShared();
      auto dto_joint = Joint::createShared();
      auto dto_link = Link::createShared();
      auto dto_coordinate_1 = Coordinate::createShared();
      auto dto_coordinate_2 = Coordinate::createShared();
      auto dto_coordinate_3 = Coordinate::createShared();
      dto_coordinate_1->x = 1.1;
      dto_coordinate_1->y = 2.1;
      dto_coordinate_1->z = 3.1;

      dto_coordinate_2->x = 1.1;
      dto_coordinate_2->y = 2.1;
      dto_coordinate_2->z = 3.1;

      dto_coordinate_3->x = 1.1;
      dto_coordinate_3->y = 2.1;
      dto_coordinate_3->z = 3.1;

      dto_joint->location = dto_coordinate_1;
      dto_joint->name = "test_joint";
      dto_joint->number = 0;

      dto_link->number = 0;
      dto_link->name = "link1";
      dto_link->start_location = dto_coordinate_2;
      dto_link->end_location = dto_coordinate_3;

      oatpp::List<oatpp::Object<Link>> links = {dto_link};
      oatpp::List<oatpp::Object<Joint>> joints = {dto_joint};

      dto_robomodel->name = "robo_dog";
      dto_robomodel->links = links;
      dto_robomodel->joints = joints;
      dto_robomodel->id = 0;

      return createDtoResponse(Status::CODE_200, dto_robomodel);
    }

  ENDPOINT("GET", "/hello", getHello) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  }

  ENDPOINT("GET", "/inverse_kinematics/{roboModelId}", getInverseKinematics,
           PATH(Int64, roboModelId, "roboModelId")) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Robot Models IK " + std::to_string(*roboModelId);
    return createDtoResponse(Status::CODE_200, dto);
  }
      */

private:
  std::vector<std::shared_ptr<RoboModel>> robo_models_;
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */