#include "BLE.hpp"

BLEProvider::BLEProvider() {
    NimBLEDevice::init("SpinachLeaf");
    this->pServer = BLEDevice::createServer();
    this->pService = this->pServer->createService(SERVICE_UUID);

    this->pConfig = this->pService->createCharacteristic(CONFIG_UUID, NIMBLE_PROPERTY::WRITE_NR | NIMBLE_PROPERTY::READ);
    this->pLeft = this->pService->createCharacteristic(LEFT_LIDAR_UUID);
    this->pCenter = this->pService->createCharacteristic(CENTER_LIDAR_UUID);
    this->pRight = this->pService->createCharacteristic(CENTER_LIDAR_UUID);

    this->pService->start();

    this->pLeft->setValue("-1");
    this->pCenter->setValue("-2");
    this->pRight->setValue("-3");

    this->pAdvertising = NimBLEDevice::getAdvertising();
    this->pAdvertising->addServiceUUID(SERVICE_UUID);
    this->pAdvertising->setScanResponse(true);
    this->pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    bool didSucceed = this->pAdvertising->start();
    printf(didSucceed ? "advertising!" : "not advertising!");
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
