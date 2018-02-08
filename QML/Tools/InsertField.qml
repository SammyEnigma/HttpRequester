import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Control {
	id: control

	implicitWidth: Math.max(background ? background.implicitWidth : 0,
							(contentItem ? contentItem.implicitWidth : 0) + leftPadding + rightPadding)
	implicitHeight: Math.max(background ? background.implicitHeight : 0,
							 (contentItem ? contentItem.implicitHeight : 0) + topPadding + bottomPadding)

	property string text
	property string placeholder
	property alias value: field.text

	contentItem: RowLayout {
		spacing: 10

		Label {
			id: label
			text: control.text
			Layout.fillHeight: true
			verticalAlignment: Text.AlignVCenter
		}

		TextField {
			id: field
			Layout.fillWidth: true
			placeholderText: placeholder
		}
	}
}
