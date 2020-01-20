#include "LightTheme.h"

QColor LightTheme::overlayBg() const { return QStringLiteral("#40000000"); }

QColor LightTheme::semitransparentBg() const {
  return QStringLiteral("#80000000");
}

QColor LightTheme::fontColor() const { return QStringLiteral("#ffffff"); }

QColor LightTheme::checkedFontColor() const {
  return QStringLiteral("#40ffffff");
}

QColor LightTheme::iconColor() const { return QStringLiteral("#ffffff"); }

QColor LightTheme::smallIconColor() const { return QStringLiteral("#ffffff"); }

QColor LightTheme::separatorColor() const { return QStringLiteral("#ffffff"); }

QColor LightTheme::controlColor() const { return QStringLiteral("#ffffff"); }

QColor LightTheme::controlBg() const { return QStringLiteral("#333333"); }

QColor LightTheme::popupBg() const { return QStringLiteral("#fff5ee"); }

QColor LightTheme::popupBorder() const { return QStringLiteral("#333333"); }

QColor LightTheme::popupFontColor() const { return QStringLiteral("#333333"); }

QColor LightTheme::popupCheckedFontColor() const {
  return QStringLiteral("#40333333");
}

QColor LightTheme::popupIconColor() const { return QStringLiteral("#333333"); }

QColor LightTheme::popupControlColor() const {
  return QStringLiteral("#333333");
}

QColor LightTheme::popupControlBg() const { return QStringLiteral("#fff5ee"); }

QString LightTheme::mapStyle() const {
  return QStringLiteral("mapbox://styles/mapbox/navigation-preview-day-v2");
}

QColor LightTheme::mapControlColor() const { return QStringLiteral("#0000ff"); }

QColor LightTheme::locationMarkColor() const {
  return QStringLiteral("#0000ff");
}

QColor LightTheme::locationMarkBorder() const {
  return QStringLiteral("#ffffff");
}

QColor LightTheme::locationMarkShadow() const {
  return QStringLiteral("#600000ff");
}

QColor LightTheme::highlightColor() const {
  return QStringLiteral("#4000ffff");
}

QColor LightTheme::itemBg() const { return QStringLiteral("#ffffff"); }

QColor LightTheme::selectedBg() const { return QStringLiteral("#f095c8d8"); }

QColor LightTheme::todayBg() const { return QStringLiteral("#f050c878"); }
