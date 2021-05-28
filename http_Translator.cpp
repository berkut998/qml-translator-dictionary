#include "http_Translator.h"

http_Translator::http_Translator(QObject *parent) : QObject(parent)
{
     networkManager = new QNetworkAccessManager(this);
     connect(networkManager,&QNetworkAccessManager::finished,this,&http_Translator::replyFromServer);
}

QString http_Translator::getJSONResult()
{
    return p_JSONResult;
}

void http_Translator::setJSONResult(const QString &json)
{
    if (json == p_JSONResult)
        return;
    p_JSONResult = json;
    emit changedJSONResult(p_JSONResult);
}

void http_Translator::getRequest(QString languageFrom,QString languageTo, QString word)
{
    QString url;
    url = "https://systran-systran-platform-for-language-processing-v1.p.rapidapi.com/translation/text/translate?source=" +languageFrom +"&target="+ languageTo +"&input=" + word;
    QUrl p_url = QUrl(url);
    QNetworkRequest request(p_url);
    request.setRawHeader(QByteArray("x-rapidapi-key"),QByteArray("f797859160mshf4a2683496b53fap10090bjsn90bb50a74921"));
    networkManager->get(request);
}

http_Translator::~http_Translator()
{
  //networkManager->destroyed(networkManager);
}


void http_Translator::replyFromServer(QNetworkReply* reply)
{
    if (reply->isReadable())
    {
        QByteArray arrayOfRep =   reply->readAll();
        // get the root object
        QJsonDocument itemDoc = QJsonDocument::fromJson(arrayOfRep);
        QJsonObject rootObject = itemDoc.object();
        // get the outputs object
        QJsonValue response = rootObject.value("outputs");
        QJsonValue outputValue;
        if(response.isArray())
        {
            QJsonArray array = response.toArray();
            QJsonValue jsonValueFromArray = array.at(0);
            QJsonObject objectOutput = jsonValueFromArray.toObject();
            outputValue = objectOutput.value("output");
            setJSONResult(outputValue.toString());
        }
        else
            setJSONResult("Cannot set data");
        qDebug() <<  getJSONResult();
    }
    else
        qDebug() <<  "Error cannot read" ;

}
