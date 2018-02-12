import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import "Tools"

Page {
	id: page

	property int index: 0
	property string info: RequestHandler.singleInfo
	property bool done: RequestHandler.singleFinished
	property int elapsed: RequestHandler.singleElapsed

	StackView {
		id: resultStack
		anchors.fill: parent
		initialItem: RequestHandler.requestsCount == 1 ? details:listView

		Component {
			id: listView

			ListView {
				id: view
				model: RequestHandlerModel
				ScrollBar.vertical: ScrollBar { }

				delegate: ResultListDelegate {
					id: del
					elapsed: elapsedRole
					requestIndex: index + 1
					done: finishedRole

					onClicked: {
						page.elapsed = elapsedRole
						page.index = index
						page.info = infoRole
						page.done = finishedRole
						resultStack.push(details)
					}

					Rectangle {
						height: 1
						parent: del
						width: parent.width*.9
						color: Material.accent
						anchors.bottom: parent.bottom
						visible: index != view.count
						anchors.horizontalCenter: parent.horizontalCenter
					}
				}
			}
		}

		Component {
			id: details
			ResultInfoView { }
		}
	}
}
