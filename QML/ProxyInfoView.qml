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
					text: "No Proxy"
					checked: true
				}

				RadioButton {
					text: "Http Proxy"
				}

				RadioButton {
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
					}

					InsertField {
						text: "Port"
						placeholder: "8080"
						Layout.fillWidth: true
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
					}

					InsertField {
						text: "Password"
						placeholder: "8080"
						Layout.fillWidth: true
						enabled: checkbox1.checked
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
