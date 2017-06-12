// 下列 ifdef 區塊是建立巨集以協助從 DLL 匯出的標準方式。
// 這個 DLL 中的所有檔案都是使用命令列中所定義 LIBMDC_EXPORTS 符號編譯的。
// 在命令列定義的符號。任何專案都不應定義這個符號
// 這樣一來，原始程式檔中包含這檔案的任何其他專案
// 會將 LIBMDC_API 函式視為從 DLL 匯入的，而這個 DLL 則會將這些符號視為
// 匯出的。
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
