import QtQuick 2.7
import QtQuick.Controls 2.0

ContentFlickerView {
	label: Label {
		text: page.info
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
	}
}