#ifndef DTOs_hpp
#define DTOs_hpp

#include <string>
#include <vector>

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class RoboModelDescriptionDTO : public oatpp::DTO {

  DTO_INIT(RoboModelDescriptionDTO, DTO)
  DTO_FIELD(Int32, id);
  DTO_FIELD(String, name);
  DTO_FIELD(Int32, num_links);
  DTO_FIELD(Int32, num_joints);
  DTO_FIELD(Int32, num_end_effectors);
};

class RoboModelDescriptionListDTO : public oatpp::DTO {

  DTO_INIT(RoboModelDescriptionListDTO, DTO)
  DTO_FIELD(Vector<Object<RoboModelDescriptionDTO>>, descriptions);
};

class CoordinateDTO : public oatpp::DTO {

  DTO_INIT(CoordinateDTO, DTO /* extends */)
  DTO_FIELD(Float32, x);
  DTO_FIELD(Float32, y);
  DTO_FIELD(Float32, z);
};

class JointDTO : public oatpp::DTO {

  DTO_INIT(JointDTO, DTO /* extends */)

  DTO_FIELD(Int32, number);
  DTO_FIELD(String, name);
  DTO_FIELD(Object<CoordinateDTO>, location);
  DTO_FIELD(Int8, joint_type);
  DTO_FIELD(Float32, current_angle_radians);
  DTO_FIELD(Float32, min_angle_radians);
  DTO_FIELD(Float32, max_angle_radians);
};

class EndEffectorDTO : public oatpp::DTO {

  DTO_INIT(EndEffectorDTO, DTO /* extends */)

  DTO_FIELD(Int32, number);
  DTO_FIELD(String, name);
  DTO_FIELD(Object<CoordinateDTO>, location);
  DTO_FIELD(Float32, min_x);
  DTO_FIELD(Float32, min_y);
  DTO_FIELD(Float32, min_z);
  DTO_FIELD(Float32, max_x);
  ;
  DTO_FIELD(Float32, max_y);
  DTO_FIELD(Float32, max_z);
};

class LinkDTO : public oatpp::DTO {

  DTO_INIT(LinkDTO, DTO /* extends */)

  DTO_FIELD(Int32, number);
  DTO_FIELD(String, name);
  DTO_FIELD(Object<CoordinateDTO>, start_location);
  DTO_FIELD(Object<CoordinateDTO>, end_location);
};

class RoboModelDTO : public oatpp::DTO {

  DTO_INIT(RoboModelDTO, DTO /* extends */)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, name);
  DTO_FIELD(Vector<Object<LinkDTO>>, links);
  DTO_FIELD(Vector<Object<JointDTO>>, joints);
  DTO_FIELD(Vector<Object<EndEffectorDTO>>, end_effectors);
};

class RoboModelListDTO : public oatpp::DTO {

  DTO_INIT(RoboModelListDTO, DTO)
  DTO_FIELD(List<Object<RoboModelDTO>>, robo_models);
};

class JointIdDTO : public oatpp::DTO {
  DTO_INIT(JointIdDTO, DTO);
  DTO_FIELD(Int32, id);
  DTO_FIELD(Float32, current_angle_radians);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */