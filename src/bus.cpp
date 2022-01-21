#include "bus.h"
#include "eim.h"
#include <fcitx/module/dbus/fcitx-dbus.h>
// must keep X11 haeder under QT header
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

const char *introspection_xml =
    "<!DOCTYPE node PUBLIC \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\"\n"
    "\"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">\n"
    "<node name=\"" FCITX_LIBPINYIN_PATH "\">\n"
    "  <interface name=\"org.freedesktop.DBus.Introspectable\">\n"
    "    <method name=\"Introspect\">\n"
    "      <arg name=\"data\" direction=\"out\" type=\"s\"/>\n"
    "    </method>\n"
    "  </interface>\n"
    "  <interface name=\"" FCITX_LIBPINYIN_INTERFACE "\">\n"
    "    <method name=\"CommitString\">"
    "      <arg name=\"str\" direction=\"in\" type=\"s\"/>\n"
    "    </method>"
    "    <method name=\"DeleteChar\">"
    "    <method name=\"GetStatus\">"
    "    </method>"
    "  </interface>\n"
    "</node>\n";

static DBusHandlerResult dbusEventHandler(DBusConnection* conn, DBusMessage* message, void* self) {
    FcitxLittleSunBus* bus = (FcitxLittleSunBus*) self;
    return bus->dbusEvent(conn, message);
}

FcitxLittleSunBus::FcitxLittleSunBus(struct _FcitxLittleSunAddonInstance* libpinyin)
{
    FcitxInstance* instance = libpinyin->owner;
    DBusConnection *conn = FcitxDBusGetConnection(instance);
    DBusConnection *privconn = FcitxDBusGetPrivConnection(instance);
    if (conn == NULL && privconn == NULL) {
        FcitxLog(ERROR, "DBus Not initialized");
    }

    m_libpinyin = libpinyin;
    m_conn = conn;
    m_privconn = privconn;

    DBusObjectPathVTable fcitxIPCVTable = {NULL, &dbusEventHandler, NULL, NULL, NULL, NULL };

    if (conn) {
        dbus_connection_register_object_path(conn, FCITX_LIBPINYIN_PATH, &fcitxIPCVTable, this);
    }

    if (privconn) {
        dbus_connection_register_object_path(privconn, FCITX_LIBPINYIN_PATH, &fcitxIPCVTable, this);
    }

}

FcitxLittleSunBus::~FcitxLittleSunBus()
{
    if (m_conn) {
        dbus_connection_unregister_object_path(m_conn, FCITX_LIBPINYIN_PATH);
    }
    if (m_privconn) {
        dbus_connection_unregister_object_path(m_privconn, FCITX_LIBPINYIN_PATH);
    }
}

DBusHandlerResult FcitxLittleSunBus::dbusEvent(DBusConnection* connection, DBusMessage* message)
{
    DBusHandlerResult result = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
    DBusMessage *reply = NULL;
    boolean flush = false;
    if (dbus_message_is_method_call(message, DBUS_INTERFACE_INTROSPECTABLE, "Introspect")) {

        reply = dbus_message_new_method_return(message);

        dbus_message_append_args(reply, DBUS_TYPE_STRING, &introspection_xml, DBUS_TYPE_INVALID);
    } else if (dbus_message_is_method_call(message, FCITX_LIBPINYIN_INTERFACE, "DeleteChar")) {
        Display* disp = XOpenDisplay(nullptr);

        if(disp != nullptr) {
            KeyCode key = XKeysymToKeycode(disp, XK_BackSpace);

            XTestFakeKeyEvent(disp, key, true, CurrentTime);
            XTestFakeKeyEvent(disp, key, false, CurrentTime);

            XFlush(disp);

            XCloseDisplay(disp);
        }
        reply = dbus_message_new_method_return(message);
    } else if (dbus_message_is_method_call(message, FCITX_LIBPINYIN_INTERFACE, "GetStatus")) {
        reply = dbus_message_new_method_return(message);

    } else if (dbus_message_is_method_call(message, FCITX_LIBPINYIN_INTERFACE, "CommitString")) {
        char* str = NULL;
        if (dbus_message_get_args(message, NULL, DBUS_TYPE_STRING, &str, DBUS_TYPE_INVALID)) {
            FcitxInstanceCommitString(m_libpinyin->owner, FcitxInstanceGetCurrentIC(m_libpinyin->owner), str);
            reply = dbus_message_new_method_return(message);
        }
        else {
            reply = dbus_message_new_error_printf(message,
                                                  DBUS_ERROR_UNKNOWN_METHOD,
                                                  "No such method with signature (%s)",
                                                  dbus_message_get_signature(message));
        }
    }

    if (reply) {
        dbus_connection_send(connection, reply, NULL);
        dbus_message_unref(reply);
        if (flush) {
            dbus_connection_flush(connection);
        }
        result = DBUS_HANDLER_RESULT_HANDLED;
    }
    return result;
}
