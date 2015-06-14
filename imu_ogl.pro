#VPATH += 
#INCLUDEPATH +=

HEADERS       = glwidget.h \
                window.h \
                serialinput.h \
                board.h \
                glhelpers.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                serialinput.cpp \
                board.cpp
QT     += opengl
CONFIG += serialport

# install
target.path = .
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS imu_ogl.pro
sources.path = imu_ogl
INSTALLS += target sources

symbian: warning(This example might not fully work on Symbian platform)
maemo5: warning(This example does not work on Maemo platform)
simulator: warning(This example might not fully work on Simulator platform)
