#ifndef WALLPAPERMODEL_H
#define WALLPAPERMODEL_H

#include <QAbstractListModel>

struct Wallpaper {
 public:
  Wallpaper(QString name, QString url)
      : mName(std::move(name)), mUrl(std::move(url)) {}

  QString name() const { return mName; }
  QString url() const { return mUrl; }

 private:
  QString mName;
  QString mUrl;
};

class WallpaperModel : public QAbstractListModel {
  Q_OBJECT

 public:
  enum WallpaperRoles { Name = Qt::UserRole + 1 };

  explicit WallpaperModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

  int indexOf(const QString &url) const;
  QString url(int row) const;
  void retranslate();

 private:
  QVector<Wallpaper> mWallpapers;
};

#endif  // WALLPAPERMODEL_H
