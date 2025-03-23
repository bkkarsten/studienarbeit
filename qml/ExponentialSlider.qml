import QtQuick
import QtCore
import QtQuick.Controls 2.5

// A slider that operates on an exponential scale.
Slider {
    id: exponentialSlider
    value: 0

    property real min
    property real max

    from: Math.log(min)
    to: Math.log(max)

    readonly property real expValue: Math.exp(value)

    function setExpValue(newValue) { value = Math.log(newValue); }
}