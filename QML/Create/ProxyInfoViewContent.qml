import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../Tools"

ColumnLayout {
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
				checked: RequestHolder.proxyType == 0
				onCheckedChanged: if (checked) RequestHolder.proxyType = 0
			}

			RadioButton {
				id: radio2
				text: "Http Proxy"
				checked: RequestHolder.proxyType == 1
				onCheckedChanged: if (checked) RequestHolder.proxyType = 1
			}

			RadioButton {
				id: radio3
				text: "Socks5 Proxy"
				checked: RequestHolder.proxyType == 2
				onCheckedChanged: if (checked) RequestHolder.proxyType = 2
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

					validator: RegExpValidator {
						regExp: /\d?\d?\d\.\d?\d?\d\.\d?\d?\d\.\d?\d?\d/
					}
				}

				InsertField {
					text: "Port"
					placeholder: "8080"
					Layout.fillWidth: true
					value: RequestHolder.proxyPort
					onValueChanged: RequestHolder.proxyPort = value

					validator: IntValidator {
						top: 65535
						bottom: 0
					}
				}
			}

			CheckBox {
				id: checkbox1
				leftPadding: 0
				bottomPadding: 0
				text: "Has Usernames"
				checked: RequestHolder.proxyHasUser
				onCheckedChanged: RequestHolder.proxyHasUser = checked
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
					placeholder: "something"
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
