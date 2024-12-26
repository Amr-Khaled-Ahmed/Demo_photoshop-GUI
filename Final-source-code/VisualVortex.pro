QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = VisualVortex
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    demo_photoshop.cpp \
    main.cpp \
    tabwidget.cpp

HEADERS += \
    Image_class.h \
    demo_photoshop.h \
    stb_image.h \
    stb_image_write.h \
    tabwidget.h

FORMS += \
    demo_photoshop.ui

TRANSLATIONS += \
    demo_photoshop_ar_EG.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    C:/Users/VICTUS/Desktop/Demo_photo/img.qrc \
    Icons.qrc
    # RC_ICONS = tvcc.ico

DISTFILES += \
    ../../../Videos/demo_photoshop[1]/demo_photoshop/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/debug/demo_photoshop.exe
