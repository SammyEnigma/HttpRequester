import QtQuick 2.7
import QtQuick.Controls 2.3

import "Tools"

Page {
	id: page
	objectName: "Main"
	background: Item { }

	header: TopBar {
		id: topBar
		title: "Http Requester"

		ToolButton {
			id: menuButton
			parent: topBar.row
			font.pointSize: iconFont
//			text: "M"
			icon.source: "qrc:/Images/Menu.png"

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
			parent: topBar.row
			font.pointSize: iconFont
//			text: "A"
			icon.source: "qrc:/Images/Plus.png"

			onClicked: {
				stackView.push(createPage)
				RequestHolder.reset()
			}
		}
	}

	RecentRequestsView {
		anchors.fill: parent
	}
}
