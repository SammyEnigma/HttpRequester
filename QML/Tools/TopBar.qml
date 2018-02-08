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
		font.pointSize: largeFont
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
	}

	RowLayout {
		id: row
		anchors.right: parent.right
		anchors.verticalCenter: parent.verticalCenter
	}
}
