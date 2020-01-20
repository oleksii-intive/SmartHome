#include "ThemeModel.h"

#include "src/settings/theme/DarkTheme.h"
#include "src/settings/theme/LightTheme.h"

ThemeModel::ThemeModel(QObject *parent) : QAbstractListModel(parent) {
  mThemes = {tr("Light"), tr("Dark")};
}

int ThemeModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
  }

  return mThemes.count();
}

QVariant ThemeModel::data(const QModelIndex &index, int role) const {
  const auto row = index.row();
  if (row < 0 || row >= mThemes.size()) {
    return {};
  }

  if (role == Name) {
    return mThemes.at(row);
  }

  return {};
}

QHash<int, QByteArray> ThemeModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[Name] = "name";
  return roles;
}

void ThemeModel::retranslate() {
  mThemes = {tr("Light"), tr("Dark")};
  emit dataChanged(index(0), index(mThemes.count() - 1), {Name});
}

AbstractTheme *ThemeModel::instantiateTheme(ThemeStyle style) {
  switch (style) {
    case ThemeStyle::Light:
      return new LightTheme(this);
    case ThemeStyle::Dark:
      return new DarkTheme(this);
  }
}
