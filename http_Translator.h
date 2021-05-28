#ifndef HTTP_TRANSLATOR_H
#define HTTP_TRANSLATOR_H

#include <QObject>
#include <QSslSocket>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QMessageBox>
#include <QtQml/qqml.h>
#include <QDebug> //TODO Delete debug after you finish this part of project
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>


class http_Translator : public QObject
{
  Q_OBJECT
    Q_PROPERTY(QString JSONResult READ getJSONResult WRITE setJSONResult NOTIFY changedJSONResult)
public:
  explicit http_Translator(QObject *parent = nullptr);
  QString getJSONResult();
     void setJSONResult(const QString &json);
     void postRequest (QString url);
     QString getRequest (QString url,QString params);
     ~http_Translator();
  public slots:
      void replyFromServer(QNetworkReply* reply);
      void getRequest (QString languageFrom,QString languageTo, QString word);
  signals:
      void changedJSONResult(QString JSONResult);
  private:
      QString p_JSONResult;
      QNetworkAccessManager * networkManager;
      void onfinish(QNetworkReply *rep);
      void jsonToUserClass (QString);

};

#endif // HTTP_TRANSLATOR_H
