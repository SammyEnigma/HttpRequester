import QtQuick 2.7
import QtQuick.Controls 2.3
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
			parent: topBar.row
			font.pointSize: iconFont
			//			text: "B"
			icon.source: "qrc:/Images/Back.png"

			onClicked: stackView.pop()
		}

		ToolButton {
			text: "Next"
			parent: topBar.row

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
			text: "Save"
			parent: topBar.row

			onClicked: {
				if (saved)
					return;

				saved = true;
				RequestSaver.saveRequest()
			}
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
