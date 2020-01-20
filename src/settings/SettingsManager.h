#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>

#include <QTranslator>

#include "src/database/DbManager.h"

#include "model/LanguageModel.h"
#include "model/ThemeModel.h"
#include "model/WallpaperModel.h"

class AbstractTheme;

class SettingsManager : public QObject {
  Q_OBJECT
  Q_PROPERTY(WallpaperModel *wallpapers READ wallpapers CONSTANT)
  Q_PROPERTY(QString wallpaper READ wallpaper NOTIFY wallpaperChanged)

  Q_PROPERTY(ThemeModel *themes READ themes CONSTANT)
  Q_PROPERTY(AbstractTheme *theme READ theme NOTIFY themeChanged)

  Q_PROPERTY(LanguageModel *languages READ languages CONSTANT)
  Q_PROPERTY(QString language READ language NOTIFY languageChanged)
 public:
  explicit SettingsManager(DbManager &dbManager, QObject *parent = nullptr);

  Q_INVOKABLE int wallpaperIndex() const;
  Q_INVOKABLE void updateWallpaper(int wallpaperIndex);
  QString wallpaper() const;

  Q_INVOKABLE int themeIndex() const;
  Q_INVOKABLE void updateTheme(int themeIndex);
  AbstractTheme *theme() const;

  Q_INVOKABLE int languageIndex() const;
  Q_INVOKABLE void updateLanguage(int languageIndex);
  QString language() const;

  WallpaperModel *wallpapers();
  ThemeModel *themes();
  LanguageModel *languages();

  Q_INVOKABLE void saveChanges();

  void updateTranslations();

 signals:
  void wallpaperChanged();
  void themeChanged();
  void languageChanged();
  void localeChanged(const QLocale &locale);

 private:
  DbManager &mDbManager;
  Settings mSettings;

  LanguageModel mLanguageModel;
  ThemeModel mThemeModel;
  WallpaperModel mWallpaperModel;

  int mLanguageIndex;
  int mWallpaperIndex;

  AbstractTheme *mTheme = nullptr;
  QTranslator mTranslator;
};

#endif  // SETTINGSMANAGER_H
