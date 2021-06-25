#ifndef KEYBOARDBUS_H
#define KEYBOARDBUS_H

#include <QObject>
#include "keyboardInterface.h"
#include <fcitx/instance.h>

class KeyboardBus : public QObject
{

    Q_OBJECT

public:
    explicit KeyboardBus(struct _FcitxLittleSunAddonInstance* libpinyin, QObject *parent = nullptr);

    void initView();
    void showView();
    void hideView();


private:
    _FcitxLittleSunAddonInstance* m_libpinyin;
    ComFcitxLittlesunServerInterface* m_keyboardInter;
    FcitxInstance* owner;

signals:

};

#endif // KEYBOARDBUS_H
