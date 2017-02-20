#include "mymotifwindow.h"

#include        <Xm/Xm.h>
#include        <Xm/AtomMgr.h>
#include        <Xm/Label.h>
#include        <Xm/BulletinB.h>
#include        <Xm/PanedW.h>
#include        <Xm/ScrolledW.h>
#include        <Xm/List.h>
#include        <Xm/Form.h>
#include        <Xm/RowColumn.h>
#include        <Xm/DrawingA.h>
#include        <Xm/PushB.h>
#include        <Xm/PushBG.h>
#include        <Xm/SeparatoG.h>
#include        <Xm/CascadeB.h>
#include        <Xm/Text.h>
#include        <Xm/Separator.h>
#include        <Xm/FileSB.h>
#include        <Xm/MessageB.h>
#include        <Xm/ToggleB.h>
#include        <Xm/CutPaste.h>
#include        <Xm/MwmUtil.h>
#include        <Xm/Protocols.h>
#include        <Xm/LabelG.h>

#include "qtmotif.h"

void
quitDebugControl(Widget w, XtPointer client_data, XtPointer call_data)
{
    // Unmap this puppy from the screen
    //this->close();
}



MyMotifWidget::MyMotifWidget(QWidget *parent, Qt::WFlags f) :
    QtMotifWidget("mymotifwidget", topLevelShellWidgetClass, parent,
                  NULL, 0, f)
{
printf("wfwf in MyMotifWidget ctor\n");
}


void MyMotifWidget::showWindow()
{
printf("showWindow00000000000000000\n");

    //invoke a callback for handling close on popup
    Display *d = XtDisplay(motifWidget());
    Atom wmDelWindow = XmInternAtom(d, String("WM_DELETE_WINDOW"), False);
    XmAddWMProtocolCallback(motifWidget(), wmDelWindow,
                            quitDebugControl, (XtPointer)NULL);
printf("showWindow1111111111111111111\n");
    i_pane = XtVaCreateManagedWidget("pane",
                                     xmPanedWindowWidgetClass,
                                     motifWidget(),
                                     XmNsashWidth, 1,
                                     XmNsashHeight, 1,
                                     NULL);

printf("showWindow22222222222222222222\n");
    i_form = XtVaCreateManagedWidget("mainform",
                                     xmFormWidgetClass,
                                     i_pane,
                                     XmNwidth, width(),
                                     XmNheight, height(),
                                     NULL);

    Widget button = XmCreatePushButton(i_pane, "motif push button", NULL, 0);
printf("showWindow333333333333333333333\n");
    // now manage it
    XtManageChild(button);

printf("shoWindow4444444444444444444444444444\n");
}


void MyMotifWidget::resizeEvent(QResizeEvent* event)
{
    QtMotifWidget::resizeEvent(event);
    synchronizeSizeAndPos();
}

void MyMotifWidget::moveEvent(QMoveEvent* event)
{
    QtMotifWidget::moveEvent(event);
    synchronizeSizeAndPos();
}

void MyMotifWidget::closeEvent(QCloseEvent* event)
{
    QtMotifWidget::closeEvent(event);
}


bool MyMotifWidget::isTextOnTheClipboard()
{
    int iCount = 0;
    unsigned long lMaxLength = 0;


    if (XmClipboardInquireCount(
                XtDisplay(motifWidget()), XtWindow(motifWidget()), &iCount, &lMaxLength)
            != ClipboardSuccess)
        return False;

    return (iCount != 0);

}

void MyMotifWidget::synchronizeSizeAndPos()
{
    XtVaSetValues(i_pane,
                  XmNwidth, width(),
                  XmNheight, height(),
                  NULL);
    XtVaSetValues(i_form,
                  XmNwidth, width(),
                  XmNheight, height(),
                  NULL);
}

