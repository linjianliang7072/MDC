// ���� ifdef �^�K�ǽ����޼��ԅf���� DLL �R���Ę˜ʷ�ʽ��
// �@�� DLL �е����Йn������ʹ���������������x STATICTEST_EXPORTS ��̖���g�ġ�
// �������ж��x�ķ�̖���κΌ������������x�@����̖
// �@��һ��ԭʼ��ʽ�n�а����@�n�����κ���������
// ���� STATICTEST_API ��ʽҕ��� DLL �R��ģ����@�� DLL �t�����@Щ��̖ҕ��
// �R���ġ�
#ifdef STATICTEST_EXPORTS
#define STATICTEST_API __declspec(dllexport)
#else
#define STATICTEST_API __declspec(dllimport)
#endif

// �@��e�Ǐ� StaticTest.dll �R����
class STATICTEST_API CStaticTest {
public:
	CStaticTest(void);
	// TODO:  �ڴ˼������ķ�����
};

extern STATICTEST_API int nStaticTest;

STATICTEST_API int fnStaticTest(void);
