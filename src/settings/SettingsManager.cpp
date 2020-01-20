#include "SettingsManager.h"

#include <QCoreApplication>

#include "theme/AbstractTheme.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(settings, "settings")

SettingsManager::SettingsManager(DbManager &dbManager, QObject *parent)
    : QObject(parent), mDbManager(dbManager), mSettings(mDbManager.settings()) {
  qRegisterMetaType<AbstractTheme *>("AbstractTheme *");
  mLanguageIndex = mLanguageModel.indexOf(mSettings.language);
  mTheme = mThemeModel.instantiateTheme(
      static_cast<ThemeModel::ThemeStyle>(mSettings.theme));
  mWallpaperIndex = mWallpaperModel.indexOf(mSettings.wallpaper);
}

int SettingsManager::wallpaperIndex() const { return mWallpaperIndex; }

void SettingsManager::updateWallpaper(int wallpaperIndex) {
  if (mWallpaperIndex == wallpaperIndex) {
    return;
  }

  mWallpaperIndex = wallpaperIndex;
  mSettings.wallpaper = wallpaper();
  emit wallpaperChanged();
}

QString SettingsManager::wallpaper() const {
  return mWallpaperModel.url(mWallpaperIndex);
}

int SettingsManager::themeIndex() const { return mSettings.theme; }

void SettingsManager::updateTheme(int themeIndex) {
  if (mSettings.theme == themeIndex) {
    return;
  }

  mSettings.theme = themeIndex;
  mTheme->deleteLater();
  mTheme = mThemeModel.instantiateTheme(
      static_cast<ThemeModel::ThemeStyle>(mSettings.theme));
  emit themeChanged();
}

AbstractTheme *SettingsManager::theme() const { return mTheme; }

int SettingsManager::languageIndex() const { return mLanguageIndex; }

void SettingsManager::updateLanguage(int languageIndex) {
  if (mLanguageIndex == languageIndex) {
    return;
  }

  mLanguageIndex = languageIndex;
  mSettings.language = language();
  updateTranslations();
  emit languageChanged();
}

QString SettingsManager::language() const {
  return mLanguageModel.code(mLanguageIndex);
}

WallpaperModel *SettingsManager::wallpapers() { return &mWallpaperModel; }

ThemeModel *SettingsManager::themes() { return &mThemeModel; }

LanguageModel *SettingsManager::languages() { return &mLanguageModel; }

void SettingsManager::saveChanges() { mDbManager.editSettings(mSettings); }

void SettingsManager::updateTranslations() {
  QLocale locale{mSettings.language};
  if (!mTranslator.load(locale, QStringLiteral("SmartHome"),
                        QStringLiteral("_"), QStringLiteral(":/translations"),
                        QStringLiteral(".qm"))) {
    qCCritical(settings) << "Couldn't load file with translations";
    return;
  }

  if (!qApp->installTranslator(&mTranslator)) {
    qCCritical(settings) << "Couldn't install translations";
    return;
  }

  mWallpaperModel.retranslate();
  mThemeModel.retranslate();
  emit localeChanged(locale);
}
