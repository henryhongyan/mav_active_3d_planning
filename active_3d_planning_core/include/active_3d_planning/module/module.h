#ifndef ACTIVE_3D_PLANNING_CORE_MODULE_H
#define ACTIVE_3D_PLANNING_CORE_MODULE_H

#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <typeinfo>

#include "active_3d_planning/module/module_factory_registry.h"

namespace active_3d_planning {
class PlannerI;
// Base class for all modules, provides creation functionalities through the
// factory
class Module {
public:
  typedef std::map<std::string, std::string> ParamMap;

  Module(PlannerI &planner);
  virtual ~Module() = default;

  // factory method that sets up the module from a param map
  virtual void setupFromParamMap(ParamMap *param_map) = 0;
  virtual void setVerbose(bool verbose);

  // Throw an exception if module parametrization is invalid. Call this after
  // module constructors.
  void assureParamsValid();

  // Allow modules to specify validity conditions. Return true if valid. Per
  // default all params are valid.
  virtual bool checkParamsValid(std::string *error_message) { return true; }

protected:
  // Utility function to parse param map and create a verbose text
  template <typename T>
  void setParam(ParamMap *map, std::string param_name, T *param,
                T param_default) {
    // Setup verbose description
    std::string verbose_text("");
    ParamMap::iterator it = map->find(std::string("verbose_text"));
    if (it != map->end()) {
      // Already have some verbose_text
      verbose_text = it->second + "\n";
    }
    verbose_text += param_name + ": ";

    // Parse param
    it = map->find(param_name);
    if (it != map->end()) {
      std::istringstream iss(it->second); // String conversion
      iss >> *param;
      verbose_text += it->second;
    } else {
      *param = param_default;
      std::ostringstream oss("");
      oss << param_default;
      verbose_text += oss.str() + " (default)";
    }
    (*map)[std::string("verbose_text")] = verbose_text;
  }

  // whether to display the module creation info
  bool verbose_modules_;
  PlannerI &planner_;
};
} // namespace active_3d_planning
#endif // ACTIVE_3D_PLANNING_CORE_MODULE_H