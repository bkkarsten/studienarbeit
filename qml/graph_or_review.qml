import QtQuick 2.15

// A switcher that can show either the graph view or the review UI

Switcher {
    id: graphOrReview
    objectName: "graphOrReview"

    Graphview {}

    ReviewSession {}
}