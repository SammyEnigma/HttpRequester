import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

ApplicationWindow {
	visible: true
	width: 640
	height: 480
	title: "REST Requester"

	property real smallFont: font.pointSize
	property real mediumFont: font.pointSize + 2
	property real largeFont: font.pointSize + 4
	property real iconFont: font.pointSize + 10
	property real splashFont: font.pointSize + 15

//	Material.theme: Material.Dark
	Material.accent: Material.primary
	Material.primary: Material.Red

	onClosing: {
		close.accepted = false
		var name = stackView.currentItem.objectName

		if (name == "Create" || name == "Result")
		{
			stackView.pop()
			RequestHolder.reset()
		}
		else
			close.accepted = true
	}

	StackView {
		id: stackView
		anchors.fill: parent
		initialItem: splashPage

		Component {
			id: splashPage
			SplashPage { }
		}

		Component {
			id: mainPage
			MainPage { }
		}

		Component {
			id: createPage
			CreatePage { }
		}

		Component {
			id: resultPage
			ResultPage { }
		}
	}
}
