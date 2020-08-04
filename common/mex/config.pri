CONFIG += console link_pkgconfig
CONFIG -= qt qml_debug

PKGCONFIG = gsl

INCLUDEPATH = \
    $$PWD/../../gen_matlab/ \
    $$PWD/../../src/ \
    /opt/MATLAB/R2019a/extern/include/ \
    /usr/local/MATLAB/R2019a/extern/include/ \
    /usr/include/coin/

HEADERS = \
   src/functions.h \
    src/c_spline.h

SOURCES = \
   $$PWD/src/functions.c \
    $$PWD/src/c_spline.c
