import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtWebView 1.1

Item {

	WebView {
		id: view
		anchors.fill: parent
		url: "file://" + RequestSaver.tempFilePath()
	}
}
