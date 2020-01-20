#ifndef WEATHERSOURCE_H
#define WEATHERSOURCE_H

#include <QGeoCoordinate>
#include <QObject>
#include <QQmlListProperty>
#include <QVector>

#include <memory>

#include "WeatherForecastModel.h"
#include "WeatherInfo.h"

class NetworkManager;

class WeatherSource : public QObject {
  Q_OBJECT
  Q_PROPERTY(WeatherInfo weatherInfo READ weatherInfo NOTIFY weatherInfoChanged)
  Q_PROPERTY(WeatherForecastModel *weatherForecast READ weatherForecast NOTIFY
                 weatherForecastChanged)
 public:
  explicit WeatherSource(const NetworkManager &networkManager,
                         QObject *parent = nullptr);

  WeatherInfo weatherInfo() const;
  WeatherForecastModel *weatherForecast() const;

  void updateWeather(const QGeoCoordinate &geoCoordinate);

 signals:
  void weatherInfoChanged();
  void weatherForecastChanged();

 private:
  void onWeatherFetched(const WeatherInfo &weatherInfo);
  void onWeatherForecastFetched(const QVector<WeatherInfo> &weatherForecast);

  const NetworkManager &mNetworkManager;
  WeatherInfo mWeatherInfo;
  std::unique_ptr<WeatherForecastModel> mWeatherForecastModel;
};

#endif  // WEATHERSOURCE_H
