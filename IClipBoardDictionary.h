#ifndef ICLIPBOARDDICTIONARY_H
#define ICLIPBOARDDICTIONARY_H
#include "QString"
class IClipBoardDictionary
{
public:

    virtual void CopyToBuffer();
    virtual void AddToDictionary(QString word);
  virtual void restoreClipBoard();
  virtual ~IClipBoardDictionary();
};

#endif // ICLIPBOARDDICTIONARY_H
