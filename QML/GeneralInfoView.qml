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
		RowLayout {
			spacing: 18
			Layout.fillHeight: false

			InsertField {
				text: "Name"
				placeholder: "Optional"
				Layout.fillWidth: true
				value: RequestHolder.requestName
				onValueChanged: RequestHolder.requestName = value
			}

			InsertField {
				text: "Description"
				placeholder: "Optional"
				Layout.fillWidth: true
				value: RequestHolder.requestDescription
				onValueChanged: RequestHolder.requestDescription = value
			}
		}

		InsertField {
			implicitWidth: 160
			text: "Requests Count"
			value: RequestHolder.requestCount
			horizontalAlignment: Text.AlignHCenter
			onValueChanged: RequestHolder.requestCount = value

			validator: IntValidator {
				bottom: 1
			}
		}

		InsertField {
			implicitWidth: 160
			text: "Request Timeout"
			horizontalAlignment: Text.AlignHCenter
			value: RequestHolder.requestTimeout
			onValueChanged: RequestHolder.requestTimeout = value

			validator: IntValidator {
				top: 300
				bottom: 5
			}
		}

		Item {
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
	}
}
