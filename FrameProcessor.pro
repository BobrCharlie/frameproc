QT += core network
QT -= gui

CONFIG += c++11

TARGET = FrameProcessor
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = vcapp

SOURCES += main.cpp paralel_device.cpp frame_processor.cpp net_adapter.cpp point_viewer.cpp
HEADERS += paralel_device.h frame_processor.h net_adapter.h point_viewer.h
