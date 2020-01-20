#ifndef ALARMDATA_H
#define ALARMDATA_H

#include <QObject>
#include <QTime>

#include "src/database/Alarm.h"

class AlarmData : public QObject {
  Q_OBJECT
  Q_PROPERTY(QTime time READ time WRITE setTime NOTIFY timeChanged)
  Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
  Q_PROPERTY(bool repeat READ isRepeat WRITE setRepeat NOTIFY repeatChanged)
  Q_PROPERTY(
      QString repeatAsString READ repeatAsString NOTIFY repeatStringChanged)
  Q_PROPERTY(QList<int> days READ days WRITE setDays NOTIFY daysChanged)

 public:
  explicit AlarmData(Alarm alarm, QObject *parent = nullptr);

  QTime time() const;
  void setTime(const QTime &time);

  bool isActive() const;
  void setActive(bool active);

  bool isRepeat() const;
  void setRepeat(bool repeat);
  QString repeatAsString() const;

  QList<int> days() const;
  void setDays(const QList<int> &days);

  int id() const;

 signals:
  void timeChanged();
  void activeChanged();
  void repeatChanged();
  void repeatStringChanged();
  void daysChanged();

 private:
  friend class AlarmManager;
  Alarm mAlarm;
};

#endif  // ALARMDATA_H
