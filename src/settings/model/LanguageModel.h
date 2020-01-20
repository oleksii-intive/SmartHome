#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H

#include <QAbstractListModel>

struct Language {
 public:
  Language(QString name, QString code)
      : mName(std::move(name)), mCode(std::move(code)) {}

  QString name() const { return mName; }
  QString code() const { return mCode; }

 private:
  QString mName;
  QString mCode;
};

class LanguageModel : public QAbstractListModel {
  Q_OBJECT

 public:
  enum LanguageRoles { Name = Qt::UserRole + 1 };

  explicit LanguageModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

  int indexOf(const QString &code) const;
  QString code(int row) const;

 private:
  QVector<Language> mLanguages;
};

#endif  // LANGUAGEMODEL_H
