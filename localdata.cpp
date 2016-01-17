#include "localdata.h"

Model::LocalData        *Model::LocalData::_instance = NULL;

Model::LocalData        *Model::LocalData::instance() {
    if (_instance == NULL)
        _instance = new LocalData;
    return _instance;
}

void                    Model::LocalData::deleteInstance() {
    if (_instance != NULL)
        delete _instance;
}

Model::LocalData::LocalData() {

}

Model::LocalData::~LocalData() {

}
