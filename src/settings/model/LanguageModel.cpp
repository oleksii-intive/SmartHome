#include "LanguageModel.h"

LanguageModel::LanguageModel(QObject *parent) : QAbstractListModel(parent) {
  mLanguages = {Language("English", "en_US"), Language("Deutsch", "de_DE"),
                Language("Polski", "pl_PL"), Language("Русский", "ru_RU")};
}

int LanguageModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
  }

  return mLanguages.count();
}

QVariant LanguageModel::data(const QModelIndex &index, int role) const {
  const auto row = index.row();
  if (row < 0 || row >= mLanguages.size()) {
    return {};
  }

  if (role == Name) {
    return mLanguages.at(row).name();
  }

  return {};
}

QHash<int, QByteArray> LanguageModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[Name] = "name";
  return roles;
}

int LanguageModel::indexOf(const QString &code) const {
  int i = 0;
  while (i < mLanguages.count()) {
    const auto &language = mLanguages.at(i);
    if (language.code() == code) {
      return i;
    }
    ++i;
  }

  return 0;
}

QString LanguageModel::code(int row) const {
  if (row < 0 || row >= mLanguages.size()) {
    return {};
  }

  return mLanguages.at(row).code();
}
