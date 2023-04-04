#pragma once

#include <QObject>
#include <QDebug>
#include <QPointer>
#include <QSize>
#include "service/models/Mirror.h"
#include "adbprocess.h"


//!
//! \brief The ResourceService class
//! This class will act as a MainThread data cullmination point
//! here we should gather all the changes from controls, events e.t.c.
//! that should enter the simulation and prepare either states, or update object
//! for SceneProvider to gather
//!
class ResourceService : public QObject
{
Q_OBJECT

    Q_PROPERTY(double mirror READ getMirror WRITE setMirror NOTIFY mirrorChanged)
    Q_PROPERTY(QSize frameSize READ frameSize WRITE setFrameSize NOTIFY frameSizeChanged)
    Q_PROPERTY(QSize portraitSize READ portraitSize WRITE setPortraitSize NOTIFY portraitSizeChanged)
    Q_PROPERTY(QSize landscapeSize READ landscapeSize WRITE setLandscapeSize NOTIFY landscapeSizeChanged)
    Q_PROPERTY(int orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)

public:
    explicit ResourceService(QObject *parent = nullptr);

    static void declareQml();

    enum DisplayOrientation {
        portrait,    // Portrait orientation is vertical
        landscape,   // Landscape orientation is horizontal
    };



    void setSerial(const QString &serial);
    QString serial();

    Q_INVOKABLE void processClick(QString type);
    Q_INVOKABLE void qmlCommands(QString command, QString data);

    bool getMirror() const;

    int orientation() const;
    QSize frameSize() const;

    QSize portraitSize() const;
    QSize landscapeSize() const;


    void clearMirrorCash();
    void setUsbMirrorParametre();

    Mirror *mirror = nullptr;

    /**   save serial for restart tcpip 5555 for first time. this cause we can access by Wi-Fi connection
    *     #adb -s RZ8NC0KA54H tcpip 5555
    *     #adb connect 192.168.1.161
    **/
    QList<QString> m_usb_serials;

public slots:

    void setMirror(bool vlaue);
    void setFrameSize(QSize size);
    void setPortraitSize(QSize size);
    void setLandscapeSize(QSize size);
    void setOrientation(int);

signals:
    void mirrorChanged(bool value);
    void frameSizeChanged(QSize size);
    void portraitSizeChanged(QSize size);
    void landscapeSizeChanged(QSize size);
    void orientationChanged(int orientation);

    void qmlEvents(QString command, QString data);
    void androidEvents(QString command, QString data);
    void cppGenerateEvents(QString name);
    void usbDeviceName(QString name);

    //void clientRequest(QString json);
    void webSocketNewConnection(QString ip);

private:
    QSize m_frameSize;
    QSize m_portraitSize;
    QSize m_landscapeSize;

    bool m_mirror = false;
    QString m_serial;

    int m_orientation = DisplayOrientation::portrait;

    bool m_showTouch = false;
    bool m_screen = false;
};
