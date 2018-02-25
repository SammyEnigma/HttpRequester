import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import "Tools"

Page {
	id: page
	objectName: "Create"
	background: Item { }

	property bool saved: false

	header: TopBar {
		id: topBar
		title: "Create Request"

		ToolButton {
			text: "➞"
			parent: topBar.row
			font.pointSize: iconFont

			onClicked: {
				if (!saved) {
					saved = true;
					RequestSaver.saveRequest()
				}

				RequestHandler.begin()
				stackView.replace(resultPage)
			}
		}

		ToolButton {
			text: "➞"
			rotation: 90
			parent: topBar.row
			font.pointSize: iconFont

			onClicked: {
				if (saved)
					return;

				saved = true;
				RequestSaver.saveRequest()
			}
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
				text: "Request"
			}

			TabButton {
				text: "General"
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

			RequstInfoView { }
			GeneralInfoView { }
			ProxyInfoView { }
		}
	}
}
