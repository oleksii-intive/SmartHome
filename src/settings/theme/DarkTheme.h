#ifndef DARKTHEME_H
#define DARKTHEME_H

#include "AbstractTheme.h"

class DarkTheme : public AbstractTheme {
 public:
  DarkTheme(QObject *parent) : AbstractTheme(parent) {}

  QColor overlayBg() const override;
  QColor semitransparentBg() const override;
  QColor fontColor() const override;
  QColor checkedFontColor() const override;
  QColor iconColor() const override;
  QColor smallIconColor() const override;
  QColor separatorColor() const override;
  QColor controlColor() const override;
  QColor controlBg() const override;
  QColor popupBg() const override;
  QColor popupBorder() const override;
  QColor popupFontColor() const override;
  QColor popupCheckedFontColor() const override;
  QColor popupIconColor() const override;
  QColor popupControlColor() const override;
  QColor popupControlBg() const override;
  QString mapStyle() const override;
  QColor mapControlColor() const override;
  QColor locationMarkColor() const override;
  QColor locationMarkBorder() const override;
  QColor locationMarkShadow() const override;
  QColor highlightColor() const override;
  QColor itemBg() const override;
  QColor selectedBg() const override;
  QColor todayBg() const override;
};

#endif  // DARKTHEME_H
