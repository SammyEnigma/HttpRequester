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
			id: menuButton
			text: "⋮"
			parent: topBar.row
			font.pointSize: iconFont
			onClicked: menu.open()

			Menu {
				id: menu
				dim: false
				modal: true
				y: parent.height/2
				x: -width+parent.width/2
				closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape

				MenuItem {
					text: "Settings"
					onClicked: stackView.push(themePage)
				}

				MenuItem {
					text: "About"
					onClicked: stackView.push(aboutPage)
				}

				MenuItem {
					text: "Exit"
					onClicked: Qt.quit()
				}
			}
		}

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
