#include <string>
#include <vector>

struct Coordinate {
  float x;
  float y;
  float z;
};

struct Joint {

  int number;
  std::string name;
  Coordinate location;
};

struct Link {

  int number;
  std::string name;
  Coordinate start_location;
  Coordinate end_location;
};

class RoboModel {
public:
  RoboModel(const int &id, const std::string &name);

  void setJoints(const std::vector<Joint> &joints);
  std::vector<Joint> getJoints();
  void setLinks(const std::vector<Link> &links);
  std::vector<Link> getLinks();

  virtual void setRoboPosition(const float &x, const float &y, const float &z,
                               const float &roll, const float &pitch,
                               const float &yaw) = 0;

private:
  int id_;
  std::string name_;
  std::vector<Link> links_;
  std::vector<Joint> joints_;
};

class RoboDog : public RoboModel {
public:
  RoboDog(const int &id, const std::string &name,
          const Coordinate &starting_location);
  void setRoboPosition(const float &x, const float &y, const float &z,
                       const float &roll, const float &pitch, const float &yaw);

private:
  float l1_ = 0.25;
  float l2_ = 0.2;
  float l3_ = 0.8;
  float l4_ = 0.8;

  float body_length_ = 1.2;
  float body_width = 0.9;
};

Coordinate translate(const Coordinate &coordinate,
                     const Coordinate &translation);