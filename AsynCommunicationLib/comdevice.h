#ifndef COMDEVICE_H
#define COMDEVICE_H
#include <windows.h>
#include <string>
#include <tchar.h>
class ComDevice
{
public:
    enum BaudRate {
        Baud1200 = 1200,
        Baud2400 = 2400,
        Baud4800 = 4800,
        Baud9600 = 9600,
        Baud19200 = 19200,
        Baud38400 = 38400,
        Baud57600 = 57600,
        Baud115200 = 115200,
        UnknownBaud = -1
    };
    enum Parity {
        NoParity = 0,
        EvenParity = 1,
        OddParity = 2,
        SpaceParity = 3,
        MarkParity = 4,
        UnknownParity = -1
    };
    enum DataBits {
        Data5 = 5,
        Data6 = 6,
        Data7 = 7,
        Data8 = 8,
        UnknownDataBits = -1
    };
    enum StopBits {
        OneStop = 0,
        OneAndHalfStop = 1,
        TwoStop = 2,
        UnknownStopBits = -1
    };
    enum FlowControl {
        NoFlowControl,
        HardwareControl,
        SoftwareControl,
        UnknownFlowControl = -1
    };
public:
    ComDevice();
    ~ComDevice();
    bool  CreateCom(const std::string ComPort, int setBaudRate,
                        int Databit, int Stopbit, int setParity,
                         int SetFlowControl);
    int WirteData(const char *Data,int wirtelength,int Timeout);
    bool CloseComPort();
    bool IsOpen();
private:
    HANDLE m_sPort;
    DCB       m_PortAttribute;
    COMMTIMEOUTS m_CommTimeouts;

};

#endif // COMDEVICE_H
