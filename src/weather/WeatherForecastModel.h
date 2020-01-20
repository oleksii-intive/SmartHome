#ifndef WEATHERFORECASTMODEL_H
#define WEATHERFORECASTMODEL_H

#include <QAbstractListModel>

#include "WeatherInfo.h"

class WeatherForecastModel : public QAbstractListModel {
  Q_OBJECT
 public:
  enum WeatherRoles {
    Weather = Qt::UserRole + 1,
  };

  explicit WeatherForecastModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

  void setModel(const QVector<WeatherInfo> &weatherForecast);

 private:
  QVector<WeatherInfo> mWeatherForecast;
};

#endif  // WEATHERFORECASTMODEL_H
