#pragma once
#include "Base.h"
#include "GameObject.h"


BEGIN(Engine)

class ENGINE_DLL CLayer: public CBase
{
private:
	explicit  CLayer();
	virtual  ~CLayer();

public:
	CComponent* Get_Component(COMPONENTID eID, const _tchar* pObjTag, const _tchar* pComponentTag);

public:
	HRESULT     Add_GameObject(const _tchar* pObjTag, CGameObject* pGameObject);
	//9�� 5�� ���� �߰��� �ڵ� 
	CGameObject*     Get_GameObject(const _tchar* pLayeTag, const _tchar* pObjTag);

public:
	HRESULT		Ready_Layer();
	void		LateReady_Layer();
	_int		Update_Layer(const _float& fTimeDelta);
	void		LateUpdate_Layer(const _float& fTimeDelta);
	void		Render_Layer();


private:
	map<const _tchar*, CGameObject*>  m_mapObejct;

public:
	static CLayer* Create();

private:
	virtual void   Free();

public:
	map<const _tchar*, CGameObject*>& GetLayerGameObjectPtr() { return m_mapObejct; }


};



END
