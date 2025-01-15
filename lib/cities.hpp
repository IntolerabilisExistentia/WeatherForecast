#pragma once

#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <ftxui/component/event.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/dom/elements.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/component/loop.hpp>
#include <ftxui/component/screen_interactive.hpp>

const int kErrorHttpCode = 200;
const int kTimesOfDay = 4;
const int kTimeOfDayLength = 6;
const int kDateBeginAndEnd = 5;

class WeatherValue {
public:
  WeatherValue() = default;
  ~WeatherValue() = default;

  int temperature_ = 0;
  int apparent_temperature_ = 0;
  int weather_code_ = 0;
  int wind_speed_max_ = -1;
  int wind_speed_min_ = 100;
  int relative_humidity_ = 0;

  void setValue(nlohmann::json& data, int time_of_day);
  void setValue(nlohmann::json& data);

  std::string getDescription();

  ftxui::Element printDayWeather();

  ftxui::Element printValues();
  ftxui::Element printArt();

  ftxui::Element printTemperature();
  ftxui::Element printWindSpeed();
  ftxui::Element printRelativeHumidity();
  ftxui::Element printDescription();
};

class City {
public:
  std::vector<WeatherValue> weather_;
  WeatherValue current_;
  std::string name_;

  City(const std::string& name, int count_of_days);
  bool getCoords(std::string& api_key);
  bool updateForecast();
  bool setForecast(cpr::Parameters& parameters);
  void setAverageValues(nlohmann::json& data);

  void incrementDays();
  void decrementDays();

  std::string getDate(int day);

  ftxui::Element output();
  ftxui::Element outputWeatherDay(int day);
  ftxui::Element outputWeatherAll();
  ftxui::Element outputWeatherCur();

private:
  std::pair<std::string, std::string> coordinates_;
  std::vector<std::string> dates_;
  int count_of_days_;
};
