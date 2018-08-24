import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import QtQuick.Window 2.3

import "../Tools"

Page {
	id: page
	objectName: "Theme"
	background: Item { }

	header: TopBar {
		id: topBar
		title: "Settings"

		ToolButton {
			parent: topBar.row
			font.pointSize: iconFont
			//			text: "B"
			icon.source: "qrc:/Images/Back.png"

			onClicked: stackView.pop()
		}
	}

	contentItem: Flickable {
		clip: true
		contentWidth: width
		contentHeight: control.height

		ScrollBar.vertical: ScrollBar { }

		Control {
			id: control
			padding: 20
			width: parent.width

			contentItem: ColumnLayout {
				spacing: 10

				RowLayout {
					spacing: 18
					Layout.fillHeight: false

					Label {
						leftPadding: 6
						text: "Theme Color"
					}

					ColorSelector {
						Layout.fillWidth: true
						currentIndex: colors.indexOf(windowThemeColor)
						onCurrentColorChanged: windowThemeColor = currentColor
					}
				}

				RowLayout {
					Layout.fillHeight: false
					Switch {
						text: "Dark Theme"
						Layout.fillWidth: true
						checked: windowDarkTheme
						onCheckedChanged: windowDarkTheme = checked
					}

					Switch {
						Layout.fillWidth: true
						text: "Show Splash Screen"
						checked: windowShowSplash
						onCheckedChanged: windowShowSplash = checked
					}
				}

				Button {
					Material.background: Material.primary
					text: "Reset Size and Position of This Window"

					onClicked: {
						w.width = 640
						w.height = 480
						w.x = (Screen.desktopAvailableWidth - w.width) / 2
						w.y = (Screen.desktopAvailableHeight - w.height) / 2
					}
				}

				Item {
					Layout.fillWidth: true
					Layout.fillHeight: true
				}
			}
		}
	}
}
