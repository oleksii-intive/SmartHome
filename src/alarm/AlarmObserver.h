#ifndef ALARMOBSERVER_H
#define ALARMOBSERVER_H

#include <QObject>

#include "AlarmData.h"

class AlarmManager;

class AlarmObserver : public QObject {
  Q_GADGET
 public:
  explicit AlarmObserver(AlarmManager *alarmManager);

  void addAlarm(AlarmData *alarm);
  void removeAlarm(AlarmData *alarm);
  void updateAlarm(AlarmData *alarm);

 protected:
  void timerEvent(QTimerEvent *event) override;

 private:
  void checkAlarms();

  AlarmManager *mAlarmManager;
  QMultiHash<QString, AlarmData *> mTimeAlarmHash;
  QHash<int, QString> mIdTimeHash;
};

#endif  // ALARMOBSERVER_H
