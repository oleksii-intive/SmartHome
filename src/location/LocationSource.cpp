#include "LocationSource.h"

#include "src/network/NetworkManager.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(locationSource, "location")

static const double DefaultLatitude = 52.520008;
static const double DefaultLongitude = 13.404954;

LocationSource::LocationSource(NetworkManager &networkManager, QObject *parent)
    : QObject(parent), mNetworkManager(networkManager) {
  connect(&mNetworkManager, &NetworkManager::networkReady, this,
          &LocationSource::onNetworkReady);
  connect(&mNetworkManager, &NetworkManager::locationFetched, this,
          &LocationSource::onLocationFetched);
  connect(this, &LocationSource::coordinateChanged, this,
          &LocationSource::fetchLocation);

  if (mNetworkManager.isNetworkReady()) {
    onNetworkReady();
  }
}

QGeoCoordinate LocationSource::coordinate() const { return mGeoCoordinate; }

void LocationSource::onNetworkReady() {
  mGeoPositionSource = std::unique_ptr<QGeoPositionInfoSource>(
      QGeoPositionInfoSource::createDefaultSource(this));

  if (mGeoPositionSource) {
    connect(mGeoPositionSource.get(), &QGeoPositionInfoSource::positionUpdated,
            this, &LocationSource::updateLocation);
    connect(mGeoPositionSource.get(),
            qOverload<QGeoPositionInfoSource::Error>(
                &QGeoPositionInfoSource::error),
            this, &LocationSource::processGeoError);
    mGeoPositionSource->startUpdates();
  } else {
    mLocation.clear();
    mGeoCoordinate.setLatitude(DefaultLatitude);
    mGeoCoordinate.setLongitude(DefaultLongitude);
    emit coordinateChanged(mGeoCoordinate);
  }
}

void LocationSource::updateLocation(const QGeoPositionInfo &info) {
  mGeoCoordinate = info.coordinate();
  emit coordinateChanged(mGeoCoordinate);
}

void LocationSource::processGeoError(QGeoPositionInfoSource::Error error) {
  qCWarning(locationSource) << "geo position source is unavailable" << error;
  mGeoPositionSource->stopUpdates();
  mLocation.clear();
  mGeoCoordinate.setLatitude(DefaultLatitude);
  mGeoCoordinate.setLongitude(DefaultLongitude);
  emit coordinateChanged(mGeoCoordinate);
}

void LocationSource::fetchLocation() {
  qCDebug(locationSource) << "requested query of city";

  mNetworkManager.fetchLocation(mGeoCoordinate.latitude(),
                                mGeoCoordinate.longitude(),
                                mLocale.bcp47Name());
}

void LocationSource::onLocationFetched(const QString &location) {
  if (mLocation == location) {
    return;
  }
  mLocation = location;
  emit locationChanged();
}

QString LocationSource::location() const { return mLocation; }

void LocationSource::processNewLocale(const QLocale &locale) {
  mLocale = locale;
  fetchLocation();
}
