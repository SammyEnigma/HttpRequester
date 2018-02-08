import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "Tools"

Page {
	id: page
	padding: 12
	rightPadding: 18
	background: Item { }

	contentItem: ColumnLayout {
		InsertField {
			implicitWidth: 160
			value: "1"
			text: "Requests Count"
			horizontalAlignment: Text.AlignHCenter
		}

		InsertField {
			implicitWidth: 160
			value: "30"
			text: "Request Timeout"
			horizontalAlignment: Text.AlignHCenter
		}

		Item {
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
	}
}
