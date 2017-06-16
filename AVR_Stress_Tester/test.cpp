#include <iostream>
#include "SimpleSerial.h"
#include <chrono>
#include <thread>
using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{
    // Establish serial connection
    SimpleSerial serial("/dev/ttyUSB0",9600);

    // Arduino ignores first command for some reason...
    serial.writeString("blah\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    // Stress test:
    while(true) {

        try {

            // Enter washout position
            serial.writeString("2\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            
            // Enter inspection position
            serial.writeString("3\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            // Carry out 10 spin operations
            for(int i = 0; i < 10; i++) {
                serial.writeString("4\n");
                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            }

		
        } catch(boost::system::system_error& e) {
            cout<<"Error: "<<e.what()<<endl;
            return 1;
        }

    }

}
