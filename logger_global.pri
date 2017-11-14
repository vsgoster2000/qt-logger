# Append current directory into the path where the compiler to find the head files
INCLUDEPATH += $$PWD

TEMPLATE += fakelib
PLATFORM_LOGGER_LIB_NAME = $$qtLibraryTarget(platform_logger)
TEMPLATE -= fakelib
PLATFORM_LOGGER_LIB_DIR=D:\software\dev\qt\platform\lib

