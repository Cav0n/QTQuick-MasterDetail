import QtQuick 2.0
import Sailfish.Silica 1.0
import "../pages"


ListItem {
    id: fileItem
    width: listView.width
    Label {
        text: name    
    }
    Label {
        id: label
        text: size
        anchors.right: parent.right
        anchors.rightMargin: Theme.paddingMedium
    }
    menu: ContextMenu {
        MenuItem {
            text: "Remove from List"
            onClicked: listView.model.removeRow(index)
        }
        MenuItem {
            text: "Delete File"
            onClicked: remorse.remorseDelete()

            RemorseItem {
                id: remorse
                function remorseDelete() {
                    var idx = index
                    remorse.execute(fileItem, "Deleting File", function() { listView.model.removeRow(idx) }, 2000 )
                }
            }
        }
    }
    onClicked: pageStack.push( filePage, { file: file }  )
    Component {
        id: filePage
        FilePage {}
    }
}
