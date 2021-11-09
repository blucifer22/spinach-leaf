#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

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
    BLEProvider();

    bool sensorsEnabled();

    void updateLeftLidar(int newVal);

    void updateCenterLidar(int newVal);

    void updateRightLidar(int newVal);
};
