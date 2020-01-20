#ifndef THEMEMODEL_H
#define THEMEMODEL_H

#include <QAbstractListModel>

class AbstractTheme;

class ThemeModel : public QAbstractListModel {
  Q_OBJECT

 public:
  enum ThemeRoles { Name = Qt::UserRole + 1 };
  enum class ThemeStyle { Light, Dark };

  explicit ThemeModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

  void retranslate();
  AbstractTheme *instantiateTheme(ThemeStyle style);

 private:
  QVector<QString> mThemes;
};

#endif  // THEMEMODEL_H
