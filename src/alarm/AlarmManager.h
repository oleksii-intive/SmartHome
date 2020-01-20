#ifndef ALARMMANAGER_H
#define ALARMMANAGER_H

#include <QObject>

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "src/database/DbManager.h"

#include "AlarmData.h"
#include "AlarmObserver.h"

class AlarmManager : public QObject {
  Q_OBJECT
  Q_PROPERTY(QObjectList alarms READ alarms NOTIFY alarmsChanged)
 public:
  explicit AlarmManager(DbManager &dbManager, QObject *parent = nullptr);

  QObjectList alarms() const;

  Q_INVOKABLE void addNewAlarm();
  Q_INVOKABLE void deleteAlarm(int index);
  Q_INVOKABLE void saveAlarmChanges(int index);
  Q_INVOKABLE void processActiveChanged(int index);

  void startAlarm();
  Q_INVOKABLE void stopAlarm();

  void updateAlarm(AlarmData *alarm);

 signals:
  void alarmsChanged();
  void timeForAlarm();
  void timeToStopAlarm();

 private:
  DbManager &mDbManager;
  QObjectList mAlarms;
  AlarmObserver mAlarmObserver{this};
  QMediaPlayer mPlayer;
  QMediaPlaylist mPlaylist;
};

#endif  // ALARMMANAGER_H
