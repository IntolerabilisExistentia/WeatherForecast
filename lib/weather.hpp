#pragma once

#include "cities.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

class Forecast {
public:
  Forecast() = default;
  ~Forecast() = default;

  bool getStartValue(char* path);
  bool run();

private:
  std::vector<City> cities_;
  int frequancy_of_forecast_;
  time_t start_;
  time_t current_time_;
  int current_city_;
};

