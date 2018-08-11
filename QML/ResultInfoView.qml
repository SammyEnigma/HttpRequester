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

			onCurrentIndexChanged: {
				if (currentIndex == 0)
					stack.replace(dataView)
				if (currentIndex == 1)
					stack.replace(headerView)
				if (currentIndex == 2)
					stack.replace(statusView)
			}

			TabButton {
				text: "Data"
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
			id: headerView
			ResultHeaderPage { }
		}

		Component {
			id: statusView
			ResultStatusPage { }
		}
	}

	Label {
		//		text: label.text.length ? "":"No Contents Available!"
		anchors.fill: parent
		elide: Text.ElideRight
		font.pointSize: mediumFont
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
	}
}
