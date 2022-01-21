#include "keyboardbus.h"
#include "eim.h"
#include <fcitx/module/dbus/fcitx-dbus.h>

KeyboardBus::KeyboardBus(struct _FcitxLittleSunAddonInstance* libpinyin, QObject *parent) : QObject(parent)
  , m_keyboardInter(new ComFcitxLittlesunServerInterface("com.fcitx.littlesun.server",
                                                         "/keyboard",
                                                         QDBusConnection::sessionBus(), this))
{
    m_libpinyin = libpinyin;
}

void KeyboardBus::initView()
{
    m_keyboardInter->initView();
}

void KeyboardBus::showView()
{
    m_keyboardInter->showView();
}

void KeyboardBus::hideView()
{
    m_keyboardInter->hideView();
}
