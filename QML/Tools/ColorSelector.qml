import QtQuick 2.10
import QtQuick.Controls 2.3

Control {
	id: control
	padding: 8
	leftPadding: 12
	rightPadding: 12

	property var colors: [
		"#ffc107", "#2196f3", "#607d8b", "#795548", "#00bcd4", "#ff5722",
		"#673ab7", "#4caf50", "#9e9e9e", "#3f51b5", "#03a9f4", "#8bc34a",
		"#cddc39", "#ff9800", "#e91e63", "#9c27b0", "#f44336", "#009688",
		"#ffeb3b"
	]

	property color currentColor: colors[currentIndex]
	property alias currentIndex: pathview.currentIndex

	contentItem: Item {
		id: item
		implicitHeight: 40
		implicitWidth: 200

		PathView {
			id: pathview

			pathItemCount: width/height
			model: control.colors
			height: parent.height
			anchors.centerIn: parent
			preferredHighlightBegin: .5
			preferredHighlightEnd: .5
			snapMode: PathView.SnapToItem

			width: Math.min(model.length*item.height, item.width)

			path: Path {
				startX: 0; startY: pathview.height/2
				PathLine { x: pathview.width; y: pathview.height/2 }
			}

			delegate: Rectangle {
				width: item.height
				height: item.height
				color: modelData

				MouseArea {
					anchors.fill: parent
					onClicked: pathview.currentIndex = index
				}
			}
		}

		Rectangle {
			width: 4
			color: "white"
			height: parent.height
			anchors.centerIn: parent

			Rectangle {
				width: 2
				color: "black"
				height: parent.height
				anchors.centerIn: parent
			}
		}
	}
}




