import QtQuick 2.7
import QtQuick.Controls 2.0

ContentFlickerView {
	label: Label {
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere

		text: {
			if (tabbar.currentIndex == 0)
				return page.info
			else if (tabbar.currentIndex == 1)
				return page.headers
			else if (tabbar.currentIndex == 2)
			{
				var answer = "Request Number: " + page.index + "\n"
				answer += "Time Elapsed: " + page.elapsed/1000 + " Seconds" + "\n"
				answer += "Request Success: " + (page.done ? "Succcessful":"Failed") + "\n"
				return answer
			}
		}
	}
}
