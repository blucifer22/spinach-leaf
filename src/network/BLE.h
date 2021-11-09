#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <string>

#define SERVICE_UUID      "eaa636ce-ffc0-4444-923e-cb0622a6772f"
#define CONFIG_UUID       "7815d597-62b4-4d3a-a58f-c4b2d9ae13e3"
#define LEFT_LIDAR_UUID   "bcbc0b7d-c813-48c4-ac04-5289cff3ebf6"
#define CENTER_LIDAR_UUID "51283344-4a85-472f-aef5-8023253bc0a5"
#define RIGHT_LIDAR_UUID  "8799087d-e65a-4ea3-9331-7222cc242da2"

class BLEProvider {
private:
    BLEServer* pServer;
    BLEService* pService;
    BLECharacteristic* pConfig;
    BLECharacteristic* pLeft;
    BLECharacteristic* pCenter;
    BLECharacteristic* pRight;

public:
    BLEProvider() {
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

    bool sensorsEnabled() {
      return true;
    }

    void updateLeftLidar(int newVal) {
        char* my_str = new char[20];
        snprintf(my_str, 20, "%d", newVal);
        this->pLeft->setValue(my_str);
        delete my_str;
    }

    void updateCenterLidar(int newVal) {
      char* my_str = new char[20];
      snprintf(my_str, 20, "%d", newVal);
      this->pCenter->setValue(my_str);
      delete my_str;
    }

    void updateRightLidar(int newVal) {
      char* my_str = new char[20];
      snprintf(my_str, 20, "%d", newVal);
      this->pRight->setValue(my_str);
      delete my_str;
    }
};
