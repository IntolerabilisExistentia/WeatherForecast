#include "cities.hpp"

City::City(const std::string& name, int count_of_days) : name_(name), count_of_days_(count_of_days) {}

bool City::getCoords(std::string& api_key) {
  cpr::Response response = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                           cpr::Header{{"X-Api-Key", api_key}},
                           cpr::Parameters{{"name", name_}});
    
  if (response.status_code != kErrorHttpCode) {
    std::cerr << response.error.message;
    return false;
  }

  nlohmann::json data = nlohmann::json::parse(response.text);

  coordinates_.first = data[0]["latitude"].dump();
  coordinates_.second = data[0]["longitude"].dump();

  return true;
}

void WeatherValue::setValue(nlohmann::json& data, int part_of_day) {
  for (int i = 0; i < kTimeOfDayLength; ++i) {
    apparent_temperature_ += data["hourly"]["apparent_temperature"][part_of_day + i].get<int>();
    temperature_ += data["hourly"]["temperature_2m"][part_of_day + i].get<int>();
    relative_humidity_ += data["hourly"]["relativehumidity_2m"][part_of_day + i].get<int>();

    wind_speed_min_ = data["hourly"]["windspeed_10m"][part_of_day + i].get<int>() < wind_speed_min_ ?
                     data["hourly"]["windspeed_10m"][part_of_day + i].get<int>() : wind_speed_min_;
    wind_speed_max_ = data["hourly"]["windspeed_10m"][part_of_day + i].get<int>() > wind_speed_max_ ?
                     data["hourly"]["windspeed_10m"][part_of_day + i].get<int>() : wind_speed_max_;
  }

  apparent_temperature_ /= kTimeOfDayLength;
  temperature_ /= kTimeOfDayLength;
  relative_humidity_ /= kTimeOfDayLength;
  weather_code_ = data["hourly"]["weathercode"][part_of_day + 3].get<int>();
}

void WeatherValue::setValue(nlohmann::json& data) {
  apparent_temperature_ = data["current"]["apparent_temperature"].get<int>();
  temperature_ = data["current"]["temperature_2m"].get<int>();
  wind_speed_min_ = data["current"]["windspeed_10m"].get<int>();
  wind_speed_max_ = data["current"]["windspeed_10m"].get<int>();
  relative_humidity_ = data["current"]["relativehumidity_2m"].get<int>();
  weather_code_ = data["current"]["weathercode"].get<int>();
}

void City::setAverageValues(nlohmann::json& data) {
  for (int i = 0; i < count_of_days_; ++i) {
    dates_.push_back(data["hourly"]["time"][24 * i].get<std::string>().substr(kDateBeginAndEnd, kDateBeginAndEnd));

    for (int j = 0; j < kTimesOfDay; j++) {
      WeatherValue values;
      values.setValue(data, 24 * i + kTimesOfDay * j);
      weather_.push_back(values);
    }
  }
}

bool City::setForecast(cpr::Parameters& parameters) {
  cpr::Response response = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"}, 
                                    parameters);

  if (response.status_code != kErrorHttpCode) {
    std::cerr << response.error.message;
    return false;
  }

  nlohmann::json data = nlohmann::json::parse(response.text, nullptr, false);

  if (data.is_discarded()) {
    std::cerr << "Error while parsing JSON";
    return false;
  }

  if (weather_.empty() && count_of_days_ != 0) {
    setAverageValues(data);
    return true; 
  }
  
  current_.setValue(data);

  return true;
}

bool City::updateForecast() {
  cpr::Parameters parameters_for_current = {{"latitude", coordinates_.first},
                                           {"longitude", coordinates_.second},
                                           {"current", "temperature_2m"},
                                           {"current", "relativehumidity_2m"},
                                           {"current", "apparent_temperature"},
                                           {"current", "weathercode"},
                                           {"current", "windspeed_10m"}};

  cpr::Parameters parameters_for_days = {{"latitude", coordinates_.first},
                                        {"longitude", coordinates_.second},
                                        {"hourly", "temperature_2m"},
                                        {"hourly", "relativehumidity_2m"},
                                        {"hourly", "apparent_temperature"},
                                        {"hourly", "weathercode"},
                                        {"hourly", "windspeed_10m"},
                                        {"forecast_days", std::to_string(count_of_days_)}};

  weather_.clear();
  dates_.clear();

  if (count_of_days_ != 0) {
    if (!setForecast(parameters_for_days)) {
      return false;
    }
  }

  if (!setForecast(parameters_for_current)) {
    return false;
  }

  return true;
}

void City::incrementDays() {
  if (count_of_days_ < 3) {
    ++count_of_days_;
  }
}

void City::decrementDays() {
  if (count_of_days_ != 0) {
    --count_of_days_;
  }
}
