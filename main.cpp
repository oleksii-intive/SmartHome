#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/alarm/AlarmManager.h"
#include "src/datetime/DateTimeSource.h"
#include "src/location/LocationSource.h"
#include "src/network/NetworkManager.h"
#include "src/settings/SettingsManager.h"
#include "src/weather/WeatherSource.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(maincpp, "main")

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  qRegisterMetaType<WeatherInfo>("WeatherInfo");
  qRegisterMetaType<QObjectList>("QObjectList");

  QGuiApplication app(argc, argv);

  DbManager dbManager;
  if (!dbManager.open()) {
    qCCritical(maincpp) << "Couldn't open database";
    return 0;
  }

  QQmlApplicationEngine engine;
  engine.addImportPath("qrc:///qml");
  DateTimeSource dateTimeSource;
  engine.rootContext()->setContextProperty("dateTimeSource", &dateTimeSource);
  NetworkManager networkManager;
  LocationSource locationSource(networkManager);
  engine.rootContext()->setContextProperty("locationSource", &locationSource);
  WeatherSource weatherSource(networkManager);
  QObject::connect(&locationSource, &LocationSource::coordinateChanged,
                   &weatherSource, &WeatherSource::updateWeather);
  engine.rootContext()->setContextProperty("weatherSource", &weatherSource);
  AlarmManager alarmManager(dbManager);
  engine.rootContext()->setContextProperty("alarmManager", &alarmManager);
  SettingsManager settingsManager(dbManager);
  QObject::connect(&settingsManager, &SettingsManager::languageChanged, &engine,
                   &QQmlApplicationEngine::retranslate);
  QObject::connect(&settingsManager, &SettingsManager::localeChanged,
                   &dateTimeSource, &DateTimeSource::processNewLocale);
  QObject::connect(&settingsManager, &SettingsManager::localeChanged,
                   &locationSource, &LocationSource::processNewLocale);
  settingsManager.updateTranslations();
  engine.rootContext()->setContextProperty("settingsManager", &settingsManager);
  const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
                   [url](QObject *obj, const QUrl &objUrl) {
                     if (!obj && url == objUrl) {
                       QCoreApplication::exit(-1);
                     }
                   },
                   Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
