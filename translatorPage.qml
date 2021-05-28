import QtQuick 2.0
import QtQuick.Controls 2.15
import Http_Translator 1.0
import SqlDictionary 1.0
import ClipBoardDictionary 1.0
import QtQuick.Controls.Material 2.12
import Qt.labs.settings 1.1

Page {
    id: translator_Page
    TextArea {
        id: textArea_orginText
        text: ClipBoardDictionary.word
        placeholderText: qsTr("Text Area")
        anchors.left: parent.left
        anchors.right: roundButton.left
        anchors.top: roundButton.bottom
        anchors.bottom: button.top
        wrapMode: Text.WordWrap
        anchors.rightMargin: -15
        textFormat: Text.AutoText
        anchors.bottomMargin: 5
        anchors.leftMargin: 10
        anchors.topMargin: 5
        selectByKeyboard: true
        selectByMouse: true
        onTextChanged: {
            console.log("textWas changed in area 1")
            Http_Translator.getRequest(comboBox_languageFrom.currentText,
                                       comboBox_languageTo.currentText,
                                       textArea_orginText.text)
            console.log(comboBox_languageFrom.currentText)
        }
    }

    Button {
        id: button
        y: 427
        text: qsTr("add to dictionary")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 5
        onClicked: {
            SqlDictionary.addWordToDictionary(textArea_orginText.text,
                                              textArea_TranslatedText.text)
        }
    }

    TextArea {
        id: textArea_TranslatedText
        text: Http_Translator.JSONResult
        anchors.left: roundButton.right
        anchors.right: parent.right
        anchors.top: roundButton.bottom
        anchors.bottom: button.top
        wrapMode: Text.WordWrap
        anchors.leftMargin: -15
        anchors.rightMargin: 10
        textFormat: Text.AutoText
        anchors.topMargin: 5
        anchors.bottomMargin: 5
        placeholderText: qsTr("Text Area")
        selectByKeyboard: true
        selectByMouse: true
        onTextChanged: {
            console.log(setting.value("showMessage", true))
            if (setting.value("showMessage",
                              true) == "true" || setting.value("showMessage",
                                                               true) == true)
                systemTray.showMessage(textArea_TranslatedText.text)
        }
    }

    RoundButton {
        id: roundButton
        x: parent.width / 2 - roundButton.width
        anchors.top: parent.top
        anchors.topMargin: 0
        Material.background: "transparent"
        icon.source: "qrc:/Assets/swap_horiz_black_24dp.svg"
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {

            var switchedLanguage = comboBox_languageFrom.currentIndex
            comboBox_languageFrom.currentIndex = comboBox_languageTo.currentIndex
            comboBox_languageTo.currentIndex = switchedLanguage
            textArea_orginText.text = textArea_TranslatedText.text
        }
    }

    ComboBox {
        id: comboBox_languageFrom
        x: 10
        y: 7
        width: 83
        height: 41
        model: ["en", "ru", "fr", "de"]
    }

    ComboBox {
        id: comboBox_languageTo
        x: 547
        y: 7
        width: 83
        height: 41
        model: ["en", "ru", "fr", "de"]
        Component.onCompleted: {
            comboBox_languageTo.currentIndex = 1
        }
    }

    Settings {
        id: setting
        fileName: "Setting.ini"
        property alias languageFrom: comboBox_languageFrom.currentIndex
        property alias languageTo: comboBox_languageTo.currentIndex
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3}D{i:4}
}
##^##*/

