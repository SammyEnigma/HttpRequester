import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../Tools"

Page {
	id: page
	background: Item { }

	contentItem: Flickable {
		clip: true
		contentWidth: width
		contentHeight: control.height

		ScrollBar.vertical: ScrollBar { }

		Control {
			id: control
			padding: 12
			rightPadding: 18
			width: parent.width
			contentItem: RequestInfoViewContent { }
		}
	}
}
