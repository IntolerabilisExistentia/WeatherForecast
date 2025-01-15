#include "cities.hpp"

std::string City::getDate(int day) {
  return dates_[day];
}

ftxui::Element WeatherValue::printDayWeather() {
  return ftxui::hbox({printArt(), printValues()});
}

ftxui::Element WeatherValue::printValues() {
  return ftxui::vbox({
    printDescription() | ftxui::hcenter,
    ftxui::text(""),
    printTemperature(),
    printWindSpeed(),
    printRelativeHumidity(),
  });
}

ftxui::Element WeatherValue::printWindSpeed() {
  if (wind_speed_max_ == wind_speed_min_) {
    return ftxui::text(" ༄   " + std::to_string(wind_speed_min_) + " km/h");
  }

  return ftxui::text(" ༄  " + std::to_string(wind_speed_min_) + "-" +
                     std::to_string(wind_speed_max_) +  " km/h");
}

ftxui::Element WeatherValue::printTemperature() {
  return ftxui::text(" T  " + std::to_string(temperature_) + "(" + 
                     std::to_string(apparent_temperature_) + ")°C");
}

ftxui::Element WeatherValue::printRelativeHumidity() {
  return ftxui::text(" 💧  " + std::to_string(relative_humidity_) + "%");
}

ftxui::Element WeatherValue::printDescription() {
  return ftxui::text(getDescription());
}

std::string WeatherValue::getDescription() {
  switch (weather_code_) {
    case 0:
      return " Clear sky";
    case 1:
      return " Mainly clear";
    case 2:
      return " Partly cloudy";
    case 3:
      return " Overcast";
    case 45:
      return " Foggy";
    case 48:
      return " Rime fog";
    case 51:
      return " Light drizzle";
    case 53:
      return " Drizzle";
    case 55:
      return " Heavy drizzle";
    case 56:
      return " Light freezing drizzle";
    case 57:
      return " Freezing drizzle";
    case 61:
      return " Light rain";
    case 63:
      return " Rain";
    case 65:
      return " Heavy rain";
    case 66:
      return " Light freezing rain";
    case 67:
      return " Freezing rain";
    case 71:
      return " Light snow";
    case 73:
      return " Snow";
    case 75:
      return " Heavy snow";
    case 77:
      return " Snow grains";
    case 80:
      return " Light showers";
    case 81:
      return " Showers";
    case 82:
      return " Heavy showers";
    case 85:
      return " Light snow showers";
    case 86:
      return " Snow showers";
    case 95:
      return " Thunderstorm";
    case 96:
      return " Light thunderstome with hail";
    case 99:
      return " Thunderstorm with hail";
    default:
      return " Undefined weather";
  }
}

ftxui::Element WeatherValue::printArt() {
  using namespace ftxui;
  if (weather_code_ == 0 || weather_code_ == 1) {
    return vbox({
      text("    \\ . /    ") | color(Color::Yellow1),
      text("   - .-. -   ") | color(Color::Yellow1),
      text("  ‒ (   ) ‒  ") | color(Color::Yellow1),
      text("   . `-᾿ .   ") | color(Color::Yellow1),
      text("    / ' \\    ") | color(Color::Yellow1),
    });
  }

  if (weather_code_ == 2) {
    return vbox({
      text("   \\  /      ") | color(Color::Yellow1),
      hbox({text(" _ /\"\"") | color(Color::Yellow1),
        text(".-.    ")}),
      hbox({text("   \\_") | color(Color::Yellow1),
        text("(   ).  ")}),
      hbox({text("   /") | color(Color::Yellow1),
        text("(___(__) ")}),
        text("             ")});
  }

  if (weather_code_ == 3) {
    return vbox ({
      text("             "),
      text("     .--.    "),
      text("  .-(    ).  "),
      text(" (___.)) "),
      text("             "),
    });
  }

  if (weather_code_ == 45 || weather_code_ == 48) {
    return vbox ({
      text("             ") | color(Color::GrayLight),
      text(" _ - _ - _ - ") | color(Color::GrayLight),
      text("  _ - _ - _  ") | color(Color::GrayLight),
      text(" _ - _ - _ - ") | color(Color::GrayLight),
      text("             ") | color(Color::GrayLight),
    });
  }

  if (weather_code_ >= 51 && weather_code_ <= 61) {
    return vbox ({
      text("     .-.     ") | color(Color::GrayLight),
      text("    (   ).   ") | color(Color::GrayLight),
      text("   (___()  ") | color(Color::GrayLight),
      text("    ʻ ʻ ʻ ʻ  ") | color(Color::BlueLight),
      text("   ʻ ʻ ʻ ʻ   ") | color(Color::BlueLight),
    });
  }

  if (weather_code_ == 65) {
    return vbox ({
      text("     .-.     ") | color(Color::GrayLight),
      text("    (   ).   ") | color(Color::GrayLight),
      text("   (___()  ") | color(Color::GrayLight),
      text("  ‚ʻ‚ʻ‚ʻ‚ʻ   ") | color(Color::BlueLight),
      text("  ‚ʻ‚ʻ‚ʻ‚ʻ   ") | color(Color::BlueLight),
    });
  }

  if (weather_code_ == 66) {
    return vbox ({
      text("     .-.     ") | color(Color::GrayLight),
      text("    (   ).   ") | color(Color::GrayLight),
      text("   (___()  ") | color(Color::GrayLight),
      text("    ʻ * ʻ *  ") | color(Color::CyanLight),
      text("   * ʻ * ʻ   ") | color(Color::CyanLight),
    });
  }

  if (weather_code_ == 67) {
    return vbox({
      text(" _`/\"\".-.    ") | color(Color::GrayLight),
      text("  ,\\_(   ).  ") | color(Color::GrayLight),
      text("   /(___() ") | color(Color::GrayLight),
      text("     ʻ * ʻ * ") | color(Color::CyanLight),
      text("    * ʻ * ʻ  ") | color(Color::CyanLight),
    });
  }

  if (weather_code_ == 71 || weather_code_ == 73) {
    return vbox ({
      text("     .-.     ") | color(Color::GrayLight),
      text("    (   ).   ") | color(Color::GrayLight),
      text("   (___()  ") | color(Color::GrayLight),
      text("    *  *  *  ") | color(Color::CyanLight),
      text("   *  *  *   ") | color(Color::CyanLight),
      });
  }

  if (weather_code_ == 75) {
    return vbox ({
      text("     .-.     ") | color(Color::GrayDark),
      text("    (   ).   ") | color(Color::GrayDark),
      text("   (___()  ") | color(Color::GrayDark),
      text("   * * * *   ") | color(Color::CyanLight),
      text("  * * * *    ") | color(Color::CyanLight),
    });
  }

  if (weather_code_ == 77) {
    return vbox ({
      text("     .-.     ") | color(Color::GrayLight),
      text("    (   ).   ") | color(Color::GrayLight),
      text("   (___()  ") | color(Color::GrayLight),
      text("   • • •    ") | color(Color::CyanLight),
      text("  • • • •    ") | color(Color::CyanLight),
    });
  }

  if (weather_code_ == 80) {
    return vbox ({
      text(" _`/\"\".-.    ") | color(Color::GrayLight),
      text("  ,\\_(   ).  ") | color(Color::GrayLight),
      text("   /(___() ") | color(Color::GrayLight),
      text("     ʻ ʻ ʻ ʻ ") | color(Color::CyanLight),
      text("    ʻ ʻ ʻ ʻ  ") | color(Color::CyanLight),
    });
  }

  if (weather_code_ == 81 || weather_code_ == 82) {
    return vbox ({
      text(" _`/\"\".-.    ") | color(Color::GrayDark),
      text("  ,\\_(   ).  ") | color(Color::GrayDark),
      text("   /(___() ") | color(Color::GrayDark),
      text("   ‚ʻ‚ʻ‚ʻ‚ʻ  ") | color(Color::CyanLight),
      text("   ‚ʻ‚ʻ‚ʻ‚ʻ  ") | color(Color::CyanLight),        
    });
  }

  if (weather_code_ == 85) {
    return vbox ({
      text(" _`/\"\".-.    ") | color(Color::GrayLight),
      text("  ,\\_(   ).  ") | color(Color::GrayLight),
      text("   /(___() ") | color(Color::GrayLight),
      text("     *  *  * ") | color(Color::CyanLight),
      text("    *  *  *  ") | color(Color::CyanLight),
    });
  }

  if (weather_code_ == 86) {
    return vbox ({
      text(" _`/\"\".-.    ") | color(Color::GrayLight),
      text("  ,\\_(   ).  ") | color(Color::GrayLight),
      text("   /(___() ") | color(Color::GrayLight),
      text("    * * * *  ") | color(Color::CyanLight),
      text("   * * * *   ") | color(Color::CyanLight),
    });
  }

  if (weather_code_ == 95) {
    return vbox ({
      text("     .-.     ") | color(Color::GrayDark),
      text("    (   ).   ") | color(Color::GrayDark),
      text("   (___()  ") | color(Color::GrayDark),
      text("  ‚ʻ⚡️ʻ‚⚡️‚ʻ   ") | color(Color::CyanLight),
      text("  ‚ʻ‚ʻ⚡️ʻ‚ʻ   ") | color(Color::CyanLight),
    });
  }

  if (weather_code_ == 96 || weather_code_ == 99) {
    return vbox ({
      text(" _`/\"\".-.    ") | color(Color::GrayDark),
      text("  ,\\_(   ).  ") | color(Color::GrayDark),
      text("   /(___() ") | color(Color::GrayDark),
      text("    ⚡️ʻ •⚡️ʻ • ") | color(Color::CyanLight),
      text("    • ʻ • ʻ  ") | color(Color::CyanLight),
    });
  }

  return vbox ({
    text("    .-.      "),
    text("       )     "),
    text("    (        "),
    text("     `-᾿     "),
    text("      •      "),
  });
}

ftxui::Element City::outputWeatherAll() {
  using namespace ftxui;

  Elements elements;

  for (int i = 0; i < count_of_days_; i++) {
    elements.push_back(outputWeatherDay(i));
  }

  return vbox({elements});
}

ftxui::Element City::outputWeatherDay(int day) {
  using namespace ftxui;

  return window(
    text(getDate(day)) | hcenter | bold,
    hbox({
      vbox({text("Morning") | hcenter, separator(), weather_[kTimesOfDay * day].printDayWeather()}),
      separator(),
      vbox({text("Afternoon") | hcenter, separator(), weather_[kTimesOfDay * day + 1].printDayWeather()}),
      separator(),
      vbox({text("Evening") | hcenter, separator(), weather_[kTimesOfDay * day + 2].printDayWeather()}),
      separator(),
      vbox({text("Night") | hcenter, separator(), weather_[kTimesOfDay * day + 3].printDayWeather()}),
    }) | xflex_grow);
}

ftxui::Element City::outputWeatherCur() {
  using namespace ftxui;
  
  return vbox({
    text("Weather in the " + name_),
    text(""),
    current_.printDayWeather(),
    text(""),
  });
}
