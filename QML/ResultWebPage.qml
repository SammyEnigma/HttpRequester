import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebEngine 1.7

Item {

	WebEngineView {
		id: view
		anchors.fill: parent
		backgroundColor: Material.background
		url: "file://" + RequestSaver.tempFilePath()
	}
}
