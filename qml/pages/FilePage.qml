import QtQuick 2.0
import Sailfish.Silica 1.0
import FileModel 1.0

Page {
    property var file

    PageHeader {
        title: "File Edition"
        id: header
    }

    Column {
        anchors.top: header.bottom
        width: parent.width

        TextField {
            text: file.name
            label: "Filename"

            width: parent.width
            validator: RegExpValidator { regExp: /^[^/]*$/ }
            EnterKey.onClicked: {
                file.name = text
                sizeField.focus = true
            }
            onFocusChanged: text = Qt.binding( function() { return file.name} )
        }

        TextField {
            id: sizeField
            text: file.size
            label: "Size in bytes"
            width: label.length*font.pointSize
            validator: RegExpValidator { regExp: /\d{1,7}$/ }

            inputMethodHints: Qt.ImhDigitsOnly
            EnterKey.onClicked: {
                file.size = text
                focus = false
            }
            onFocusChanged:  text = Qt.binding( function() { return file.size} )
        }

    }
}
