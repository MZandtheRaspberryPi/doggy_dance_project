#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

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
  ENDPOINT("GET", "/robomodels", getRoboModels) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Robot Models";
    return createDtoResponse(Status::CODE_200, dto);
  }

  ENDPOINT("GET", "/robomodels/{roboId}", getRoboModelById,
           PATH(Int64, roboId)) {
    OATPP_LOGD("Test", "userId=%d", *roboId);
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Robot Models";
    return createDtoResponse(Status::CODE_200, dto);
  }

  ENDPOINT("GET", "/hello", getHello) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  }

ENDPOINT("GET", "/users/{userId}", getUserById,
         PATH(Int64, userId)) 
{
  OATPP_LOGD("Test", "userId=%d", userId->getValue());
  return createResponse(Status::CODE_200, "OK");
}


  ENDPOINT("GET", "/inverse_kinematics", getInverseKinematics) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Robot Models";
    return createDtoResponse(Status::CODE_200, dto);
  }

  // TODO Insert Your endpoints here !!!
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */