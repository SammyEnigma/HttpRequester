import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import "../Tools"

Page {
	id: page
	objectName: "Create"
	background: Item { }

	property bool saved: false
	property string content: "This is an open-source software written with Qt framework that deploys Qt projects on linux operating systems.\n\nThis software is written by Shahriar Rezghi (shahriar25.ss@gmail.com).\n\nCopyright (C) 2018  Shahriar Rezghi\n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details."

	header: TopBar {
		id: topBar
		title: "About"

		ToolButton {
			parent: topBar.row
			font.pointSize: iconFont
			//			text: "B"
			icon.source: "qrc:/Images/Back.png"

			onClicked: stackView.pop()
		}
	}

	contentItem: Flickable {
		clip: true
		contentWidth: width
		contentHeight: control.height

		ScrollBar.vertical: ScrollBar { }

		Control {
			id: control
			padding: 20
			width: parent.width

			contentItem: RowLayout {
				id: row
				spacing: 30
				Layout.leftMargin: 10
				width: parent.width

				Control {
					implicitWidth: 120
					implicitHeight: 120

					contentItem: Image {
						anchors.fill: parent
						source: "qrc:/Images/icon.png"

						sourceSize.width: width
						sourceSize.height: height
					}
				}

				Label {
					text: content
					Layout.fillWidth: true
					wrapMode: Text.WrapAtWordBoundaryOrAnywhere
				}
			}
		}
	}
}
