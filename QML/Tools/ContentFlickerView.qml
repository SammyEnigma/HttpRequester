import QtQuick 2.7
import QtQuick.Controls 2.0

Flickable {
	clip: true
	contentWidth: width
	contentHeight: control.height

	ScrollBar.vertical: ScrollBar { }

	property alias label: control.contentItem

	Control {
		id: control
		padding: 12
		width: parent.width
	}
}
