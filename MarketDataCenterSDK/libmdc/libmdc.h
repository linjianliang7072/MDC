// �U�C ifdef �϶��O�إߥ����H��U�q DLL �ץX���зǤ覡�C
// �o�� DLL �����Ҧ��ɮ׳��O�ϥΩR�O�C���ҩw�q LIBMDC_EXPORTS �Ÿ��sĶ���C
// �b�R�O�C�w�q���Ÿ��C����M�׳������w�q�o�ӲŸ�
// �o�ˤ@�ӡA��l�{���ɤ��]�t�o�ɮת������L�M��
// �|�N LIBMDC_API �禡�����q DLL �פJ���A�ӳo�� DLL �h�|�N�o�ǲŸ�����
// �ץX���C
#ifdef LIBMDC_EXPORTS
#define LIBMDC_API __declspec(dllexport)
#else
#define LIBMDC_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	LIBMDC_API void WINAPI mdc_set_agent_addr(char* port);
	LIBMDC_API int WINAPI mdc_init();
	LIBMDC_API int WINAPI mdc_close();
	LIBMDC_API int WINAPI mdc_destory();
	//LIBMDC_API int WINAPI mdc_get_last_message(TCHAR* message);

#ifdef __cplusplus
}
#endif 
