// Code from http://www.webalice.it/fede.tft/serial_port/serial_port.html
#ifndef SIMPLESERIAL
#define SIMPLESERIAL

#include <boost/asio.hpp>

class SimpleSerial
{
public:

    /**
     * Constructor.
     * \param port device name, example "/dev/ttyUSB0" or "COM4"
     * \param baud_rate communication speed, example 9600 or 115200
     * \throws boost::system::system_error if cannot open the
     * serial device
     */
    SimpleSerial(std::string port, unsigned int baud_rate)
    : io(), serial(io,port)
    {
        serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    }

    std::string readLine();

    void writeString(std::string s);

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
};


#endif // SIMPLESERIAL

