#ifndef WEATHERINFO_H
#define WEATHERINFO_H

#include <QDateTime>
#include <QObject>

class WeatherInfo {
  Q_GADGET
  Q_PROPERTY(float temperature READ temperature CONSTANT)
  Q_PROPERTY(float pressure READ pressure CONSTANT)
  Q_PROPERTY(int humidity READ humidity CONSTANT)
  Q_PROPERTY(float windSpeed READ windSpeed CONSTANT)
  Q_PROPERTY(QString description READ description CONSTANT)
  Q_PROPERTY(QString icon READ icon CONSTANT)
  Q_PROPERTY(QString time READ time CONSTANT)

 public:
  WeatherInfo() = default;
  WeatherInfo(float temperature, float pressure, int humidity, float windSpeed,
              QString description, QString icon, qint64 timestamp)
      : mTemperature(temperature),
        mPressure(pressure),
        mHumidity(humidity),
        mWindSpeed(windSpeed),
        mDescription(description),
        mIcon(icon),
        mTimestamp(timestamp) {
    mTime = QDateTime::fromSecsSinceEpoch(mTimestamp).toString("HH:mm");
  }

  float temperature() const { return mTemperature; }
  float pressure() const { return mPressure; }
  int humidity() const { return mHumidity; }
  float windSpeed() const { return mWindSpeed; }
  QString description() const { return mDescription; }
  QString icon() const { return mIcon; }
  QString time() const { return mTime; }

 private:
  float mTemperature;
  float mPressure;
  int mHumidity;
  float mWindSpeed;
  QString mDescription;
  QString mIcon;
  qint64 mTimestamp;
  QString mTime;
};

#endif  // WEATHERINFO_H
