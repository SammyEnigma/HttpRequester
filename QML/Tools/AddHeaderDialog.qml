import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Popup {
	id: popup

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	onClosed: {
		keyField.clear()
		valueField.clear()
	}

	contentItem: ColumnLayout {
		Label {
			color: Material.accent
			font.pointSize: mediumFont
			text: "Add Header"
			Layout.fillWidth: true
			horizontalAlignment: Text.AlignHCenter
			bottomPadding: 6
		}

		RowLayout {
			spacing: 12
			Layout.fillHeight: false

			TextField {
				id: keyField
				placeholderText: "Key"
				Layout.fillWidth: true
			}

			TextField {
				id: valueField
				placeholderText: "Value"
				Layout.fillWidth: true
			}
		}

		RowLayout {
			Layout.fillHeight: false

			Item {
				Layout.fillHeight: true
				Layout.fillWidth: true
			}

			Button {
				flat: true
				text: "Cancel"
				onClicked: popup.close()
			}

			Button {
				flat: true
				text: "Confirm"
				enabled: keyField.text && valueField.text

				onClicked: {
					popup.close()
					RequestHolder.addHeader(keyField.text, valueField.text)
				}
			}
		}
	}
}
