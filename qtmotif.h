
#ifndef QMOTIF_H
#define QMOTIF_H

#include "AlgoPlatformDefs.h"
//#include <QtCore/qabstracteventdispatcher.h>
#include <QAbstractEventDispatcher>
#include <X11/Intrinsic.h>

class QtMotifPrivate;

class GCC_EXPORT QtMotif : public QAbstractEventDispatcher
{
    Q_OBJECT
    QtMotifPrivate *d;

public:
    QtMotif(const char *applicationClass, XtAppContext context = NULL,
            XrmOptionDescRec *options = 0, int numOptions = 0);
    ~QtMotif();

    XtAppContext applicationContext() const;

    static Display *display();
    static XEvent *lastEvent();

    static void registerWidget(QWidget *);
    static void unregisterWidget(QWidget *);
    static bool redeliverEvent(XEvent *event);

    // QAbstractEventDispatcher interface
    bool processEvents(QEventLoop::ProcessEventsFlags flags);
    bool hasPendingEvents();

    void registerSocketNotifier(QSocketNotifier *);
    void unregisterSocketNotifier(QSocketNotifier *);

    void registerTimer(int timerId, int interval, QObject *object);
    bool unregisterTimer(int timerId);
    bool unregisterTimers(QObject *object);
    QList<TimerInfo> registeredTimers(QObject *object) const;

    void wakeUp();
    void interrupt();
    void flush();

    void startingUp();
    void closingDown();
};

#endif // QMOTIF_H
