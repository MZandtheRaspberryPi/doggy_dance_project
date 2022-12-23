#include <string>
#include <vector>

#include <Eigen/Dense>

struct Joint {

  int number;
  std::string name;
  Eigen::Vector3d location;
};

struct Link {

  int number;
  std::string name;
  Eigen::Vector3d start_location;
  Eigen::Vector3d end_location;
};

class RoboModel {
public:
  RoboModel(const int &id, const std::string &name);

  void setJoints(const std::vector<Joint> &joints);
  std::vector<Joint> getJoints();
  void setLinks(const std::vector<Link> &links);
  std::vector<Link> getLinks();

  /*
  virtual void setRoboPosition(const float &x, const float &y, const float &z,
                               const float &roll, const float &pitch,
                               const float &yaw) = 0;
  */

  std::string getName();
  int getId();

private:
  int id_;
  std::string name_;
  std::vector<Link> links_;
  std::vector<Joint> joints_;
};

class RoboDog : public RoboModel {
public:
  RoboDog(const int &id, const std::string &name,
          const Eigen::Vector3d &starting_location);
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