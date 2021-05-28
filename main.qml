import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import ClipBoardDictionary 1.0
import QSystemTrayIcon 1.0
import QtQuick.Window 2.0
import Qt.labs.platform 1.1
import Http_Translator 1.0
import SqlDictionary 1.0
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: application
    width: 640
    height: 480
    visible: true
    title: qsTr("Dictionary")
    // Обработчик события закрытия окна
    header: ToolBar {
        contentHeight: toolButton.implicitHeight
        ToolButton {
            id: toolButton
            icon.source: stackView.depth > 1 ? "qrc:/Assets/arrow_back_black_24dp.svg" : "qrc:/Assets/menu_black_24dp.svg"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }
    onClosing: {

        application.hide()
    }

    Connections {
        target: systemTray
        // Сигнал - показать окно
        onSignalShow: {
            application.show()
        }

        // Сигнал - закрыть приложения игнорируя чек-бокс
        onSignalQuit: {
            console.log("exite from app")
            Qt.quit()
        }

        // Свернуть/развернуть окно через клик по системному трею
        onSignalIconActivated: {
            if (application.visibility === Window.Hidden) {
                application.show()
            } else {
                application.hide()
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: "qrc:/translatorPage.qml"
    }

    Drawer {
        id: drawer
        width: application.width * 0.66
        height: application.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Dictionary")
                width: parent.width
                onClicked: {
                    stackView.push("qrc:/dictionaryPage.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Setting")
                width: parent.width
                onClicked: {
                    stackView.push("qrc:/settingPage.qml")
                    drawer.close()
                }
            }
        }
    }

    Shortcut {
        sequence: "Ctrl+E"
        onActivated: {
            console.log("ShortCut was pressed")
            ClipBoardDictionary.copyToBuffer()
        }
    }
}
