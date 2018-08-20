import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import "../Tools"

ContentFlickerView {

	label: Column {
		spacing: 6

		Repeater {
			model: {
				var a = page.headers.split('\n')
				a.sort()
				return a
			}

			delegate: RowLayout {
				spacing: 15

				Label {
					padding: 4
					text: modelData.split(": ")[0]

					background: Rectangle {
						color: Material.accent

						Rectangle {
							width: height
							color: parent.color
							height: parent.height/1.41

							rotation: 45
							anchors.horizontalCenter: parent.right
							anchors.verticalCenter: parent.verticalCenter
						}
					}
				}

				Label {
					padding: 6
					text: modelData.split(": ")[1]
				}
			}
		}
	}
}
