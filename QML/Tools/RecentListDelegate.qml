import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ItemDelegate {
	id: control

//	contentItem.implicitWidth: row.implicitWidth
//	contentItem.implicitHeight: row.implicitHeight

	property string name
	property string time

	contentItem: RowLayout {
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
