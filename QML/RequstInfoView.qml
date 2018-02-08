import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "Tools"

Page {
	id: page
	background: Item { }

	ButtonGroup {
		buttons: [radio1, radio2]
	}

	contentItem: ColumnLayout {
		RowLayout {
			Layout.fillHeight: false

			RadioButton {
				id: radio1
				text: "Url"
			}

			InsertField {
				text: "Url"
				Layout.fillWidth: true
				placeholder: "http://example.com"
			}
		}

		RowLayout {
			Layout.fillHeight: false

			RadioButton {
				id: radio2
				text: "IP/Port"
			}

			InsertField {
				text: "Ip"
				Layout.fillWidth: true
				placeholder: "255.255.255.255"
			}

			InsertField {
				text: "Port"
				Layout.fillWidth: true
				placeholder: "8080"
			}
		}

		Item {
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
	}
}
