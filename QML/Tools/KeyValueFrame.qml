import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

RowLayout {
	property alias model: view.model

	signal addParameter()
	signal removeParameter(int index)

	Frame {
		padding: 0
		Layout.fillWidth: true

		contentItem: ListView {
			id: view
			clip: true
			implicitHeight: 40
			orientation: Qt.Horizontal

			delegate: Row {
				Label {
					id: label
					height: 40
					padding: 6
					rightPadding: 0
					text: nameRole + " : " + dataRole
					verticalAlignment: Text.AlignVCenter
				}

				ToolButton {
					icon.width: 20
					icon.height: 20
					icon.source: "qrc:/Images/Plus.png"

					padding: 0
					height: 40
					rotation: 45
					width: height

					anchors.verticalCenter: parent.verticalCenter
					onClicked: removeParameter(index)
				}

				Rectangle {
					width: 1
					color: label.linkColor
					height: parent.height - 2
					anchors.verticalCenter: parent.verticalCenter
				}
			}
		}
	}

	ToolButton {
		text: "+"
		font.pointSize: iconFont
		Layout.alignment: Qt.AlignVCenter
		onClicked: addParameter()
	}
}
