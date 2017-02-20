FORMS       = mainwindow.ui
HEADERS     = mainwindow.h \
              treeitem.h \
              treemodel.h \
              qtmotif.h \
              qtmotifwidget.h \
              mymotifwindow.h
RESOURCES   = editabletreemodel.qrc
SOURCES     = mainwindow.cpp \
              treeitem.cpp \
              treemodel.cpp \
              main.cpp \
              qtmotif.cpp \
              qtmotifwidget.cpp \
              mymotifwindow.cpp
CONFIG  += qt

# install
target.path = $$[QT_INSTALL_EXAMPLES]/itemviews/editabletreemodel
sources.files = $$FORMS $$HEADERS $$RESOURCES $$SOURCES *.pro *.txt
sources.path = $$[QT_INSTALL_EXAMPLES]/itemviews/editabletreemodel
INSTALLS += target sources
