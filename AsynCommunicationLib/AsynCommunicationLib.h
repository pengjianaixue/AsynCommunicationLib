// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ASYNCOMMUNICATIONLIB_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ASYNCOMMUNICATIONLIB_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ASYNCOMMUNICATIONLIB_EXPORTS
#define ASYNCOMMUNICATIONLIB_API __declspec(dllexport)
#else
#define ASYNCOMMUNICATIONLIB_API __declspec(dllimport)
#endif

// �����Ǵ� AsynCommunicationLib.dll ������
class ASYNCOMMUNICATIONLIB_API CAsynCommunicationLib {
public:
	CAsynCommunicationLib(void);
	// TODO:  �ڴ�������ķ�����
};

extern ASYNCOMMUNICATIONLIB_API int nAsynCommunicationLib;

ASYNCOMMUNICATIONLIB_API int fnAsynCommunicationLib(void);
