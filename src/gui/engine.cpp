#include <iostream>
#include "sensordata.h"
#include "engine.h"
#include "client.h"

void Engine::run()
{
    client = new Client();
    std::cout << "Connecting" << std::endl;
    if (client->connectTo(host, 6668)) {
        std::cout << "Connected!" << std::endl;

        //client.sendMessage("Hello World");
        //std::cout << "Text sent!" << std::endl;
        //SensorData sensor("in.txt");
        SensorData sensor("/sys/class/i2c-adapter/i2c-3/3-001d/coord");
        for (int i = 0; i < 2000; ++i) {
            sensor.update();
            sensor.processLine();
            Engine::msleep(25);
            qint64 x = sensor.getDx() / 1000;
            qint64 y = sensor.getDy() / 1000;
            // z is roughly -1000 when it's laying on your hand, screen up.
            qint64 z = sensor.getDz() + 1000;

            //  if (x != 0 || z != 0) {
            qint16 dz = z > 0 ? 5 : -5;
            client->sendMouseMovement(0, dz );
            std::cout << x << ", " << y << ", " << z << std::endl;
            //}
            //std::cout << "Mouse movement sent!" << std::endl;
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
