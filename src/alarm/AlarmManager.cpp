#include "AlarmManager.h"

#include <QTimer>

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(alarm, "alarm")

AlarmManager::AlarmManager(DbManager &dbManager, QObject *parent)
    : QObject(parent), mDbManager(dbManager) {
  const auto alarms = mDbManager.alarms();
  for (const auto &alarm : alarms) {
    auto alarmObject = new AlarmData(alarm, this);
    if (alarmObject->isActive()) {
      mAlarmObserver.addAlarm(alarmObject);
    }
    mAlarms.append(alarmObject);
  }

  mPlaylist.addMedia(QUrl("qrc:/resources/sound/alarm.mp3"));
  mPlaylist.setPlaybackMode(QMediaPlaylist::Loop);
  mPlayer.setPlaylist(&mPlaylist);
}

QObjectList AlarmManager::alarms() const { return mAlarms; }

void AlarmManager::addNewAlarm() {
  qCDebug(alarm) << "Adding new alarm";
  Alarm alarm;
  alarm.time = QTime::currentTime();
  alarm.active = true;
  alarm.repeat = false;
  if (mDbManager.addAlarm(alarm)) {
    mAlarms.append(new AlarmData(alarm, this));
    emit alarmsChanged();
  }
}

void AlarmManager::deleteAlarm(int index) {
  if (index < 0 || index >= mAlarms.size()) {
    return;
  }

  qCDebug(alarm) << "Removing alarm";
  auto alarm = qobject_cast<AlarmData *>(mAlarms.takeAt(index));
  if (mDbManager.removeAlarm(alarm->id())) {
    mAlarmObserver.removeAlarm(alarm);
    alarm->deleteLater();
    emit alarmsChanged();
  }
}

void AlarmManager::saveAlarmChanges(int index) {
  if (index < 0 || index >= mAlarms.size()) {
    return;
  }

  qCDebug(alarm) << "Saving alarm's changes";
  auto alarm = qobject_cast<AlarmData *>(mAlarms.at(index));
  if (alarm->isActive()) {
    mAlarmObserver.updateAlarm(alarm);
  }
  updateAlarm(alarm);
}

void AlarmManager::processActiveChanged(int index) {
  qCDebug(alarm) << "Processing alarm active change";
  auto alarm = qobject_cast<AlarmData *>(mAlarms.at(index));
  if (alarm->isActive()) {
    mAlarmObserver.addAlarm(alarm);
  } else {
    mAlarmObserver.removeAlarm(alarm);
  }
  updateAlarm(alarm);
}

void AlarmManager::startAlarm() {
  qCDebug(alarm) << "Starting alarm";
  emit timeForAlarm();
  mPlayer.play();
  QTimer::singleShot(59 * 1000, this, [this]() {
    if (mPlayer.state() == QMediaPlayer::PlayingState) {
      stopAlarm();
    }
  });
}

void AlarmManager::stopAlarm() {
  qCDebug(alarm) << "Stopping alarm";
  mPlayer.stop();
  emit timeToStopAlarm();
}

void AlarmManager::updateAlarm(AlarmData *alarm) {
  mDbManager.editAlarm(alarm->mAlarm);
}
