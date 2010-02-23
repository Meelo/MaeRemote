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

        //client.sendMessage("Hello World");
        //std::cout << "Text sent!" << std::endl;
        //SensorData sensor("in.txt");
        SensorData sensor("/sys/class/i2c-adapter/i2c-3/3-001d/coord");
        for (int i = 0; i < 2000 && !connectionTerminated; ++i) {
            Engine::msleep(25);
            if (!locked) {
                sensor.update();
                sensor.processLine();
                qint16 x = sensor.getX();
                qint16 y = sensor.getY();
                // z is roughly -1000 when it's laying on your hand, screen up.
                qint16 z = sensor.getZ();
                qint16 dx = x;
                qint16 dy = y;
                qint16 dz = z;

                dx /= 10;
                dy /= 10;
                dz /= 10;

                qreal pitch = atan2(x, -y);
                qreal roll = atan2(y, -z);
                std::cout << pitch << ", " << roll << std::endl;
                pitch = pitch * 180 / M_PI * -1;
                roll = (roll * 180 / M_PI) + 90;
                std::cout << pitch << ", " << roll << std::endl;

//pos->pitch = (pitch * 180/M_PI)*-1;
//pos->roll = (roll * 180/M_PI) + 90;

//                dx = (abs(dx) < 10) ? 0 : dx;
//                dy = (abs(dy) < 10) ? 0 : dy;
//                dz = (abs(dz) < 10) ? 0 : dz;

                if (dx + dy != 0) {
                    client->sendMouseMovement(dy*2, -(dx*2));
                }
//                std::cout << x << ", " << y << ", " << z << std::endl;
                //std::cout << "Mouse movement sent!" << std::endl;
            }
            else {
                sensor.reInitializeValues();
            }
        }

        //client.sendClick(3);
        //std::cout << "Right mouse click sent!" << std::endl;

        //client.sendScroll(5);
        //std::cout << "Mouse wheel scroll sent!" << std::endl;
    }
    else {
        std::cout << "Connection failed :(" << std::endl;
    }
}
