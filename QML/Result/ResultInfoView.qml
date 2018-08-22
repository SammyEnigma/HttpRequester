import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import "../Tools"

Page {
	background: Item { }

	header: ColumnLayout {
		spacing: 0

		TabBar {
			id: tabbar
			Layout.fillWidth: true
			currentIndex: page.done ? (page.info ? 0:2):3

			TabButton {
				text: "Data"
				enabled: done && page.info
				onClicked: if (tabbar.currentIndex != 0) stack.replace(dataView)
			}

			TabButton {
				text: "Browser"
				enabled: done && page.info
				onClicked: stack.replace(webView)
			}

			TabButton {
				text: "Headers"
				enabled: done
				onClicked: stack.replace(headerView)
			}

			TabButton {
				text: "Request Info"
				onClicked: stack.replace(statusView)
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
		initialItem: {
			print(page.done)
			page.done ? (page.info ? dataView:headerView):statusView
		}

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
