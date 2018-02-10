import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

import "Tools"

Item {
	id: item

	ListView {
		id: view
		anchors.fill: parent
		model: RequestSaverModel

		delegate: RecentListDelegate {
			id: del
			name: nameRole
			time: timeRole

			Rectangle {
				height: 1
				parent: del
				width: parent.width*.9
				color: Material.accent
				anchors.horizontalCenter: parent.horizontalCenter
			}
		}
	}

	Label {
		visible: !view.count
		text: "No Requests Yet"
		anchors.centerIn: parent
		font.pointSize: mediumFont
	}
}
