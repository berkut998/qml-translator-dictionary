import QtQuick 2.0
import QtQuick.Controls 2.15
import SqlDictionary 1.0
import QtQuick.Controls.Material 2.12
import ClipBoardDictionary 1.0
import Qt.labs.settings 1.1

Page {
    id: dictionary_Page
    ListView {
        id: listView
        anchors.fill: parent
        spacing: 10
        delegate: dictionaryDelegate
        model: SqlDictionary
    }

    Component {
        id: dictionaryDelegate
        Item {
            height: {
                if (id_englishWord.height > id_translatedWord.height)
                    id_englishWord.height
                else
                    id_translatedWord.height
            }
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            Text {
                id: id_englishWord
                text: wordEnglish
                width: parent.width / 2
                color: Material.foreground
                wrapMode: Text.WordWrap
                font.pointSize: {
                    8 + parseInt(setting.value("fontSize", 1))
                } //minimum size 8 ( contain only index in combobox in .ini file so need add 8)
            }
            Text {
                id: id_translatedWord
                width: parent.width / 2
                text: wordTranslated
                wrapMode: Text.WordWrap
                color: Material.foreground
                anchors.right: parent.right
                anchors.rightMargin: 0
                font.pointSize: {
                    8 + parseInt(setting.value("fontSize", 1))
                } //minimum size 8 ( contain only index in combobox in .ini file so need add 8)
                Component.onCompleted: {
                    console.log("Font size " + id_translatedWord.font.pointSize)
                }
            }
        }
    }

    Settings {
        id: setting
        fileName: "Setting.ini"
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

