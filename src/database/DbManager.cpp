#include "DbManager.h"

#include <QSqlError>
#include <QSqlQuery>

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(db, "db")

DbManager::~DbManager() {
  if (mDb.isOpen()) {
    close();
  }
}

bool DbManager::open() {
  qCDebug(db) << "Opening database";
  mDb = QSqlDatabase::addDatabase("QSQLITE");
  mDb.setDatabaseName("settings.db");
  bool ok = mDb.open();
  if (!ok) {
    qCCritical(db) << "Couldn't open database" << mDb.lastError().text();
    return false;
  }

  if (!hasTablesStructure()) {
    return createTables();
  }

  return true;
}

void DbManager::close() {
  qCDebug(db) << "Closinging database";
  mDb.close();
}

QList<Alarm> DbManager::alarms() const {
  qCDebug(db) << "Select alarms";
  QSqlQuery query("SELECT id, time, active, repeat, days FROM alarm");
  if (!query.exec()) {
    qCCritical(db) << "Couldn't select alarms" << query.lastError().text();
    return {};
  }

  QList<Alarm> alarms;
  while (query.next()) {
    Alarm alarm;
    alarm.id = query.value(0).toInt();
    alarm.time = QTime::fromString(query.value(1).toString(), "HH:mm");
    alarm.active = query.value(2).toBool();
    alarm.repeat = query.value(3).toBool();
    alarm.daysFromString(query.value(4).toString());
    alarms.append(alarm);
  }

  return alarms;
}

bool DbManager::addAlarm(Alarm &alarm) {
  qCDebug(db) << "Add alarm";
  QSqlQuery query;
  query.prepare(
      "INSERT INTO alarm (time, active, repeat, days) VALUES (:time, :active, "
      ":repeat, :days)");
  query.bindValue(":time", alarm.time.toString("HH:mm"));
  query.bindValue(":active", alarm.active);
  query.bindValue(":repeat", alarm.repeat);
  query.bindValue(":days", alarm.daysToString());
  if (!query.exec()) {
    qCCritical(db) << "Couldn't add new alarm" << query.lastError().text();
    return false;
  }

  const auto id = query.lastInsertId();
  if (!id.isValid()) {
    qCCritical(db) << "Last inserted id is invalid";
    return false;
  }

  alarm.id = id.toInt();
  return true;
}

bool DbManager::removeAlarm(int id) {
  qCDebug(db) << "Remove alarm";
  QSqlQuery query;
  query.prepare("DELETE FROM alarm WHERE id=:id");
  query.bindValue(":id", id);
  if (!query.exec()) {
    qCCritical(db) << "Couldn't remove alarm by id" << id
                   << query.lastError().text();
    return false;
  }

  return true;
}

bool DbManager::editAlarm(const Alarm &alarm) {
  qCDebug(db) << "Edit alarm";
  QSqlQuery query;
  query.prepare(
      "UPDATE alarm SET time=:time, active=:active, repeat=:repeat, days=:days "
      "WHERE id=:id");
  query.bindValue(":id", alarm.id);
  query.bindValue(":time", alarm.time.toString("HH:mm"));
  query.bindValue(":active", alarm.active);
  query.bindValue(":repeat", alarm.repeat);
  query.bindValue(":days", alarm.daysToString());
  if (!query.exec()) {
    qCCritical(db) << "Couldn't update alarm with id" << alarm.id
                   << query.lastError().text();
    return false;
  }

  return true;
}

Settings DbManager::settings() const {
  qCDebug(db) << "Select settings";
  QSqlQuery query("SELECT id, wallpaper, theme, language FROM setting");
  if (!query.exec()) {
    qCCritical(db) << "Couldn't select settings" << query.lastError().text();
    return {};
  }

  if (query.next()) {
    Settings settings;
    settings.id = query.value(0).toInt();
    settings.wallpaper = query.value(1).toString();
    settings.theme = query.value(2).toInt();
    settings.language = query.value(3).toString();
    return settings;
  }

  qCCritical(db) << "No settings available";
  return {};
}

bool DbManager::editSettings(const Settings &settings) {
  qCDebug(db) << "Edit settings";
  QSqlQuery query;
  query.prepare(
      "UPDATE setting SET wallpaper=:wallpaper, theme=:theme, "
      "language=:language WHERE id=:id");
  query.bindValue(":id", settings.id);
  query.bindValue(":wallpaper", settings.wallpaper);
  query.bindValue(":theme", settings.theme);
  query.bindValue(":language", settings.language);
  if (!query.exec()) {
    qCCritical(db) << "Couldn't update setting with id" << settings.id
                   << query.lastError().text();
    return false;
  }

  return true;
}

bool DbManager::hasTablesStructure() {
  qCDebug(db) << "Checking db tables structure";
  QSqlQuery query(
      "SELECT count(*) FROM sqlite_master WHERE type='table' AND name IN "
      "('user','alarm','setting')");
  if (!query.exec()) {
    qCCritical(db) << "Couldn't request tables count"
                   << query.lastError().text();
    return false;
  }

  if (query.next()) {
    const auto tablesCount = query.value(0).toInt();
    return tablesCount == mUserTablesCount;
  }

  return false;
}

bool DbManager::createTables() {
  qCDebug(db) << "Creating tables";
  QSqlQuery query;
  if (!query.exec("CREATE TABLE user ("
                  " id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  " login TEXT NOT NULL,"
                  " password TEXT NOT NULL"
                  ")")) {
    qCCritical(db) << "Couldn't create user table" << query.lastError().text();
    return false;
  }

  if (!query.exec("CREATE TABLE alarm ("
                  " id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  " time TEXT NOT NULL,"
                  " active NUMERIC NOT NULL,"
                  " repeat NUMERIC NOT NULL,"
                  " days TEXT"
                  ")")) {
    qCCritical(db) << "Couldn't create alarm table" << query.lastError().text();
    return false;
  }

  if (!query.exec("CREATE TABLE setting ("
                  " id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  " wallpaper TEXT NOT NULL,"
                  " theme INTEGER NOT NULL,"
                  " language TEXT NOT NULL"
                  ")")) {
    qCCritical(db) << "Couldn't create setting table"
                   << query.lastError().text();
    return false;
  }

  if (!query.exec("INSERT INTO setting (wallpaper, theme, language) VALUES "
                  "('qrc:/resources/wallpaper/4.jpg', 0, 'en_US')")) {
    qCCritical(db) << "Couldn't insert default setting"
                   << query.lastError().text();
    return false;
  }

  return true;
}
