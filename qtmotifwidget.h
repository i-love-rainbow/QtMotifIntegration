
#ifndef QMOTIFWIDGET_H
#define QMOTIFWIDGET_H

#include <QtGui/qwidget.h>

#include <X11/Intrinsic.h>
#undef Bool
#undef Int

class QtMotifWidgetPrivate;
class QKeyEvent;

class QtMotifWidget : public QWidget
{
    Q_OBJECT
    QtMotifWidgetPrivate *d;

public:
    QtMotifWidget(const char *name, WidgetClass widgetClass, QWidget *parent,
                  ArgList args = NULL, Cardinal argCount = 0,
                  Qt::WFlags flags = 0);
    ~QtMotifWidget();

    Widget motifWidget() const;

protected:
    bool event(QEvent *);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    bool eventFilter(QObject *object, QEvent *event);
    bool x11Event(XEvent *event);

private:
    void realize(Widget);

    friend void qmotif_widget_shell_destroy(Widget w);
    friend void qmotif_widget_shell_realize(Widget, XtValueMask *,
                                            XSetWindowAttributes *);
    friend void qmotif_widget_shell_change_managed(Widget);
    static bool dispatchQEvent(QEvent*, QWidget*);
    friend class QtMotifDialog;
};

#endif // QMOTIFWIDGET_H
