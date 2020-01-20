#include "AlarmObserver.h"

#include <QTimer>

#include "AlarmManager.h"

AlarmObserver::AlarmObserver(AlarmManager *alarmManager)
    : QObject(alarmManager), mAlarmManager(alarmManager) {
  auto seconds = QTime::currentTime().second();
  seconds = (seconds == 0) ? seconds : 60 - seconds;
  QTimer::singleShot(seconds * 1000, this, [this]() {
    checkAlarms();
    startTimer(60 * 1000);
  });
}

void AlarmObserver::addAlarm(AlarmData *alarm) {
  const auto time = alarm->time().toString("HH:mm");
  mTimeAlarmHash.insert(time, alarm);
  mIdTimeHash.insert(alarm->id(), time);
}

void AlarmObserver::removeAlarm(AlarmData *alarm) {
  mTimeAlarmHash.remove(alarm->time().toString("HH:mm"), alarm);
  mIdTimeHash.remove(alarm->id());
}

void AlarmObserver::updateAlarm(AlarmData *alarm) {
  const auto alarmTime = mIdTimeHash.value(alarm->id());
  const auto newTime = alarm->time().toString("HH:mm");
  if (alarmTime != newTime) {
    mTimeAlarmHash.remove(alarmTime, alarm);
    mTimeAlarmHash.insert(newTime, alarm);
  }
}

void AlarmObserver::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event)
  checkAlarms();
}

void AlarmObserver::checkAlarms() {
  if (mIdTimeHash.isEmpty()) {
    return;
  }

  const auto currentDateTime = QDateTime::currentDateTime();
  const auto currentTime = currentDateTime.time().toString("HH:mm");
  if (!mTimeAlarmHash.contains(currentTime)) {
    return;
  }

  int dayOfWeek = currentDateTime.date().dayOfWeek();
  auto alarms = mTimeAlarmHash.values(currentTime);
  bool needAlarm = false;
  for (auto alarm : alarms) {
    if (!alarm->isRepeat()) {
      alarm->setActive(false);
      mAlarmManager->updateAlarm(alarm);
      mTimeAlarmHash.remove(currentTime, alarm);
      mIdTimeHash.remove(alarm->id());
      needAlarm = true;
      continue;
    }

    if (needAlarm) {
      continue;
    }

    const auto days = alarm->days();
    if (days.contains(dayOfWeek)) {
      needAlarm = true;
    }
  }

  if (needAlarm) {
    mAlarmManager->startAlarm();
  }
}
