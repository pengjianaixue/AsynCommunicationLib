#include "comdevice.h"

ComDevice::ComDevice():m_sPort(nullptr)
{

}
ComDevice::~ComDevice()
{
    if(m_sPort!=nullptr)
    CloseHandle(m_sPort);
    m_sPort = nullptr;
}

bool ComDevice::CreateCom(const std::string ComPort, int  setBaudRate, int  Databit, int  Stopbit, int setParity, int  SetFlowControl)
{
   m_sPort =  ::CreateFileW(_T("COM4"),GENERIC_READ|GENERIC_WRITE,0,
                      NULL,OPEN_EXISTING,
                      NULL,
                      NULL);
   if(m_sPort==INVALID_HANDLE_VALUE)
   {
       return false;
   }
   m_PortAttribute.DCBlength = sizeof(DCB);
   m_PortAttribute.fParity = true;
   m_PortAttribute.Parity = setParity;
   m_PortAttribute.BaudRate = setBaudRate;
   m_PortAttribute.StopBits = Stopbit; //ONESTOPBIT
   m_PortAttribute.ByteSize = Databit;

   if (!SetCommState(m_sPort, &m_PortAttribute))
   {
       CloseHandle(m_sPort);
       return (false);
   }

   GetCommTimeouts(m_sPort, &m_CommTimeouts);        //Get the serial port default timeout.
   m_CommTimeouts.ReadIntervalTimeout = MAXDWORD;
   m_CommTimeouts.ReadTotalTimeoutMultiplier = 10;
   m_CommTimeouts.ReadTotalTimeoutConstant = 10;
   m_CommTimeouts.WriteTotalTimeoutMultiplier = 50;
   m_CommTimeouts.WriteTotalTimeoutConstant = 100;
   if (!SetCommTimeouts(m_sPort, &m_CommTimeouts))
   {
       CloseHandle(m_sPort);
       return (false);
   }
   return true;


}
//timeout  暂时不起作用，超时时间为无限
int ComDevice::WirteData(const char *Data, int wirtelength, int Timeout)
{

    DWORD dwNumBytes, dwRet;
    dwRet = WriteFile(m_sPort, //Handle
                                Data, //Data buffer
                                wirtelength, //Buffer size
                                &dwNumBytes, //written bytes
                                NULL); //don't support
        return (dwRet != 0);



}

bool ComDevice::CloseComPort()
{
    CloseHandle(m_sPort);
    return true;

}

bool ComDevice::IsOpen()
{
    return m_sPort !=nullptr ? true:false;

}

