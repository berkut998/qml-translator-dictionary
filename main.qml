import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import ClipBoardDictionary 1.0
import QSystemTrayIcon 1.0
import QtQuick.Window 2.0

ApplicationWindow
{
    id:application
    width: 640
    height: 480
    visible: true
    title: qsTr("Dictionary")



    Connections {
        target: systemTray
        // Сигнал - показать окно
        onSignalShow: {
            application.show();
        }

        // Сигнал - закрыть приложения игнорируя чек-бокс
        onSignalQuit: {
            ignoreCheck = true
            close();
        }

        // Свернуть/развернуть окно через клик по системному трею
        onSignalIconActivated: {
             if(application.visibility === Window.Hidden) {
                 application.show()
             } else {
                 application.hide()
             }
        }
    }







    QSystemTrayIcon
    {
        id:systemTray
        Component.onCompleted:
        {
            systemTray.icon = iconTray
            systemTray.toolTip = "dictionary"
            systemTray.show()
            systemTray.visible = true
            console.log("tray completed")
        }
        onActivated:
        {
            console.log("onActivated")
            //left click by mouse
            if (reason === 1)
                trayMenu.popup()
            else
            {
                if (application.visibility == Window.Hidden)
                {
                    application.show();
                }
                else
                {
                    application.hide()
                }
            }
        }
    }

    Menu
    {
        id:trayMenu
        MenuItem
        {
            text: qsTr("Развернуть окно")
            onTriggered: application.show()
        }
        MenuItem
        {
            text: qsTr("Выход")
            onTriggered:
            {
                systemTray.hide()
                Qt.quit()
            }
        }
    }

    Text{
    id:textResult
    text:ClipBoardDictionary.word
    }

    Shortcut {
        sequence:  "Ctrl+E"
        onActivated:
        {
            console.log("ShortCut was pressed")
            ClipBoardDictionary.copyToBuffer()
        }
    }

}
