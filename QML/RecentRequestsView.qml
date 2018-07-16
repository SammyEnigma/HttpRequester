import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

import "Tools"

Item {
	id: item

	ListView {
		id: view
		anchors.fill: parent
		model: RequestSaverModel
		ScrollBar.vertical: ScrollBar { }

		delegate: RecentListDelegate {
			id: del
			time: timeRole
			width: parent.width
			name: titleRole ? titleRole:"Unnamed"

			onClicked: {
				RequestSaver.loadRequest(idRole)
				stackView.push(createPage)
			}

			Rectangle {
				height: 1
				parent: del
				width: parent.width*.9
				color: Material.accent
				anchors.bottom: parent.bottom
				visible: index != view.count
				anchors.horizontalCenter: parent.horizontalCenter
			}
		}
	}

	ColumnLayout {
		visible: !view.count
		anchors.centerIn: parent

		Label {
			text: "No Requests Yet"
			font.pointSize: mediumFont
			Layout.fillWidth: true
			horizontalAlignment: Text.AlignHCenter
		}

		Button {
			text: "New Request"
			Layout.fillWidth: true
			Material.background: Material.primary

			onClicked: {
				stackView.push(createPage)
				RequestHolder.reset()
			}
		}
	}
}
