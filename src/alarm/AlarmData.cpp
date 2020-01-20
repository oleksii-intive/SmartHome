#include "AlarmData.h"

#include "DateUtils.h"

AlarmData::AlarmData(Alarm alarm, QObject *parent)
    : QObject(parent), mAlarm(std::move(alarm)) {
  connect(this, &AlarmData::repeatChanged, this,
          &AlarmData::repeatStringChanged);
  connect(this, &AlarmData::daysChanged, this, &AlarmData::repeatStringChanged);
}

QTime AlarmData::time() const { return mAlarm.time; }

void AlarmData::setTime(const QTime &time) {
  if (time == mAlarm.time) {
    return;
  }

  mAlarm.time = time;
  emit timeChanged();
}

bool AlarmData::isActive() const { return mAlarm.active; }

void AlarmData::setActive(bool active) {
  if (active == mAlarm.active) {
    return;
  }

  mAlarm.active = active;
  emit activeChanged();
}

bool AlarmData::isRepeat() const { return mAlarm.repeat; }

void AlarmData::setRepeat(bool repeat) {
  if (repeat == mAlarm.repeat) {
    return;
  }

  mAlarm.repeat = repeat;
  emit repeatChanged();
}

QString AlarmData::repeatAsString() const {
  if (mAlarm.repeat) {
    QString result;
    for (const int day : mAlarm.days) {
      result.append(DateUtils::getDayName(day) + QStringLiteral(" "));
    }
    result.chop(1);
    return result;
  }

  return tr("No");
}

QList<int> AlarmData::days() const { return mAlarm.days; }

void AlarmData::setDays(const QList<int> &days) {
  if (mAlarm.days == days) {
    return;
  }

  mAlarm.days = days;
  emit daysChanged();
}

int AlarmData::id() const { return mAlarm.id; }
