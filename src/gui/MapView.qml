import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

Map {
    id: map
    plugin: Plugin { name: "osm" }
    center: QtPositioning.coordinate(55.75, 37.62)
    zoomLevel: 15

    // Здесь можно добавить Repeater с маркерами из swarm.getDronePositions()
    // но для простоты — статичный пример
    MapQuickItem {
        coordinate: QtPositioning.coordinate(55.755, 37.617)
        anchorPoint.x: image.width/2
        anchorPoint.y: image.height
        sourceItem: Image { id: image; source: "qrc:/icons/drone.png" }
    }
}