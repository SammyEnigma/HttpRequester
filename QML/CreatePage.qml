import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import "Tools"

Page {
	id: page
	objectName: "Create"
	background: Item { }

	header: TopBar {
		id: topBar
		title: "Create Request"

		ToolButton {
			text: "➞"
			parent: topBar.row
			font.pointSize: iconFont
			onClicked: stackView.replace(resultPage)
		}

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
				text: "General"
			}

			TabButton {
				text: "Request"
			}

			TabButton {
				text: "Proxy"
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

			GeneralInfoView { }
			RequstInfoView { }
			ProxyInfoView { }
		}
	}
}
