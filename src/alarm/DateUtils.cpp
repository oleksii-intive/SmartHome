#include "DateUtils.h"

#include <QObject>
#include <QStringList>

namespace DateUtils {
QString getDayName(int dayNumber) {
  if (dayNumber < 0 || dayNumber > 7) {
    return {};
  }

  static QStringList weekDays = {"",
                                 QObject::tr("Mon"),
                                 QObject::tr("Tue"),
                                 QObject::tr("Wed"),
                                 QObject::tr("Thu"),
                                 QObject::tr("Fri"),
                                 QObject::tr("Sat"),
                                 QObject::tr("Sun")};
  return weekDays.at(dayNumber);
}
}  // namespace DateUtils
