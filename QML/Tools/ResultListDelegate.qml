import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ItemDelegate {
	id: control

	property real elapsed
	property int requestIndex
	property bool done


	contentItem: RowLayout {
		id: row

		Label {
			Layout.fillWidth: true
			text: "Request " + requestIndex
		}

		Label {
			text: elapsed
		}

		Label {
			text: done
		}
	}
}
