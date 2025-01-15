#include <iostream>
#include "../lib/weather.hpp"

int main (int argc, char *argv[]) {

  std::cout << "here\n";
  Forecast weather_forecast;
  if (!weather_forecast.getStartValue(argv[1])) {
    return EXIT_FAILURE;
  }
  if (!weather_forecast.run()) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
