import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import "Tools"

Page {
	background: Item { }

	header: ColumnLayout {
		spacing: 0

		TabBar {
			id: tabbar
			Layout.fillWidth: true
			currentIndex: done ? 0:3
			enabled: done

			onCurrentIndexChanged: {
				if (currentIndex == 0)
					stack.replace(dataView)
				else if (currentIndex == 1)
					stack.replace(webView)
				else if (currentIndex == 2)
					stack.replace(headerView)
				else if (currentIndex == 3)
					stack.replace(statusView)
			}

			TabButton {
				text: "Data"
			}

			TabButton {
				text: "Browser"
			}

			TabButton {
				text: "Headers"
			}

			TabButton {
				text: "Request Info"
			}
		}

		Rectangle {
			height: 1
			color: Material.accent
			Layout.fillWidth: true
		}
	}

	contentItem: StackView {
		id: stack
		initialItem: dataView

		Component {
			id: dataView
			ResultDataPage { }
		}

		Component {
			id: webView
			ResultWebPage { }
		}

		Component {
			id: headerView
			ResultHeaderPage { }
		}

		Component {
			id: statusView
			ResultStatusPage { }
		}
	}
}
