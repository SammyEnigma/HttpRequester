import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ToolBar {
	id: control

	property string title
	property alias row: row

	Label {
		id: label
		text: control.title
		anchors.fill: parent
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		font.pointSize: control.font.pointSize + 5
	}

	RowLayout {
		id: row
		anchors.right: parent.right
		anchors.verticalCenter: parent.verticalCenter
	}
}
