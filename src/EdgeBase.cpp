#include "EdgeBase.hpp"

boost::json::object EdgeBase::toJson(int srcId, int destId) {
    boost::json::object json = propertiesToJson();
    json["type"] = getTypeName();
    json["src"] = srcId;
    json["dest"] = destId;
    return json;
}

void EdgeBase::loadJson(boost::json::object json) {
    propertiesLoadJson(json);
}
