#pragma once

#include "GraphicDev.h"
#include "TimerMgr.h"
#include "FrameMgr.h"
#include "FontMgr.h"
#include "InputDev.h"

BEGIN(Engine)


// GraphicDev
inline HRESULT	Ready_GraphicDev(HWND hWnd, WINMODE eMode, const _uint& iSizeX, const _uint& iSizeY, CGraphicDev** ppGraphicDev);
inline void		Render_Begin(D3DXCOLOR Color);
inline void		Render_End();

// TimerMgr
inline _float			Get_TimeDelta(const _tchar* pTimerTag);
inline void				Set_TimeDelta(const _tchar* pTimerTag);
inline HRESULT			Ready_Timer(const _tchar* pTimerTag);

// FrameMgr
inline HRESULT			Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit);
inline _bool			IsPermit_Call(const _tchar* pFrameTag, const _float& fTimeDelta);

// FontMgr  
inline HRESULT			Ready_Font(LPDIRECT3DDEVICE9 pGraphicDev
	, const _tchar* pFontTag
	, const _tchar* pFontType
	, const _uint& iWidth
	, const _uint& iHeight
	, const _uint& iWeight);

inline void				Render_Font(const _tchar* pFontTag
	, const _tchar* pString
	, const _vec2* pPos
	, D3DXCOLOR Color
	, TEXTRANGE _eTextRange = TEXT_DEFAULT
	, _vec2 vXYSize = { 600.f, 600.f });

// inputDev

inline _byte	Get_DIKeyState(_ubyte byKeyID);
inline _bool    GetKeyDown(_ubyte byKeyID);
inline _bool	GetKeyUp(_ubyte byKeyID);
inline _bool	GetKeyPress(_ubyte byKeyID);
inline _bool    GetAnyActionKeyDown();

inline _byte	Get_DIMouseState(MOUSEKEYSTATE eMouse);
inline _long	Get_DIMouseMove(MOUSEMOVESTATE eMouseState);

inline HRESULT Ready_InputDev(HINSTANCE hInst, HWND hWnd);
inline void	Update_InputDev(void);

inline void		Release_System();

#include "Export_System.inl"

END
