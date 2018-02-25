import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
	id: item

	ColumnLayout {
		spacing: 12
		anchors.centerIn: parent

		Label {
			Layout.fillWidth: true
			font.pointSize: largeFont
			horizontalAlignment: Text.AlignHCenter

			text: RequestHandler.state == 1 ? "Please Wait":"Done!" +
				  " (" + (RequestHandler.currentRequest + 1) +
				  "/" + RequestHandler.requestsCount + ")"
		}

		ProgressBar {
			from: 0
			indeterminate: to == 1 && RequestHandler.state == 1
			Layout.fillWidth: true
			to: RequestHandler.requestsCount
			value: RequestHandler.currentRequest + 1
		}
	}
}
