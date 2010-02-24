#include <iostream>
#include <cmath>
#include "sensordata.h"
#include "engine.h"
#include "client.h"

void Engine::run()
{
    client = new Client();
    std::cout << "Connecting" << std::endl;
	if (client->connectTo(host, port)) {
        std::cout << "Connected!" << std::endl;
        SensorData sensor("/sys/class/i2c-adapter/i2c-3/3-001d/coord");
        while (!connectionTerminated) {
            Engine::msleep(25);
            if (!locked) {
                sensor.update();
                sensor.processLine();
                qint16 x = sensor.getX();
                qint16 y = sensor.getY();
                qint16 z = sensor.getZ();

                x /= 50;
                y /= 50;
                z /= 50;

// qreal pitch = atan2(x, -y);
// qreal roll = atan2(y, -z);
// pitch = pitch * 180 / M_PI * -1;
// roll = (roll * 180 / M_PI) + 90;

                if (x + y != 0) {
                    x = pow(abs(x), 1.5) * x / abs(x);
                    y = pow(abs(y), 1.5) * y / abs(y);
                    client->sendMouseMovement(y, -x);
                }
            }
            else {
                sensor.reInitializeValues();
            }
        }
    }
    else {
        std::cout << "Connection failed :(" << std::endl;
    }
}
