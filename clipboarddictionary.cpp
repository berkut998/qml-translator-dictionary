#include "clipboarddictionary.h"
#include <QHotkey>
ClipBoardDictionary::ClipBoardDictionary(QObject *parent) : QObject(parent)
{
    clipboard = QGuiApplication::clipboard();
    QObject::connect(clipboard,SIGNAL(dataChanged()),this,SLOT(setData()));
    shortCut = new QHotkey(QKeySequence("ctrl+T"), true, this);//The hotkey will be automatically registered
    qDebug() << "Platform is supported" << clipboard->supportsFindBuffer();
    qDebug() << "Is Registered: " << shortCut->isRegistered();
    if (shortCut != NULL)
      QObject::connect(shortCut, SIGNAL(activated()), this, SLOT(copyToBuffer()));


}

void ClipBoardDictionary::copyToBuffer()
{
    setWord(clipboard->text(clipboard->Clipboard));
}

void ClipBoardDictionary::AddToDictionary(QString word)
{

}

void ClipBoardDictionary::restoreClipBoard()
{
 // clipboard->setText(backUpText);
}

QString ClipBoardDictionary::getWord()
{
  return p_word;
}

void ClipBoardDictionary::setWord(QString word)
{
  p_word = word;
  emit wordChanged();
  qDebug() << "Data was copied";
  qDebug() << p_word;
}

void ClipBoardDictionary::setData()
{
   copyToBuffer();
  // restoreClipBoard();
}

