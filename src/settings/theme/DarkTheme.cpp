#include "DarkTheme.h"

QColor DarkTheme::overlayBg() const { return QStringLiteral("#40ffffff"); }

QColor DarkTheme::semitransparentBg() const {
  return QStringLiteral("#80ffffff");
}

QColor DarkTheme::fontColor() const { return QStringLiteral("#333333"); }

QColor DarkTheme::checkedFontColor() const {
  return QStringLiteral("#40333333");
}

QColor DarkTheme::iconColor() const { return QStringLiteral("#333333"); }

QColor DarkTheme::smallIconColor() const { return QStringLiteral("#333333"); }

QColor DarkTheme::separatorColor() const { return QStringLiteral("#333333"); }

QColor DarkTheme::controlColor() const { return QStringLiteral("#333333"); }

QColor DarkTheme::controlBg() const { return QStringLiteral("#ffffff"); }

QColor DarkTheme::popupBg() const { return QStringLiteral("#333333"); }

QColor DarkTheme::popupBorder() const { return QStringLiteral("#ffffff"); }

QColor DarkTheme::popupFontColor() const { return QStringLiteral("#ffffff"); }

QColor DarkTheme::popupCheckedFontColor() const {
  return QStringLiteral("#40ffffff");
}

QColor DarkTheme::popupIconColor() const { return QStringLiteral("#ffffff"); }

QColor DarkTheme::popupControlColor() const {
  return QStringLiteral("#ffffff");
}

QColor DarkTheme::popupControlBg() const { return QStringLiteral("#333333"); }

QString DarkTheme::mapStyle() const {
  return QStringLiteral("mapbox://styles/mapbox/navigation-preview-night-v2");
}

QColor DarkTheme::mapControlColor() const { return QStringLiteral("#ffffff"); }

QColor DarkTheme::locationMarkColor() const {
  return QStringLiteral("#ffffff");
}

QColor DarkTheme::locationMarkBorder() const {
  return QStringLiteral("#333333");
}

QColor DarkTheme::locationMarkShadow() const {
  return QStringLiteral("#60ffffff");
}

QColor DarkTheme::highlightColor() const { return QStringLiteral("#400080ff"); }

QColor DarkTheme::itemBg() const { return QStringLiteral("#3e424b"); }

QColor DarkTheme::selectedBg() const { return QStringLiteral("#f0588bae"); }

QColor DarkTheme::todayBg() const { return QStringLiteral("#f0679267"); }
