import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "Tools"

Page {
	id: page
	padding: 12
	rightPadding: 18
	background: Item { }

	ButtonGroup {
		buttons: [radio1, radio2]
	}

	contentItem: ColumnLayout {
		ColumnLayout {
			Layout.fillHeight: false

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
					onCheckedChanged: RequestHolder.addressType = false
				}

				InsertField {
					text: "Url"
					placeholder: "http://example.com"

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
					onCheckedChanged: RequestHolder.addressType = true
				}

				InsertField {
					text: "IP"
					placeholder: "255.255.255.255"

					Layout.rightMargin: 18
					Layout.fillWidth: true
					enabled: radio2.checked
					value: RequestHolder.addressIp
					onValueChanged: RequestHolder.addressIp = value
				}

				InsertField {
					text: "Port"
					placeholder: "8080"
					Layout.fillWidth: true
					enabled: radio2.checked
					value: RequestHolder.addressPort
					onValueChanged: RequestHolder.addressPort = value
				}
			}
		}

		ColumnLayout {
			Layout.fillHeight: false

			CheckBox {
				id: checkbox1
				text: "Post Data"
				leftPadding: 0
				font.pointSize: mediumFont
				checked: RequestHolder.hasPostData
				onCheckedChanged: RequestHolder = checked
			}

			Frame {
				enabled: checkbox1.checked
				padding: 0
				Layout.leftMargin: 12
				Layout.fillWidth: true

				contentItem: ListView {
					model: 5
					clip: true
					implicitHeight: 40
					orientation: Qt.Horizontal

					delegate: Label {
						id: label
						height: 40
						padding: 6
						text: "\"name\" : \"shahriar\" "
						verticalAlignment: Text.AlignVCenter

						Rectangle {
							width: 1
							parent: label
							color: label.linkColor
							height: parent.height - 2
							anchors.right: parent.right
							anchors.verticalCenter: parent.verticalCenter
						}
					}
				}
			}
		}

		Item {
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
	}
}
