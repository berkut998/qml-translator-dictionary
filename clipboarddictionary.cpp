#include "clipboarddictionary.h"

ClipBoardDictionary::ClipBoardDictionary(QObject *parent) : QObject(parent)
{
    clipboard = QGuiApplication::clipboard();
    QObject::connect(clipboard,SIGNAL(dataChanged()),this,SLOT(setData()));
}

void ClipBoardDictionary::copyToBuffer()
{
    setWord(clipboard->text(clipboard->Selection));
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

