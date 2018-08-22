import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

ItemDelegate {
	id: control

	property bool done
	property real elapsed
	property int requestIndex

	contentItem: RowLayout {
		id: row

		Label {
			Layout.fillWidth: true
			text: "Request " + requestIndex
		}

		Label {
			text: (elapsed/1000).toFixed(3) + " Seconds"
		}

		Label {
			text: done ? "Succeeded":"Failed"
		}
	}
}
