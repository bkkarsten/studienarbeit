#include "NodeBase.hpp"

boost::json::object NodeBase::toJson() {
    boost::json::object json = propertiesToJson();
    json["type"] = getTypeName();
    qan::NodeItem* item = getItem();
    json["x"] = item ? item->x() : 0;
    json["y"] = item ? item->y() : 0;
    json["width"] = item ? item->width() : -1;
    json["height"] = item ? item->height() : -1;
    return json;
}

void NodeBase::loadJson(boost::json::object json) {
    propertiesLoadJson(json);
    qan::NodeItem* item = getItem();
    if(item != nullptr) {
        item->setX(json["x"].as_double());
        item->setY(json["y"].as_double());
        double width = json["width"].as_double();
        if(width > 0) {
            item->setWidth(json["width"].as_double());
        }
        double height = json["height"].as_double();
        if(height > 0) {
            item->setHeight(json["height"].as_double());
        }
    }
}
