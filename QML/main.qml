import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Window 2.2
import Qt.labs.settings 1.0

ApplicationWindow {
	id: w
	visible: true
	width: 640
	height: 480
	title: "Http Requester"

	property real smallFont: font.pointSize
	property real mediumFont: font.pointSize + 2
	property real largeFont: font.pointSize + 4
	property real iconFont: font.pointSize + 10
	property real splashFont: font.pointSize + 15

	Settings {
		property alias x: w.x
		property alias y: w.y
		property alias width: w.width
		property alias height: w.height
		property alias darkTheme: w.windowDarkTheme
		property alias showSplash: w.windowShowSplash
		property alias themeColor: w.windowThemeColor

	}

	property bool windowDarkTheme: false
	property bool windowShowSplash: true
	property color windowThemeColor: "#00bcd4"

	Component.onCompleted: RequestHandler.setTopColor(windowThemeColor)
	onWindowThemeColorChanged: RequestHandler.setTopColor(windowThemeColor)


	Material.accent: Material.primary
	Material.primary: windowThemeColor
	Material.theme: windowDarkTheme ? Material.Dark:Material.Light

	onClosing: {
		close.accepted = false
		var name = stackView.currentItem.objectName

		if (addPostDialog.visible)
			addPostDialog.close()
		else if (name != "Splash" && name != "Main")
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
		initialItem: windowShowSplash ? splashPage:mainPage

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

		Component {
			id: aboutPage
			AboutPage { }
		}

		Component {
			id: themePage
			ThemePage { }
		}
	}

	AddPostDialog {
		id: addPostDialog
		modal: true
	}
}
