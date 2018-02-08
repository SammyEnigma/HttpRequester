import QtQuick 2.7
import QtQuick.Controls 2.0

import "Tools"

Page {
	id: page
	objectName: "Main"
	background: Item { }

	header: TopBar {
		id: topBar
		title: "REST Requester"

		ToolButton {
			text: "+"
			parent: topBar.row
			font.pointSize: iconFont
			onClicked: stackView.push(createPage)
		}
	}

	RecentRequestsView {
		anchors.fill: parent
	}
}
