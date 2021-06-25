#ifndef FCITX_LIBPINYIN_BUS_H
#define FCITX_LIBPINYIN_BUS_H

#include <dbus/dbus.h>
#include <fcitx/instance.h>

class FcitxLittleSunBus {
public:
    FcitxLittleSunBus(struct _FcitxLittleSunAddonInstance* libpinyin);
    virtual ~FcitxLittleSunBus();

    DBusHandlerResult dbusEvent(DBusConnection* connection, DBusMessage* message);
private:
    DBusConnection* m_privconn;
    DBusConnection* m_conn;
    _FcitxLittleSunAddonInstance* m_libpinyin;
};

#endif // FCITX_LIBPINYIN_BUS_H
