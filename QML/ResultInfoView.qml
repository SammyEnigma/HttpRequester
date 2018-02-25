import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import "Tools"

Page {
	background: Item { }

	header: ResultListDelegate {
		id: del
		done: page.done
		elapsed: page.elapsed
		requestIndex: page.index

		Rectangle {
			height: 1
			parent: del
			width: parent.width
			color: Material.accent
			anchors.bottom: parent.bottom
		}
	}

	Flickable {
		anchors.fill: parent
		contentWidth: width
		contentHeight: label.height

		ScrollBar.vertical: ScrollBar { }

		Label {
			id: label
			padding: 12
			text: page.info
			width: parent.width
		}
	}
}
