import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

ItemDelegate {
	id: control

	contentItem.implicitWidth: row.implicitWidth
	contentItem.implicitHeight: row.implicitHeight

	property string name
	property string time

	RowLayout {
		id: row

		Label {
			text: name
			Layout.fillWidth: true
		}

		Label {
			text: time
		}
	}
}
