#include "BLE.hpp"


BLEProvider::BLEProvider() {
    BLEDevice::init("SpinachLeaf");
    this->pServer = BLEDevice::createServer();
    this->pService = this->pServer->createService(SERVICE_UUID);
    this->pConfig = this->pService->createCharacteristic(CONFIG_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

    this->pLeft = this->pService->createCharacteristic(LEFT_LIDAR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    this->pCenter = this->pService->createCharacteristic(CENTER_LIDAR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    this->pRight = this->pService->createCharacteristic(CENTER_LIDAR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

    this->pLeft->setValue("-1");
    this->pCenter->setValue("-2");
    this->pRight->setValue("-3");

    this->pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
}

bool BLEProvider::sensorsEnabled() {
    return true;
}

void BLEProvider::updateLeftLidar(int newVal) {
    char* my_str = new char[20];
    snprintf(my_str, 20, "%d", newVal);
    this->pLeft->setValue(my_str);
    delete my_str;
}

void BLEProvider::updateCenterLidar(int newVal) {
    char* my_str = new char[20];
    snprintf(my_str, 20, "%d", newVal);
    this->pCenter->setValue(my_str);
    delete my_str;
}

void BLEProvider::updateRightLidar(int newVal) {
    char* my_str = new char[20];
    snprintf(my_str, 20, "%d", newVal);
    this->pRight->setValue(my_str);
    delete my_str;
}
