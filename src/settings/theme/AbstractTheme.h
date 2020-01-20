#ifndef ABSTRACTTHEME_H
#define ABSTRACTTHEME_H

#include <QObject>

#include <QColor>

class AbstractTheme : public QObject {
  Q_OBJECT
  // General
  Q_PROPERTY(QColor overlayBg READ overlayBg CONSTANT)
  Q_PROPERTY(QColor semitransparentBg READ semitransparentBg CONSTANT)
  Q_PROPERTY(QColor fontColor READ fontColor CONSTANT)
  Q_PROPERTY(QColor checkedFontColor READ checkedFontColor CONSTANT)
  Q_PROPERTY(QColor iconColor READ iconColor CONSTANT)
  Q_PROPERTY(QColor smallIconColor READ smallIconColor CONSTANT)
  Q_PROPERTY(QColor separatorColor READ separatorColor CONSTANT)
  Q_PROPERTY(QColor controlColor READ controlColor CONSTANT)
  Q_PROPERTY(QColor controlBg READ controlBg CONSTANT)
  Q_PROPERTY(QColor popupBg READ popupBg CONSTANT)
  Q_PROPERTY(QColor popupBorder READ popupBorder CONSTANT)
  Q_PROPERTY(QColor popupFontColor READ popupFontColor CONSTANT)
  Q_PROPERTY(QColor popupCheckedFontColor READ popupCheckedFontColor CONSTANT)
  Q_PROPERTY(QColor popupIconColor READ popupIconColor CONSTANT)
  Q_PROPERTY(QColor popupControlColor READ popupControlColor CONSTANT)
  Q_PROPERTY(QColor popupControlBg READ popupControlBg CONSTANT)
  // TrafficPage
  Q_PROPERTY(QString mapStyle READ mapStyle CONSTANT)
  Q_PROPERTY(QColor mapControlColor READ mapControlColor CONSTANT)
  Q_PROPERTY(QColor locationMarkColor READ locationMarkColor CONSTANT)
  Q_PROPERTY(QColor locationMarkBorder READ locationMarkBorder CONSTANT)
  Q_PROPERTY(QColor locationMarkShadow READ locationMarkShadow CONSTANT)
  // AlarmPage
  Q_PROPERTY(QColor highlightColor READ highlightColor CONSTANT)
  // CalendarPage
  Q_PROPERTY(QColor itemBg READ itemBg CONSTANT)
  Q_PROPERTY(QColor selectedBg READ selectedBg CONSTANT)
  Q_PROPERTY(QColor todayBg READ todayBg CONSTANT)
 public:
  AbstractTheme(QObject *parent) : QObject(parent) {}

  virtual QColor overlayBg() const = 0;
  virtual QColor semitransparentBg() const = 0;
  virtual QColor fontColor() const = 0;
  virtual QColor checkedFontColor() const = 0;
  virtual QColor iconColor() const = 0;
  virtual QColor smallIconColor() const = 0;
  virtual QColor separatorColor() const = 0;
  virtual QColor controlColor() const = 0;
  virtual QColor controlBg() const = 0;
  virtual QColor popupBg() const = 0;
  virtual QColor popupBorder() const = 0;
  virtual QColor popupFontColor() const = 0;
  virtual QColor popupCheckedFontColor() const = 0;
  virtual QColor popupIconColor() const = 0;
  virtual QColor popupControlColor() const = 0;
  virtual QColor popupControlBg() const = 0;
  virtual QString mapStyle() const = 0;
  virtual QColor mapControlColor() const = 0;
  virtual QColor locationMarkColor() const = 0;
  virtual QColor locationMarkBorder() const = 0;
  virtual QColor locationMarkShadow() const = 0;
  virtual QColor highlightColor() const = 0;
  virtual QColor itemBg() const = 0;
  virtual QColor selectedBg() const = 0;
  virtual QColor todayBg() const = 0;
};

#endif  // ABSTRACTTHEME_H
