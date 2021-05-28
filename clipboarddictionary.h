#ifndef CLIPBOARDDICTIONARY_H
#define CLIPBOARDDICTIONARY_H
#include <QObject>
#include "QString"
#include "QClipboard"
#include "QGuiApplication"
#include "QDebug"
#include <QHotkey>

class ClipBoardDictionary : public QObject
{
    Q_PROPERTY(QString word READ getWord WRITE setWord NOTIFY wordChanged)
    Q_OBJECT
public:
    explicit ClipBoardDictionary(QObject *parent = nullptr);
    void AddToDictionary(QString word);
    void restoreClipBoard();
    QString getWord();
    void setWord(QString word);
    QHotkey *shortCut;
public slots:
        void copyToBuffer();
private  slots:
    void setData();
signals:
    void wordChanged();
private:
    QClipboard *clipboard;
    QString p_word = "Null";
    QString backUpText;
};

#endif // CLIPBOARDDICTIONARY_H
