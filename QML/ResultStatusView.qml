import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
	id: item

	ColumnLayout {
		spacing: 12
		anchors.centerIn: parent

		Label {
			text: "Please Wait(4/5)"
			Layout.fillWidth: true
			font.pointSize: largeFont
			horizontalAlignment: Text.AlignHCenter
		}

		ProgressBar {
			value: .8
			Layout.fillWidth: true
		}
	}
}
