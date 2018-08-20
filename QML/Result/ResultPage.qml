import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

import "../Tools"

Page {
	id: page
	objectName: "Result"
	background: Item { }

	header: TopBar {
		id: topBar
		title: "Results"

		ToolButton {
			parent: topBar.row
			font.pointSize: iconFont
			//			text: "B"
			icon.source: "qrc:/Images/Back.png"

			onClicked: {
				if(resultList.resultStack.depth > 1)
					resultList.resultStack.pop()
				else
					stackView.pop()
			}
		}
	}

	SwipeView {
		id: swipeView
		anchors.fill: parent
		interactive: false

		ResultStatusView { }
		ResultInfoListView { id: resultList }
	}

	Connections {
		target: RequestHandler
		onStateChanged: if (state == 2) swipeView.incrementCurrentIndex()
	}
}
