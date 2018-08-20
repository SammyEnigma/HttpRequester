import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

import "../Tools"

Page {
	id: page
	background: Item { }

	property int index: 0

	onInfoChanged: RequestSaver.saveToFile(info)

	property string info: RequestHandler.singleInfo
	property bool done: RequestHandler.singleFinished
	property int elapsed: RequestHandler.singleElapsed
	property string headers: RequestHandler.singleHeaders
	property int statusCode: RequestHandler.singleStatusCode
	property string statusMessage: RequestHandler.singleStatusMessage

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
					width: parent.width

					done: finishedRole
					elapsed: elapsedRole
					requestIndex: index + 1

					onClicked: {
						page.elapsed = elapsedRole
						page.index = index
						page.info = infoRole
						page.done = finishedRole
						page.headers = headersRole
						page.statusCode = statusCodeRole
						page.statusMessage = statusMessageRole
						resultStack.push(details)
					}

					Rectangle {
						height: 1
						parent: del
						width: parent.width*.9
						color: Material.accent
						anchors.bottom: parent.bottom
						visible: index != view.count-1
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
