#include "WeatherForecastModel.h"

WeatherForecastModel::WeatherForecastModel(QObject *parent)
    : QAbstractListModel(parent) {}

int WeatherForecastModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
  }

  return mWeatherForecast.size();
}

QVariant WeatherForecastModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= mWeatherForecast.size()) return {};

  if (role != Weather) {
    return {};
  }

  return QVariant::fromValue(mWeatherForecast.at(index.row()));
}

QHash<int, QByteArray> WeatherForecastModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[Weather] = "weather";
  return roles;
}

void WeatherForecastModel::setModel(
    const QVector<WeatherInfo> &weatherForecast) {
  beginResetModel();
  mWeatherForecast = weatherForecast;
  endResetModel();
}
