import QtQuick 2.0
import Sailfish.Silica 1.0
import FileModel 1.0
import "../delegates"

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Add Element")
                onClicked: listView.model.newElement()
            }
        }

        header: PageHeader { title: qsTr("My files")   }

        model: FileModel { list: filesFromTmp }
        delegate: DelegateFile { }
        VerticalScrollDecorator {}
    }
}
