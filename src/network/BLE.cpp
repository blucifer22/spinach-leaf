#define NUM_MEASUREMENT_BYTES 2

#include "BLE.hpp"

BLEProvider::BLEProvider() {
    NimBLEDevice::init("SpinachLeaf");
    this->pServer = BLEDevice::createServer();
    this->pService = this->pServer->createService(SERVICE_UUID);

    this->pConfig = this->pService->createCharacteristic(CONFIG_UUID, NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::READ);
    this->pLeft = this->pService->createCharacteristic(LEFT_LIDAR_UUID);
    this->pCenter = this->pService->createCharacteristic(CENTER_LIDAR_UUID);
    this->pRight = this->pService->createCharacteristic(RIGHT_LIDAR_UUID);

    this->pService->start();

    uint8_t* pConfigVal = new uint8_t[1] {2};
    this->pConfig->setValue(pConfigVal, 1);

    this->pLeftVal = (uint8_t*) calloc(NUM_MEASUREMENT_BYTES, 1);
    this->updateLeftLidar(0);

    this->pCenterVal = (uint8_t*) calloc(NUM_MEASUREMENT_BYTES, 1);
    this->updateCenterLidar(0);

    this->pRightVal = (uint8_t*) calloc(NUM_MEASUREMENT_BYTES, 1);
    this->updateRightLidar(0);

    this->pAdvertising = NimBLEDevice::getAdvertising();
    this->pAdvertising->addServiceUUID(SERVICE_UUID);
    this->pAdvertising->setScanResponse(true);
    this->pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    this->pAdvertising->start();
}

bool BLEProvider::sensorsEnabled() {
    // printf("%d\n", this->pConfig->getValue()[0]);
    return this->pConfig->getValue()[0] == 2;
}

void BLEProvider::updateLeftLidar(unsigned int newVal) {
    // printf("%d %d\n", this->pLeftVal[0], this->pLeftVal[1]);
    // printf("%d %d\n", this->pLeft->getValue()[0], this->pLeft->getValue()[1]);
    for (int i = 0; i < NUM_MEASUREMENT_BYTES; i++) {
        this->pLeftVal[i] = newVal % 0xFF;
        newVal = newVal >> 8;
        this->pLeft->setValue(this->pLeftVal, NUM_MEASUREMENT_BYTES);
    }
}

void BLEProvider::updateCenterLidar(unsigned int newVal) {
  for (int i = 0; i < NUM_MEASUREMENT_BYTES; i++) {
      this->pCenterVal[i] = newVal % 0xFF;
      newVal = newVal >> 8;
      this->pCenter->setValue(this->pCenterVal, NUM_MEASUREMENT_BYTES);
  }
}

void BLEProvider::updateRightLidar(unsigned int newVal) {
  for (int i = 0; i < NUM_MEASUREMENT_BYTES; i++) {
      this->pRightVal[i] = newVal % 0xFF;
      newVal = newVal >> 8;
      this->pRight->setValue(this->pRightVal, NUM_MEASUREMENT_BYTES);
  }
}
