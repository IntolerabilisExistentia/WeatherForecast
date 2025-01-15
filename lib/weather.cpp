#include "weather.hpp"

bool Forecast::getStartValue(char* path) {
  std::ifstream fin(path, std::ifstream::binary);

  if (!fin) {
    std::cerr << "Can not open " << path;
    return false;
  }

  nlohmann::json data = nlohmann::json::parse(fin, nullptr, false);

  if (data.is_discarded()) {
    std::cerr << "Error while parsing JSON";
    return false;
  }

  for (int i = 0; i < data["cities"].size(); ++i) {
    City city(data["cities"][i]["name"].get<std::string>(), data["cities"][i]["count_days"].get<int>());

    if (!city.getCoords(data["api_key"].get<std::string>())) {
      std::cerr << "Cant get coordinates of" << city.name_;
      return false;
    }
    
    cities_.push_back(city);
  }
  
  frequancy_of_forecast_ = data["update_frequency"].get<int>();

  return true;
}

bool Forecast::run() {
  using namespace ftxui;

  auto screen = ScreenInteractive::FitComponent();

  bool was_error = false;
  bool need_to_render = false;
  current_city_ = 0;
  time(&start_);

  cities_[current_city_].updateForecast();
    
  auto renderer = Renderer([&] {
    return vbox({cities_[current_city_].outputWeatherCur(), cities_[current_city_].outputWeatherAll(),});
  });
    
  auto component = CatchEvent(renderer, [&](Event event) {
    time(&current_time_);

    if (event == Event::Escape) {
      screen.Exit();
      return false;
    }

    if (event == Event::Character('n') || event == Event::Character('N')) {
      current_city_ = (current_city_ + 1) % cities_.size();
      need_to_render = true;
    }

    if (event == Event::Character('p') || event == Event::Character('P')) {
      current_city_ = (current_city_ + cities_.size() - 1) % cities_.size();
      need_to_render = true;
    }

    if (event == Event::Character('+')) {
      cities_[current_city_].incrementDays();
      need_to_render = true;
    }

    if (event == Event::Character('-')) {
      cities_[current_city_].decrementDays();
      need_to_render = true;
    }

    if (difftime(current_time_, start_) > frequancy_of_forecast_) {
      start_ = current_time_;
      need_to_render = true;
    }

    if (need_to_render) {
      need_to_render = false;

      if (!cities_[current_city_].updateForecast()) {
        was_error = true;
        screen.Exit();

        return false;
      }

      return true;
    }

    return false;
  });
    
  screen.Loop(component);

  return was_error;
}
