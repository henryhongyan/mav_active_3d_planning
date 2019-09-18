#ifndef ACTIVE_3D_PLANNING_CORE_DATA_VISUALILZATION_MARKERS_H
#define ACTIVE_3D_PLANNING_CORE_DATA_VISUALILZATION_MARKERS_H

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>

namespace active_3d_planning {

struct Color {
  double r = 0;
  double g = 0;
  double b = 0;
  double a = 1;
};

struct VisualizationMarker {
    // from ROS visualization_msgs/marker.msg documentation (Only relevant fields)
  unsigned char ARROW = 0;
  unsigned char CUBE = 1;
  unsigned char SPHERE = 2;
  unsigned char CYLINDER = 3;
  unsigned char LINE_STRIP = 4;
  unsigned char LINE_LIST = 5;
  unsigned char CUBE_LIST = 6;
  unsigned char SPHERE_LIST = 7;
  unsigned char POINTS = 8;
  unsigned char TEXT_VIEW_FACING = 9;
  unsigned char MESH_RESOURCE = 10;
  unsigned char TRIANGLE_LIST = 11;
  unsigned char ADD = 0;
  unsigned char MODIFY = 0;
  unsigned char DELETE = 2;
  unsigned char DELETEALL = 3;
  int type = 0;
  int action = 0;
  int id = 0;
  std::string ns = "";
  Eigen::Vector3d position;
  Eigen::Quaterniond orientation;
  Eigen::Vector3d scale;
  Color color;
  std::vector<Eigen::Vector3d> points;
  std::vector<Color> colors;
};

struct VisualizationMarkers {
    std::vector<VisualizationMarker>markers;

    // access
    virtual void addMarker(const VisualizationMarker &marker);
    int getNextVisualizationId();
};

} // namespace active_3d_planning
#endif /* ACTIVE_3D_PLANNING_CORE_DATA_VISUALILZATION_MARKERS_H */