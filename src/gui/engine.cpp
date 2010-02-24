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
        for (int i = 0; i < 2000 && !connectionTerminated; ++i) {
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

                if (dx + dy != 0) {
                    dx = pow(abs(dx), 1.5) * dx / abs(dx);
                    dy = pow(abs(dy), 1.5) * dy / abs(dy);
                    client->sendMouseMovement(dy, -dx);
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
