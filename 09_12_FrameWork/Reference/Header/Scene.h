#pragma once
#include "Base.h"
#include "Layer.h"

BEGIN(Engine)

class ENGINE_DLL CScene : public CBase
{
protected:
	explicit CScene(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene();

public:
	CComponent* Get_Component(COMPONENTID eID, const _tchar* pLayeTag, const _tchar* pObjTag, const _tchar* pComponentTag);
	CGameObject* Get_GameObject(const _tchar* pLayeTag, const _tchar* pObjTag);


public:
	virtual  HRESULT Ready_Scene();
	virtual  _int    Update_Scene(const _float& fTimeDelta);
	virtual  void    LateUpdate_Scene(const _float& fTimeDelta);
	virtual  void    Render_Scene()PURE;


protected:
	map<const _tchar*, CLayer*>  m_mapLayer;
	LPDIRECT3DDEVICE9			 m_pGraphicDev; 


protected:
	virtual  void  Free();


	//8�� 26�� �۾�
public:
	map<const _tchar*, CLayer*>& GetLayerMapPtr() { return m_mapLayer; }
};

END