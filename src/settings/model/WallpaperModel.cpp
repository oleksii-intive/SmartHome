#include "WallpaperModel.h"

WallpaperModel::WallpaperModel(QObject *parent) : QAbstractListModel(parent) {
  mWallpapers = {
      Wallpaper(tr("Wallpaper 1"), "qrc:/resources/wallpaper/1.jpg"),
      Wallpaper(tr("Wallpaper 2"), "qrc:/resources/wallpaper/2.jpg"),
      Wallpaper(tr("Wallpaper 3"), "qrc:/resources/wallpaper/3.jpg"),
      Wallpaper(tr("Wallpaper 4"), "qrc:/resources/wallpaper/4.jpg")};
}

int WallpaperModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
  }

  return mWallpapers.count();
}

QVariant WallpaperModel::data(const QModelIndex &index, int role) const {
  const auto row = index.row();
  if (row < 0 || row >= mWallpapers.size()) {
    return {};
  }

  if (role == Name) {
    return mWallpapers.at(row).name();
  }

  return {};
}

QHash<int, QByteArray> WallpaperModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[Name] = "name";
  return roles;
}

int WallpaperModel::indexOf(const QString &url) const {
  int i = 0;
  while (i < mWallpapers.count()) {
    const auto &wallpaper = mWallpapers.at(i);
    if (wallpaper.url() == url) {
      return i;
    }
    ++i;
  }

  return 0;
}

QString WallpaperModel::url(int row) const {
  if (row < 0 || row >= mWallpapers.size()) {
    return {};
  }

  return mWallpapers.at(row).url();
}

void WallpaperModel::retranslate() {
  mWallpapers = {
      Wallpaper(tr("Wallpaper 1"), "qrc:/resources/wallpaper/1.jpg"),
      Wallpaper(tr("Wallpaper 2"), "qrc:/resources/wallpaper/2.jpg"),
      Wallpaper(tr("Wallpaper 3"), "qrc:/resources/wallpaper/3.jpg"),
      Wallpaper(tr("Wallpaper 4"), "qrc:/resources/wallpaper/4.jpg")};
  emit dataChanged(index(0), index(mWallpapers.count() - 1), {Name});
}
