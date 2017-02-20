#pragma once

#include <QMainWindow>
#include <QDialog>
#include <QApplication>
#include "qtmotifwidget.h"


class MyMotifWidget : public QtMotifWidget
{
    Q_OBJECT
public:
    MyMotifWidget(QWidget *parent = 0, Qt::WFlags f = 0);

    QWidget* getWidget()
    {
        return this;
    }

    void showWindow();
    void resizeEvent(QResizeEvent* event);
    void moveEvent(QMoveEvent* event);
    void closeEvent(QCloseEvent* event);

    bool isTextOnTheClipboard();

private:
    void synchronizeSizeAndPos();
    Widget i_form;
    Widget i_pane;
};
