#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

#include "Alarm.h"
#include "Settings.h"

class DbManager {
 public:
  DbManager() = default;
  ~DbManager();

  bool open();
  void close();

  QList<Alarm> alarms() const;
  bool addAlarm(Alarm &alarm);
  bool removeAlarm(int id);
  bool editAlarm(const Alarm &alarm);

  Settings settings() const;
  bool editSettings(const Settings &settings);

 private:
  bool hasTablesStructure();
  bool createTables();

  QSqlDatabase mDb;
  const int mUserTablesCount = 3;
};

#endif  // DBMANAGER_H
