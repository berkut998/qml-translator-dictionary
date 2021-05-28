#ifndef SQLDICTIONARY_H
#define SQLDICTIONARY_H

#include <QObject>
#include <QtSql/QSqlQueryModel>
#include <QSqlRecord>
#include <QColor>
#include <QDebug>
#include <QHash>
#include <QCoreApplication>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QImage>
#include <QtSql>


class SqlDictionary :  public QSqlQueryModel
{
  Q_OBJECT
public:
  explicit SqlDictionary(QObject *parent = nullptr);
  QVariant data(const QModelIndex &item, int role) const override;
  QHash<int, QByteArray> roleNames() const override;
  ~SqlDictionary();
public slots:
  void addWordToDictionary (QString wordEnglish, QString wordTranslated);
signals:

private:
      void conectToDataBase ();
      QSqlDatabase mydb;
      void setDataFromDataBase();

};

#endif // SQLDICTIONARY_H
