#ifndef _DGUI_DINCLUDES_H_
#define _DGUI_DINCLUDES_H_

#ifdef _MSVC_LANG
#define DGUI_MSVC
#endif
 
#ifdef DGUI_MSVC
#ifdef UNICODE
#undef UNICODE
#endif
#define DGUI_PROJECT
#define _CRT_SECURE_NO_WARNINGS
typedef int WINBOOL;
#endif

#ifdef __cplusplus
#define CPP_VERID __cplusplus
#else
#error Please compile this as a C++ program!
#endif

#ifndef DGUI_MSVC
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#endif

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <utility>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <map>

#include <process.h>
#include <windows.h>
#include <mmsystem.h>
#include <shlobj.h>
#include <urlmon.h>

#define dllfunc GetProcAddress

#ifdef OLDVERSION
#define DGUI_OLDVER
#endif

#ifdef OLDVER
#define DGUI_OLDVER
#endif

#ifdef DGUI_OLDVER
#define dgui dgui_ns
#endif
/*for v2.1 or earlier*/

#ifdef PROJECT
#ifndef DGUI_PROJECT
#define DGUI_PROJECT
#endif
#endif

#ifndef DGUI_PROJECT
namespace dAPI{
	typedef HINSTANCE DGDIDLL;
	typedef WINBOOL(*API_T1)(HDC,CONST POINT*,int);
	typedef WINBOOL(*API_T2)(HDC,int,int,int,int);
	typedef WINBOOL(*API_T3)(HDC,int,int,LPCSTR,int);
	typedef HBRUSH(*API_T4)(COLORREF);
	typedef WINBOOL(*API_T5)(HGDIOBJ);
	typedef HDC(*API_T6)(HDC);
	typedef HBITMAP(*API_T7)(HDC,int,int);
	typedef HPEN(*API_T8)(int,int,COLORREF);
	typedef HFONT(*API_T9)(int,int,int,int,int,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,LPCSTR);
	typedef HGDIOBJ(*API_T10)(HDC,HGDIOBJ);
	typedef int(*API_T11)(HDC,int);
	typedef WINBOOL(*API_T12)(HDC,int,int,int,int,HDC,int,int,DWORD);
	typedef WINBOOL(*API_T13)(HDC);
	typedef COLORREF(*API_T14)(HDC,int,int,COLORREF);
	typedef COLORREF(*API_T15)(HDC,int,int);
	typedef WINBOOL(*API_T16)(HDC,int,int,int,int,HDC,int,int,int,int,DWORD);
	typedef HDC(*API_T17)(LPCSTR,LPCSTR,LPCSTR,CONST DEVMODEA*);
	typedef int(*API_T18)(HDC,int);
	typedef int(*API_T19)(HANDLE,int,LPVOID);
	typedef HGDIOBJ(*API_T20)(int);
	typedef HPALETTE(*API_T21)(HDC,HPALETTE,WINBOOL);
	typedef UINT(*API_T22)(HDC);
	typedef int(*API_T23)(HDC,HBITMAP,UINT,UINT,LPVOID,LPBITMAPINFO,UINT);
	typedef WINBOOL(*API_T24)(HDC,LPCSTR,int,LPSIZE);
	typedef WINBOOL(*API_T25)(HDC,CONST POINT*,int);
	typedef WINBOOL(*API_T26)(HDC,CONST POINT*,HDC,int,int,int,int,HBITMAP,int,int);
	
	typedef WINBOOL(*DAPI_T1)(LPOPENFILENAME);
	typedef WINBOOL(*DAPI_T2)(LPOPENFILENAME);
	
	HMODULE dll=LoadLibrary("gdi32.dll"),
			dlld=LoadLibrary("comdlg32.dll");

	API_T1 dPolygon=(API_T1)dllfunc(dll,"Polygon");
	API_T2 dEllipse=(API_T2)dllfunc(dll,"Ellipse");
	API_T3 dTextOutA=(API_T3)dllfunc(dll,"TextOutA");
	API_T4 dCreateSolidBrush=(API_T4)dllfunc(dll,"CreateSolidBrush");
	API_T5 dDeleteObject=(API_T5)dllfunc(dll,"DeleteObject");
	API_T6 dCreateCompatibleDC=(API_T6)dllfunc(dll,"CreateCompatibleDC");
	API_T7 dCreateCompatibleBitmap=(API_T7)dllfunc(dll,"CreateCompatibleBitmap");
	API_T8 dCreatePen=(API_T8)dllfunc(dll,"CreatePen");
	API_T9 dCreateFontA=(API_T9)dllfunc(dll,"CreateFontA");
	API_T10 dSelectObject=(API_T10)dllfunc(dll,"SelectObject");
	API_T11 dSetBkMode=(API_T11)dllfunc(dll,"SetBkMode");
	API_T12 dBitBlt=(API_T12)dllfunc(dll,"BitBlt");
	API_T13 dDeleteDC=(API_T13)dllfunc(dll,"DeleteDC");
	API_T14 dSetPixel=(API_T14)dllfunc(dll,"SetPixel");
	API_T15 dGetPixel=(API_T15)dllfunc(dll,"GetPixel");
	API_T16 dStretchBlt=(API_T16)dllfunc(dll,"StretchBlt");
	API_T17 dCreateDCA=(API_T17)dllfunc(dll,"CreateDCA");
	API_T18 dGetDeviceCaps=(API_T18)dllfunc(dll,"GetDeviceCaps");
	API_T19 dGetObjectA=(API_T19)dllfunc(dll,"GetObjectA");
	API_T20 dGetStockObject=(API_T20)dllfunc(dll,"GetStockObject");
	API_T21 dSelectPalette=(API_T21)dllfunc(dll,"SelectPalette");
	API_T22 dRealizePalette=(API_T22)dllfunc(dll,"RealizePalette");
	API_T23 dGetDIBits=(API_T23)dllfunc(dll,"GetDIBits");
	API_T24 dGetTextExtentPoint32A=(API_T24)dllfunc(dll,"GetTextExtentPoint32A");
	API_T25 dPolyline=(API_T25)dllfunc(dll,"Polyline");
	API_T26 dPlgBlt=(API_T26)dllfunc(dll,"PlgBlt");
	
	DAPI_T1 dGetOpenFileNameA=(DAPI_T1)dllfunc(dlld,"GetOpenFileNameA");
	DAPI_T2 dGetSaveFileNameA=(DAPI_T2)dllfunc(dlld,"GetSaveFileNameA");
}
#define Polygon dAPI::dPolygon
#define Ellipse dAPI::dEllipse
#define TextOutA dAPI::dTextOutA
#define CreateSolidBrush dAPI::dCreateSolidBrush
#define DeleteObject dAPI::dDeleteObject
#define CreateCompatibleDC dAPI::dCreateCompatibleDC
#define CreateCompatibleBitmap dAPI::dCreateCompatibleBitmap
#define CreatePen dAPI::dCreatePen
#define CreateFontA dAPI::dCreateFontA
#define SelectObject dAPI::dSelectObject
#define SetBkMode dAPI::dSetBkMode
#define BitBlt dAPI::dBitBlt
#define DeleteDC dAPI::dDeleteDC
#define SetPixel dAPI::dSetPixel
#define GetPixel dAPI::dGetPixel
#define StretchBlt dAPI::dStretchBlt
#define CreateDCA dAPI::dCreateDCA
#define GetDeviceCaps dAPI::dGetDeviceCaps
#define GetObjectA dAPI::dGetObjectA
#define GetStockObject dAPI::dGetStockObject
#define SelectPalette dAPI::dSelectPalette
#define RealizePalette dAPI::dRealizePalette
#define GetDIBits dAPI::dGetDIBits
#define GetTextExtentPoint32A dAPI::dGetTextExtentPoint32A
#define GetOpenFileNameA dAPI::dGetOpenFileNameA
#define GetSaveFileNameA dAPI::dGetSaveFileNameA
#define Polyline dAPI::dPolyline
#define PlgBlt dAPI::dPlgBlt
#else
namespace dAPI{}
#endif

namespace dAPI{
	typedef WINBOOL(*MAPI_T1)(LPCSTR,HMODULE,DWORD);
	typedef HWND(*KAPI_T1)();
	typedef HRESULT(*WAPI_T1)(LPUNKNOWN,LPCSTR,LPCSTR,DWORD,LPBINDSTATUSCALLBACK); 
	
	HMODULE dllm=LoadLibrary("winmm.dll"),
			dllk=GetModuleHandle("kernel32"),
			dllw=LoadLibrary("urlmon.dll"); 

	MAPI_T1 dPlaySoundA=(MAPI_T1)dllfunc(dllm,"PlaySoundA");
	KAPI_T1 dGetConsoleWindow=(KAPI_T1)dllfunc(dllk,"GetConsoleWindow");
	WAPI_T1 dURLDownloadToFileA=(WAPI_T1)dllfunc(dllw,"URLDownloadToFileA");
}
#define PlaySoundA dAPI::dPlaySoundA
#define GetConsoleWindow dAPI::dGetConsoleWindow
#define URLDownloadToFileA dAPI::dURLDownloadToFileA

using std::pair;
using std::vector;
using std::string;
using std::stack;
using std::queue;
using std::map;

using std::make_pair;

#ifdef DGUI_PROJECT
namespace dgui_ns{
	int WINAPI dgWinMain(HINSTANCE,HINSTANCE,LPSTR,int);
}
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	return dgui_ns::dgWinMain(hInstance,hPrevInstance,lpCmdLine,nCmdShow); 
}
#endif

#endif
