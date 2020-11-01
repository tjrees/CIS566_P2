import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: converterWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Length Converter")

    TextField
    {
        x: 10
        y: 10
        id: kmInput
        text: ""
        readOnly: false
        cursorVisible: true
    }
    Text
    {
        x : converterWindow.width / 2
        y : 10
        id: kmLabel
        text: qsTr("Kilometer")
    }

    TextField
    {
        id: outputField
        x: 10
        y: kmInput.y + kmInput.height + 20
        readOnly: true
        text: ""
    }

    ComboBox
    {
        id: unitChoice
        x: converterWindow.width / 2
        y: kmInput.y + kmInput.height + 20
        editable: false
        model: ListModel
        {
            id: model
            ListElement { text: "Mile" }
            ListElement { text: "Yard" }
            ListElement { text: "Foot" }
        }
    }
    Button
    {
        id: convertButton
        x: 10
        y: outputField.y + outputField.y + 30
        text: "Convert"
        onClicked: {
            outputField.text = converterObject.convert(kmInput.text, unitChoice.currentText)
        }
    }
}
