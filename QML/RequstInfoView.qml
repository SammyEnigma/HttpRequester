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
		}

		ColumnLayout {
			Layout.fillHeight: false

			RowLayout {
				Layout.fillHeight: false

				CheckBox {
					id: checkbox1
					leftPadding: 0
					font.pointSize: mediumFont

					text: "Post Data"
					Layout.fillWidth: true

					checked: RequestHolder.hasPostData
					onCheckedChanged: RequestHolder.hasPostData = checked
				}

				ToolButton {
					text: "+"
					enabled: checkbox1.checked
					font.pointSize: iconFont
					Layout.alignment: Qt.AlignVCenter
					onClicked: addPostDialog.open()
				}
			}

			Frame {
				enabled: checkbox1.checked
				padding: 0
				Layout.leftMargin: 12
				Layout.fillWidth: true

				contentItem: ListView {
					clip: true
					implicitHeight: 40
					orientation: Qt.Horizontal
					model: RequestHolderPostModel

					delegate: Row {
						Label {
							id: label
							height: 40
							padding: 6
							rightPadding: 0
							text: nameRole + " : " + dataRole
							verticalAlignment: Text.AlignVCenter
						}

						ToolButton {
							text: "-"
							height: 40
							font.pointSize: iconFont
							anchors.verticalCenter: parent.verticalCenter
							onClicked: RequestHolder.removePostParameter(index)
						}

						Rectangle {
							width: 1
							color: label.linkColor
							height: parent.height - 2
							anchors.verticalCenter: parent.verticalCenter
						}
					}
				}
			}
		}

		ColumnLayout {
			Layout.fillHeight: false

			RowLayout {
				Layout.fillHeight: false

				CheckBox {
					id: checkbox2
					leftPadding: 0
					font.pointSize: mediumFont

					text: "Headers"
					Layout.fillWidth: true

					checked: RequestHolder.hasHeader
					onCheckedChanged: RequestHolder.hasHeader = checked
				}

				ToolButton {
					text: "+"
					enabled: checkbox2.checked
					font.pointSize: iconFont
					Layout.alignment: Qt.AlignVCenter
					onClicked: addPostDialog.open()
				}
			}

			Frame {
				enabled: checkbox2.checked
				padding: 0
				Layout.leftMargin: 12
				Layout.fillWidth: true

				contentItem: ListView {
					clip: true
					implicitHeight: 40
					orientation: Qt.Horizontal
					model: RequestHolderPostModel

					delegate: Row {
						Label {
							id: label1
							height: 40
							padding: 6
							rightPadding: 0
							text: nameRole + " : " + dataRole
							verticalAlignment: Text.AlignVCenter
						}

						ToolButton {
							text: "-"
							height: 40
							font.pointSize: iconFont
							anchors.verticalCenter: parent.verticalCenter
							onClicked: RequestHolder.removeHeader(index)
						}

						Rectangle {
							width: 1
							color: label1.linkColor
							height: parent.height - 2
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
