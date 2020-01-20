#include "DateTimeSource.h"

#include <QDateTime>
#include <QLocale>
#include <QTimer>

DateTimeSource::DateTimeSource(QObject *parent) : QObject(parent) {
  updateDateTime();
  auto seconds = QTime::currentTime().second();
  seconds = (seconds == 0) ? seconds : 60 - seconds;
  QTimer::singleShot(seconds * 1000, this, [this]() { startTimer(60 * 1000); });
}

QString DateTimeSource::date() const { return mDate; }

int DateTimeSource::month() const { return mMonth; }

int DateTimeSource::year() const { return mYear; }

void DateTimeSource::processNewLocale(const QLocale &locale) {
  mLocale = locale;
  const auto date = QDate::currentDate();
  mDate = QStringLiteral("%1, %2").arg(
      mLocale.dayName(date.dayOfWeek(), QLocale::ShortFormat),
      date.toString("d/M/yy"));
  emit dateChanged();
}

QString DateTimeSource::time() const { return mTime; }

void DateTimeSource::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event)
  updateDateTime();
}

void DateTimeSource::updateDateTime() {
  const auto dateTime = QDateTime::currentDateTime();
  const auto time = dateTime.time();
  if (time.minute() == mMinutes) {
    return;
  }

  mMinutes = time.minute();
  mTime = time.toString("HH:mm");
  emit timeChanged();

  if (mDate.isEmpty() || (mMinutes == 0 && time.hour() == 0)) {
    const auto date = dateTime.date();
    mDate = QStringLiteral("%1, %2").arg(
        mLocale.dayName(date.dayOfWeek(), QLocale::ShortFormat),
        date.toString("d/M/yy"));
    mMonth = date.month();
    mYear = date.year();
    emit dateChanged();
  }
}
