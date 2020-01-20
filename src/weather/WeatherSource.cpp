#include "WeatherSource.h"

#include <QUrlQuery>

#include "src/network/NetworkManager.h"

WeatherSource::WeatherSource(const NetworkManager &networkManager,
                             QObject *parent)
    : QObject(parent), mNetworkManager(networkManager) {
  mWeatherForecastModel = std::make_unique<WeatherForecastModel>();
  connect(&mNetworkManager, &NetworkManager::weatherFetched, this,
          &WeatherSource::onWeatherFetched);
  connect(&mNetworkManager, &NetworkManager::weatherForecastFetched, this,
          &WeatherSource::onWeatherForecastFetched);
}

WeatherInfo WeatherSource::weatherInfo() const { return mWeatherInfo; }

WeatherForecastModel *WeatherSource::weatherForecast() const {
  return mWeatherForecastModel.get();
}

void WeatherSource::updateWeather(const QGeoCoordinate &geoCoordinate) {
  if (mNetworkManager.isNetworkReady()) {
    mNetworkManager.fetchWeatherInfo(geoCoordinate.latitude(),
                                     geoCoordinate.longitude());
  }
}

void WeatherSource::onWeatherFetched(const WeatherInfo &weatherInfo) {
  mWeatherInfo = weatherInfo;
  emit weatherInfoChanged();
}

void WeatherSource::onWeatherForecastFetched(
    const QVector<WeatherInfo> &weatherForecast) {
  mWeatherForecastModel->setModel(weatherForecast);
  emit weatherForecastChanged();
}
