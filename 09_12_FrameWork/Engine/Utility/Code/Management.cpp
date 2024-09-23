#include "Management.h"
#include "Export_Utility.h"

IMPLEMENT_SINGLETON(CManagement)



//:m_pScene(nullptr)

CManagement::CManagement()
	:m_pScene(nullptr)
{

}

CManagement::~CManagement()
{
	Free();
}

CComponent* CManagement::Get_Component(COMPONENTID eID, const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag)
{
	NULL_CHECK_RETURN(m_pScene, nullptr);

	return m_pScene->Get_Component(eID, pLayerTag, pObjTag, pComponentTag);

}

CGameObject* CManagement::Get_GameObject(const _tchar* pLayeTag, const _tchar* pObjTag)
{

	NULL_CHECK_RETURN(m_pScene, nullptr);

	return m_pScene->Get_GameObject(pLayeTag, pObjTag);
}

HRESULT CManagement::Set_Scene(CScene* pScene)
{
	Safe_Release(m_pScene);

	Engine::Clear_RenderGroup();

	m_pScene = pScene;

	return S_OK;
}

void CManagement::LateReady_Scene()
{
	m_pScene->LateReady_Scene();
}

_int CManagement::Update_Scene(const _float& fTimeDelta)
{
	NULL_CHECK_RETURN(m_pScene, -1);

	return m_pScene->Update_Scene(fTimeDelta);
}

void CManagement::LateUpdate_Scene(const _float& fTimeDelta)
{
	NULL_CHECK(m_pScene);
	m_pScene->LateUpdate_Scene(fTimeDelta);
}

void CManagement::Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::Render_GameObject(pGraphicDev);

	NULL_CHECK(m_pScene);
	m_pScene->Render_Scene();
}

void CManagement::Free()
{
	Safe_Release(m_pScene);
}
