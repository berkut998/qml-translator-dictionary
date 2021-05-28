import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import Qt.labs.settings 1.1

Page {
    id: setting_page
    property alias checkBox_ShowMessage: checkBox_ShowMessage
    property alias comboBox_Size: comboBox_Size
    CheckBox {
        id: checkBox_ShowMessage
        text: qsTr("Show message")
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.leftMargin: 10
    }

    ComboBox {
        id: comboBox_Size
        anchors.left: parent.left
        anchors.top: checkBox_ShowMessage.bottom
        anchors.topMargin: 10
        anchors.leftMargin: 10
        model: ["8", "9", "10", "11", "12", "13", "14", "15", "16"]
    }

    Label {
        id: label_Size
        text: qsTr("Size text in dictionary")
        anchors.left: comboBox_Size.right
        anchors.top: checkBox_ShowMessage.bottom
        anchors.topMargin: 25
        anchors.leftMargin: 5
    }

    Settings {
        id: setting
        fileName: "Setting.ini"
        property alias fontSize: comboBox_Size.currentIndex
        property alias showMessage: checkBox_ShowMessage.checked
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1}D{i:2}D{i:3}
}
##^##*/

