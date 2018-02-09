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
		buttons: row.children
		property int currentIndex: RequestHolder.proxyType

		onCheckedButtonChanged: {
			if (checkedButton == radio1)
				currentIndex = 0
			else if (checkedButton == radio2)
				currentIndex = 1
			else if (checkedButton == radio3)
				currentIndex = 2
		}

		onCurrentIndexChanged: {
			if (currentIndex == 0)
				radio1.checked = true
			else if (currentIndex == 1)
				radio2.checked = true
			else if (currentIndex == 2)
				radio3.checked = true
		}
	}

	contentItem: ColumnLayout {
		ColumnLayout {
			Layout.fillHeight: false

			Label {
				text: "Type"
				font.pointSize: mediumFont
			}

			RowLayout {
				id: row
				Layout.leftMargin: 12
				Layout.fillHeight: false

				RadioButton {
					id: radio1
					text: "No Proxy"
					checked: true
				}

				RadioButton {
					id: radio2
					text: "Http Proxy"
				}

				RadioButton {
					id: radio3
					text: "Socks5 Proxy"
				}
			}
		}

		ColumnLayout {
			Layout.fillHeight: false

			Label {
				text: "Information"
				font.pointSize: mediumFont
			}

			ColumnLayout {
				Layout.leftMargin: 12
				Layout.fillHeight: false

				RowLayout {
					spacing: 18
					Layout.fillHeight: false

					InsertField {
						text: "Host"
						Layout.fillWidth: true
						placeholder: "255.255.255.255"
						value: RequestHolder.proxyHost
						onValueChanged: RequestHolder.proxyHost = value
					}

					InsertField {
						text: "Port"
						placeholder: "8080"
						Layout.fillWidth: true
						value: RequestHolder.proxyPort
						onValueChanged: RequestHolder.proxyPort = value
					}
				}

				CheckBox {
					id: checkbox1
					leftPadding: 0
					bottomPadding: 0
					text: "Has Usernames"
				}

				RowLayout {
					spacing: 18
					Layout.leftMargin: 12
					Layout.fillHeight: false

					InsertField {
						text: "Username"
						placeholder: "someone"
						Layout.fillWidth: true
						enabled: checkbox1.checked
						value: RequestHolder.proxyUsername
						onValueChanged: RequestHolder.proxyUsername = value
					}

					InsertField {
						text: "Password"
						placeholder: "8080"
						Layout.fillWidth: true
						enabled: checkbox1.checked
						value: RequestHolder.proxyPassword
						onValueChanged: RequestHolder.proxyPassword = value
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
