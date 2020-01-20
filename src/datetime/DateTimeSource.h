#ifndef DATETIMESOURCE_H
#define DATETIMESOURCE_H

#include <QLocale>
#include <QObject>

class DateTimeSource : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString time READ time NOTIFY timeChanged)
  Q_PROPERTY(QString date READ date NOTIFY dateChanged)
  Q_PROPERTY(int month READ month NOTIFY dateChanged)
  Q_PROPERTY(int year READ year NOTIFY dateChanged)

 public:
  explicit DateTimeSource(QObject *parent = nullptr);

  QString time() const;
  QString date() const;
  int month() const;
  int year() const;

  void processNewLocale(const QLocale &locale);

 signals:
  void timeChanged();
  void dateChanged();

 protected:
  void timerEvent(QTimerEvent *event) override;

 private:
  void updateDateTime();

  QString mTime;
  int mMinutes = -1;
  QString mDate;
  int mMonth = 0;
  int mYear = 0;
  QLocale mLocale = QLocale::c();
};

#endif  // DATETIMESOURCE_H
