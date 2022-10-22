#ifndef MyController_hpp
#define MyController_hpp

#include <memory>

#include "dto/DTOs.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include "kinematics/RoboKinematicModel.hpp"

auto getSharedPtrFromModel(RoboModel *model);

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

    Coordinate starting_location{0, 0, 0};
    std::string robo_dog_name("Robot Dog");
    RoboDog *robot_dog_ptr = new RoboDog(0, robo_dog_name, starting_location);
    robo_dog_ = std::unique_ptr<RoboDog>(robot_dog_ptr);
    robo_models_.push_back(robo_dog_);
  }

public:
  ENDPOINT("GET", "/robomodels", getRoboModels) {

    oatpp::List<oatpp::Object<RoboModelDescriptionDTO>> descriptions;

    for (RoboModel model : robo_models_) {
      auto desc = RoboModelDescriptionDTO::createShared();
      desc->id = model.id;
      desc->name = model.name;
      descriptions.push_back(desc);
    }

    return createDtoResponse(Status::CODE_200, dog_desc);
  }

  ENDPOINT("GET", "/robomodels/{roboModelId}", getRoboModelById,
           PATH(Int64, roboModelId, "roboModelId")) {

    auto robo_model = RoboModelDTO::createShared();

    bool model_found = false;
    for (RoboModel *model : robo_models_) {

      if (model->id != roboModelId) {
        continue;
      }
      auto desc = getSharedPtrFromModel(model);
      model_found = true;
      break;
    }
    return createDtoResponse(Status::CODE_200, dto);
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
  std::vector<std::unique_ptr<RoboModel>> robo_models_;
  std::unique_ptr<RoboDog> robo_dog_;
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */