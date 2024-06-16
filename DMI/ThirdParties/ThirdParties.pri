#Mqtt
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ThirdParties/Mqtt/lib/ -lQt5Mqtt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ThirdParties/Mqtt/lib/ -lQt5Mqttd
else:unix: LIBS += -L$$PWD/../ThirdParties/Mqtt/lib/ -lQt5Mqtt

INCLUDEPATH += $$PWD/../ThirdParties/Mqtt/include
DEPENDPATH += $$PWD/../ThirdParties/Mqtt/include

#spdlog
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ThirdParties/spdlog/lib/ -lspdlog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ThirdParties/spdlog/lib/ -lspdlogd

INCLUDEPATH += $$PWD/../ThirdParties/spdlog/include
DEPENDPATH += $$PWD/../ThirdParties/spdlog/include

#CommonLib
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/CommonLib/lib/ -lCommonLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/CommonLib/lib/ -lCommonLibd
else:unix: LIBS += -L$$PWD/CommonLib/lib/ -lCommonLib

INCLUDEPATH += $$PWD/CommonLib/include
DEPENDPATH += $$PWD/CommonLib/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/CommonLib/lib/libCommonLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/CommonLib/lib/libCommonLibd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/CommonLib/lib/CommonLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/CommonLib/lib/CommonLibd.lib
else:unix: PRE_TARGETDEPS += $$PWD/CommonLib/lib/libCommonLib.a

#Tools
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ThirdParties/Tools/lib/ -lTools
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ThirdParties/Tools/lib/ -lToolsd
else:unix: LIBS += -L$$PWD/../ThirdParties/Tools/lib/ -lTools

CONFIG(debug, debug|release) {
    tools_dll.files = $$PWD/Tools/bin/Toolsd.dll
    tools_dll.path = $$OUT_PWD/debug

}else {
    tools_dll.files = $$PWD/Tools/bin/Tools.dll
    tools_dll.path = $$OUT_PWD/release
}

INCLUDEPATH += $$PWD/Tools/include
DEPENDPATH += $$PWD/Tools/include

#GUIComponentLib
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ThirdParties/GUIComponentLib/lib/ -lGUIComponentLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ThirdParties/GUIComponentLib/lib/ -lGUIComponentLibd
else:unix: LIBS += -L$$PWD/../ThirdParties/GUIComponentLib/lib/ -lGUIComponentLib

CONFIG(debug, debug|release) {
    guicomponentlib_dll.files = $$PWD/GUIComponentLib/bin/GUIComponentLibd.dll
    guicomponentlib_dll.path = $$OUT_PWD/debug
}else {
    guicomponentlib_dll.files = $$PWD/GUIComponentLib/bin/GUIComponentLib.dll
    guicomponentlib_dll.path = $$OUT_PWD/release
}

COPIES += tools_dll \
          guicomponentlib_dll

INCLUDEPATH += $$PWD/GUIComponentLib/include
DEPENDPATH += $$PWD/GUIComponentLib/include
