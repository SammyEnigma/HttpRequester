import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import "Tools"

Page {
	id: page
	objectName: "Theme"
	background: Item { }

	header: TopBar {
		id: topBar
		title: "Settings"

		ToolButton {
			text: "➞"
			rotation: 180
			parent: topBar.row
			font.pointSize: iconFont
			onClicked: stackView.pop()
		}
	}

	ColumnLayout {
		anchors.fill: parent

		RowLayout {
			spacing: 18
			Layout.fillHeight: false

			Label {
				text: "Theme Color"
			}

			ColorSelector {
				Layout.fillWidth: true
				currentIndex: colors.indexOf(windowThemeColor)
				onCurrentColorChanged: windowThemeColor = currentColor
			}
		}

		RowLayout {
			spacing: 18
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

		Item {
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
	}
}
