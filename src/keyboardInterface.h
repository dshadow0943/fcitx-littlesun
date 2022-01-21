/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp com.fcitx.littlesun.xml -p keyboardInterface
 *
 * qdbusxml2cpp is Copyright (C) 2017 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef KEYBOARDINTERFACE_H
#define KEYBOARDINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.fcitx.littlesun.server
 */
class ComFcitxLittlesunServerInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.fcitx.littlesun.server"; }

public:
    ComFcitxLittlesunServerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);

    ~ComFcitxLittlesunServerInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<int> hideView()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("hideView"), argumentList);
    }

    inline QDBusPendingReply<int> initView()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("initView"), argumentList);
    }

    inline QDBusPendingReply<int> showView()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("showView"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void sendCandidateCharacter(const QString &str);

};

namespace com {
  namespace fcitx {
    namespace littlesun {
      typedef ::ComFcitxLittlesunServerInterface server;
    }
  }
}
#endif
