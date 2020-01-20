#ifndef ALARM_H
#define ALARM_H

#include <QTime>

struct Alarm {
  int id;
  QTime time;
  bool active;
  bool repeat;
  QList<int> days;

  void daysFromString(const QString &string) {
    if (string.isEmpty()) {
      return;
    }
    const auto daysList = string.split(QStringLiteral(","));
    bool ok;
    for (const auto &dayItem : daysList) {
      ok = false;
      int day = dayItem.toInt(&ok);
      if (ok) {
        days.append(day);
      }
    }
  }

  QString daysToString() const {
    QString result;
    for (const auto &day : days) {
      result.append(QString::number(day) + QStringLiteral(","));
    }
    result.chop(1);
    return result;
  }
};

#endif  // ALARM_H
