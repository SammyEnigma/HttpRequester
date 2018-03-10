import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Page {
	id: page
	objectName: "Splash"

	background: Rectangle {
		color: Material.background
	}

	Label {
		anchors.centerIn: parent
		text: "Http Requester"
		font.pointSize: splashFont
		color: Material.accent
	}

	Timer {
		repeat: false
		running: true
		interval: 2000
		onTriggered: stackView.replace(mainPage)
	}
}
