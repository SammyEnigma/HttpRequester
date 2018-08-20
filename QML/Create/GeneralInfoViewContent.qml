import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../Tools"

ColumnLayout {
	ButtonGroup {
		buttons: [radio1, radio2]
	}

	Label {
		text: "Address"
		font.pointSize: mediumFont
	}

	RowLayout {
		Layout.leftMargin: 12
		Layout.fillHeight: false

		RadioButton {
			id: radio1
			text: "Url"
			implicitWidth: 120
			checked: RequestHolder.addressType == false
			onCheckedChanged: RequestHolder.addressType = !checked
		}

		InsertField {
			text: "Url"
			placeholder: "http://example.com"

			validator: RegExpValidator {
				regExp: /[-a-zA-Z0-9@:%._\+~#=]{2,256}\.[a-z]{2,6}\b([-a-zA-Z0-9@:%_\+.~#?&//=]*)/
			}

			Layout.fillWidth: true
			enabled: radio1.checked
			value: RequestHolder.addressUrl
			onValueChanged: RequestHolder.addressUrl = value
		}
	}

	RowLayout {
		Layout.leftMargin: 12
		Layout.fillHeight: false

		RadioButton {
			id: radio2
			text: "IP/Port"
			implicitWidth: 120
			checked: RequestHolder.addressType == true
			onCheckedChanged: RequestHolder.addressType = checked
		}

		InsertField {
			text: "IP"
			placeholder: "255.255.255.255"

			validator: RegExpValidator {
				regExp: /\d?\d?\d\.\d?\d?\d\.\d?\d?\d\.\d?\d?\d/
			}

			Layout.rightMargin: 18
			Layout.fillWidth: true
			enabled: radio2.checked
			value: RequestHolder.addressIp
			onValueChanged: RequestHolder.addressIp = value
		}

		InsertField {
			text: "Port"
			placeholder: "8080"

			validator: IntValidator {
				top: 65535
				bottom: 0
			}

			Layout.fillWidth: true
			enabled: radio2.checked
			value: RequestHolder.addressPort
			onValueChanged: RequestHolder.addressPort = value
		}
	}

	Label {
		text: "General"
		Layout.topMargin: 12
		font.pointSize: mediumFont
	}

	RowLayout {
		spacing: 18
		Layout.leftMargin: 18
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

	RowLayout {
		spacing: 18
		Layout.leftMargin: 18
		Layout.fillHeight: false

		RowLayout {
			Label {
				text: "Requests Count"
			}

			SpinBox {
				from: 1
				to: 100
				editable: true
				Layout.fillWidth: true
				value: RequestHolder.requestCount
				onValueChanged: RequestHolder.requestCount = value
			}
		}

		RowLayout {
			Label {
				text: "Request Timeout"
			}

			SpinBox {
				from: -1
				to: 300
				editable: true
				Layout.fillWidth: true
				value: RequestHolder.requestTimeout
				onValueChanged: RequestHolder.requestTimeout = value
			}
		}
	}

	Item {
		Layout.fillWidth: true
		Layout.fillHeight: true
	}
}
