import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.2

Window {
    id: root

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ChartView {
        id: chart
        anchors.fill: parent

//        DateTimeAxis {
//            id: axisX
//            format: "HH:mm:ss"
//        }

        ValueAxis {
            id: axisX
            min: 0
            max: 100
        }

        ValueAxis {
            id: axisY
            min: 0
            max: 2
        }

        ScatterSeries {
            id: line
            axisX: axisX
            axisY: axisY
            markerSize: 5
//            style: Qt.DotLine
        }
//        LineSeries{
//            id: line2
//            axisX: axisX
//            axisY: axisY
//        }

        VXYModelMapper {
            id: modelMapper
            model: lineModel // QStandardModel in C++
            series: line
            firstRow: 1
            xColumn: 0
            yColumn: 1
        }
//        VXYModelMapper {
//            id: modelMapper2
//            model: lineModel // QStandardModel in C++
//            series:line2
//            firstRow: 1
//            xColumn: 1
//            yColumn: 3
//        }
    }
}
