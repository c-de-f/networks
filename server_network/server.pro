#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T14:49:01
#
#-------------------------------------------------

QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp \
    Assignment.cpp \
    CompHeurSolver.cpp \
    ExactSolver.cpp \
    Heuristics.cpp \
    MixedSolver.cpp \
    Problem.cpp \
    Resource.cpp \
    Solver.cpp \
    stdafx.cpp \
    Task.cpp

HEADERS  += mainwindow.h \
    server.h \
    Assignment.h \
    heur.h \
    Heuristics.h \
    Problem.h \
    Resource.h \
    resource1.h \
    resource2.h \
    Solver.h \
    stdafx.h \
    targetver.h \
    Task.h

FORMS    += mainwindow.ui


CONFIG   += console
CONFIG   -= app_bundle

EXAMPLE_FILES += echoclient.html

target.path = $$[QT_INSTALL_EXAMPLES]/websockets/echoserver
INSTALLS += target

DISTFILES += \
    Solved.rar \
    server.pro.user \
    draft2.csv \
    mixedres1sdraft.csv \
    Problem.txt \
    ResearchTask.rc \
    ResearchTask.vcxproj \
    ResearchTask.vcxproj.filters \
    ResearchTask.vcxproj.user \
    solve_test1_renamed tasks.txt \
    solve_test2_unresolved tasks.txt \
    solve_test3_reordered sections.txt \
    solve_test4_mismatched attributes.txt \
    solve_test5_link cycles.txt \
    solve_test6_schedule1.txt \
    solve_test7_schedule2.txt \
    solve_test8_schedule3.txt \
    solve_test9_schedule4.txt \
    solve_test10_resource1.txt \
    solve_test11_resource2.txt \
    solve_test12_resource3.txt \
    solve_test13_resource4.txt
