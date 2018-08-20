import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import "../Tools"

ColumnLayout {
	spacing: 10

	RowLayout {
		Layout.fillHeight: false

		CheckBox {
			id: checkbox2
			font.pointSize: mediumFont

			text: "Headers"

			checked: RequestHolder.hasHeader
			onCheckedChanged: RequestHolder.hasHeader = checked
		}

		KeyValueFrame {
			Layout.fillWidth: true
			enabled: checkbox2.checked

			model: RequestHolderHeaderModel
			onAddParameter: addHeaderDialog.open()
			onRemoveParameter: RequestHolder.removeHeader(index)
		}
	}

	Label {
		text: "Request Type"
		Layout.topMargin: 12
		font.pointSize: mediumFont
	}

	RowLayout {
		Layout.leftMargin: 12
		Layout.fillHeight: false

		RadioButton {
			topPadding: 6
			bottomPadding: 6

			text: "Get Request"
			Layout.fillWidth: true
			checked: RequestHolder.requestType == 0
			onCheckedChanged: if (checked) RequestHolder.requestType = 0
		}

		RadioButton {
			topPadding: 6
			bottomPadding: 6

			text: "Head Request"
			Layout.fillWidth: true
			checked: RequestHolder.requestType == 1
			onCheckedChanged: if (checked) RequestHolder.requestType = 1
		}

		RadioButton {
			topPadding: 6
			bottomPadding: 6

			text: "Delete Request"
			Layout.fillWidth: true
			checked: RequestHolder.requestType == 2
			onCheckedChanged: if (checked) RequestHolder.requestType = 2
		}
	}

	RadioButton {
		id: postRadio
		topPadding: 6
		bottomPadding: 6

		text: "Post Request"
		Layout.leftMargin: 12
		checked: RequestHolder.requestType == 3
		onCheckedChanged: if (checked) RequestHolder.requestType = 3
	}

	KeyValueFrame {
		Layout.leftMargin: 24
		Layout.fillWidth: true
		enabled: postRadio.checked

		model: RequestHolderPostModel
		onAddParameter: addPostDialog.open()
		onRemoveParameter: RequestHolder.removePostParameter(index)
	}

	RadioButton {
		id: putRadio
		topPadding: 6
		bottomPadding: 6

		text: "Put Request"
		Layout.leftMargin: 12
		checked: RequestHolder.requestType == 4
		onCheckedChanged: if (checked) RequestHolder.requestType = 4
	}

	RowLayout {
		enabled: putRadio.checked

		TextArea {
			topPadding: 0
			Layout.leftMargin: 24
			Layout.rightMargin: 12
			Layout.fillWidth: true
			text: RequestHolder.putData
			onTextChanged: RequestHolder.putData = text
		}

		Button {
			text: "From File"
			onClicked: fileDialog.open()
			Material.background: Material.primary
		}
	}

	Item {
		Layout.fillWidth: true
		Layout.fillHeight: true
	}

	FileDialog {
		id: fileDialog
		onAccepted: RequestHolder.readPutDataFromFile(fileUrl)
	}
}
