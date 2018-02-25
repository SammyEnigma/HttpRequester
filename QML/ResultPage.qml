import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

import  "Tools"

Page {
	id: page
	objectName: "Result"
	background: Item { }

	header: TopBar {
		id: topBar
		title: "Results"

		ToolButton {
			text: "➞"
			rotation: 180
			parent: topBar.row
			font.pointSize: iconFont
			onClicked: stackView.pop()
		}
	}

	ColumnLayout {
		spacing: 0
		anchors.fill: parent

		TabBar {
			id: tabBar
			Layout.fillWidth: true
			currentIndex: swipeView.currentIndex

			TabButton {
				text: "Status"
			}

			TabButton {
				text: "Data"
			}
		}

		Rectangle {
			height: 1
			color: Material.accent
			Layout.fillWidth: true
		}

		SwipeView {
			id: swipeView
			Layout.fillWidth: true
			Layout.fillHeight: true
			currentIndex: tabBar.currentIndex

			ResultStatusView { }
			ResultInfoListVliew { }
		}
	}
}
