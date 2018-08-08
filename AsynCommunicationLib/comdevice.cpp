#include "stdafx.h"
#include "comdevice.h"
#ifdef _WIN32
   
#endif

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
#ifdef _UNICODE


   m_sPort =  ::CreateFileW((LPCWCHAR)UTF8_To_string(ComPort).c_str(),GENERIC_READ|GENERIC_WRITE,0,
                      NULL,OPEN_EXISTING,
                      NULL,
                      NULL);
#else
	m_sPort = ::CreateFileA(ComPort.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING,
		NULL,
		NULL);
#endif // _UNICODE

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

std::string ComDevice::UTF8_To_string(const std::string & str)
{
	
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];

	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;
	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;
	return retStr;
	
}

