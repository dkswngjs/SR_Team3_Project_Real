#include "pch.h"
#include "ElectriceelBossStage.h"
#include "Export_Utility.h"


CElectriceelBossStage::CElectriceelBossStage(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CScene(pGraphicDev)
{
}

CElectriceelBossStage::~CElectriceelBossStage()
{
}

HRESULT CElectriceelBossStage::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Layer_Environmnet(L"Layer_Environment"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GameLogic(L"Layer_GameLogic"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"Layer_UI"), E_FAIL);

  Engine::StopSound(SOUND_BGM);   
  Engine::PlayBGM(L"BGM_65_OceanFinalBossFight.wav", 1.f);       


	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

    CLayer* layer = Engine::Get_Layer(L"Layer_GameLogic");
    CPlayer* player = dynamic_cast<CPlayer*>(
        Get_GameObject(L"Layer_GameLogic", L"Player"));

    dynamic_cast<CTransform*>(
        player->Get_Component(ID_DYNAMIC, L"Com_Transform")
        )->Set_Pos(500.f, 30.f, 550.f);

	return S_OK;
}

_int CElectriceelBossStage::Update_Scene(const _float& fTimeDelta)
{
	_int  iExit = Engine::CScene::Update_Scene(fTimeDelta);

    if (GetAsyncKeyState('M') & 0x8000)
    {
        Engine::CScene* pStage3 = CArenaStage::Create(m_pGraphicDev);
        NULL_CHECK_RETURN(pStage3, -1);

        FAILED_CHECK_RETURN(Engine::Set_Scene(pStage3), E_FAIL);
        //pStage3->init(); // 맵툴에서 가져온 오브젝트들을 위해 사용   

        return 0;
    }


	return iExit;
}

void CElectriceelBossStage::LateUpdate_Scene(const _float& fTimeDelta)
{
	Engine::CScene::LateUpdate_Scene(fTimeDelta);
}

void CElectriceelBossStage::Render_Scene()
{
}

void CElectriceelBossStage::init()
{
    //Engine::CLayer* pLayer = CLayer::Create();
    //
    //DWORD bytesRead = 1;
    //HANDLE hFile = CreateFile(L"../Map/MoonForestMap.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    //if (hFile != INVALID_HANDLE_VALUE)
    //{
    //    if (hFile != INVALID_HANDLE_VALUE) {
    //
    //        Engine::CLayer* pLayer = CLayer::Create();
    //
    //        DWORD bytesRead = 1;
    //
    //        while (bytesRead > 0)
    //        {
    //            ObjectData* objData = new ObjectData;
    //
    //            if (!ReadFile(hFile, objData, sizeof(ObjectData), &bytesRead, NULL))
    //            {
    //                MSG_BOX("읽기 오류");
    //            };
    //
    //            if (bytesRead == 0)
    //            {
    //                break;
    //            }
    //
    //
    //            int a = 4;
    //
    //            Engine::CGameObject* pGameObject = nullptr;
    //            pGameObject = CObject::Create(CGraphicDev::GetInstance()->Get_GraphicDev());
    //            if (pGameObject == nullptr)
    //            {
    //                MSG_BOX("CObject nullptr Error");
    //            }
    //
    //            pGameObject->SetObjectKey(objData->objectName);
    //            pGameObject->SetTextureKey(objData->textureKey);
    //
    //
    //            map<const _tchar*, CLayer*>& pMapLayer = Engine::Get_CurScenePtr()->GetLayerMapPtr();
    //            pMapLayer[L"Layer_GameLogic"]->Add_GameObject(objData->objectName, pGameObject);
    //
    //            CTransform* pTransform = dynamic_cast<CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Layer_GameLogic", objData->objectName, L"Com_Transform"));
    //
    //
    //            pTransform->m_vScale = { objData->scale.x,objData->scale.y,objData->scale.z };
    //            pTransform->Rotation(ROT_X, objData->rotation.x * 3.14f / 180.f);
    //            pTransform->Rotation(ROT_Y, objData->rotation.y * 3.14f / 180.f);
    //            pTransform->Rotation(ROT_Z, objData->rotation.z * 3.14f / 180.f);
    //            pTransform->Set_Pos(objData->worldMatrix._41, objData->worldMatrix._42, objData->worldMatrix._43);
    //
    //
    //            pTransform->Rotation_x = objData->rotation.x;
    //            pTransform->Rotation_y = objData->rotation.y;
    //            pTransform->Rotation_z = objData->rotation.z;
    //
    //
    //
    //            pTransform->Scale_x = objData->scale.x;
    //            pTransform->Scale_y = objData->scale.y;
    //            pTransform->Scale_z = objData->scale.z;
    //
    //
    //
    //        }
    //        CloseHandle(hFile);
    //    }
    //}
}

HRESULT CElectriceelBossStage::Ready_LightInfo()
{
	return E_NOTIMPL;
}

HRESULT CElectriceelBossStage::Ready_Layer_Environmnet(const _tchar* pLayerTag)
{
    Engine::CLayer* pLayer = CLayer::Create();
    NULL_CHECK_RETURN(pLayer, E_FAIL);

    Engine::CGameObject* pGameObject = nullptr;

    _vec3 Eye = { 0.f, 0.f, 0.f };
    _vec3 At = { 0.f, 1.f, 1.f };
    _vec3 Up = { 0.f, 1.f, 0.f };

    pGameObject = CDynamicCamera::Create(m_pGraphicDev, &Eye, &At, &Up);

    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"DynamicCamera", pGameObject), E_FAIL);

    
    //GameObject = CSkyBox::Create(m_pGraphicDev);          
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SkyBox", pGameObject), E_FAIL);

    m_mapLayer.insert({ pLayerTag, pLayer });

    return S_OK;
}

HRESULT CElectriceelBossStage::Ready_Layer_GameLogic(const _tchar* pLayerTag)
{
    Engine::CLayer* pLayer = CLayer::Create();
    NULL_CHECK_RETURN(pLayer, E_FAIL);

    Engine::CGameObject* pGameObject = nullptr;

    
    pGameObject = CElectriceelBossMap::Create(m_pGraphicDev);   
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"ElectriceelBossMap", pGameObject), E_FAIL);


    pGameObject = CPlayer::Create(m_pGraphicDev);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Player", pGameObject), E_FAIL);
    CManagement::GetInstance()->GetCurScenePtr()->Add_ObjectGroup(GROUP_TYPE::PLAYER, pGameObject);
    pGameObject->SetObjectKey(L"Player");

    pGameObject = CElectriceelBoss::Create(m_pGraphicDev);  
    NULL_CHECK_RETURN(pGameObject, E_FAIL);     
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"ElectriceelBoss", pGameObject), E_FAIL);
    CManagement::GetInstance()->GetCurScenePtr()->Add_ObjectGroup(GROUP_TYPE::MONSTER, pGameObject);    


    pGameObject = CStone::Create(m_pGraphicDev);    
    NULL_CHECK_RETURN(pGameObject, E_FAIL); 
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Stone0", pGameObject), E_FAIL);  
    static_cast<Engine::CTransform*>(pGameObject->Get_Component(ID_DYNAMIC, L"Com_Transform"))->Set_Pos(500.f, 21.f, 500.f);
    pGameObject->SetObjectKey(L"Stone0");

    pGameObject = CPlayerInteractionBox::Create(m_pGraphicDev); 
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"PlayerInteractionBox", pGameObject), E_FAIL);
    CManagement::GetInstance()->GetCurScenePtr()->Add_ObjectGroup(GROUP_TYPE::PLAYER, pGameObject);
    pGameObject->SetObjectKey(L"PlayerInteractionBox");

    CGameObject* PlayerObj = pLayer->Get_GameObject(L"Layer_GameLogic", L"Player");
    CGameObject* InteractionObj = pLayer->Get_GameObject(L"Layer_GameLogic", L"PlayerInteractionBox");
    dynamic_cast<CPlayerInteractionBox*>(InteractionObj)->SetPlayer(
        dynamic_cast<CPlayer*>(PlayerObj));
    //폭포 웨이브
    //pGameObject = CWaterFall::Create(m_pGraphicDev);    
    //NULL_CHECK_RETURN(pGameObject, E_FAIL);
    //FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"WaterFall", pGameObject), E_FAIL);


    m_mapLayer.insert({ pLayerTag, pLayer });
}

HRESULT CElectriceelBossStage::Ready_Layer_UI(const _tchar* pLayerTag)
{
    Engine::CLayer* pLayer = CLayer::Create();
    NULL_CHECK_RETURN(pLayer, E_FAIL);

    Engine::CGameObject* pGameObject = nullptr;
    pGameObject = CDefaultUI::Create(m_pGraphicDev);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Default_UI", pGameObject), E_FAIL);

    pGameObject = CInvenUI::Create(m_pGraphicDev);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Inven_UI", pGameObject), E_FAIL);

    pGameObject = CQuickSlot::Create(m_pGraphicDev);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"QuickSlot_UI", pGameObject), E_FAIL);

    pGameObject = CQuestUI::Create(m_pGraphicDev);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Quest_UI", pGameObject), E_FAIL);

    pGameObject = CPowerUI::Create(m_pGraphicDev);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Power_UI", pGameObject), E_FAIL);

    pGameObject = CSpeedUI::Create(m_pGraphicDev);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Speed_UI", pGameObject), E_FAIL);

    pGameObject = CStoreUI::Create(m_pGraphicDev);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Store_UI", pGameObject), E_FAIL);

    m_mapLayer.insert({ pLayerTag, pLayer });

    return S_OK;

}

CElectriceelBossStage* CElectriceelBossStage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CElectriceelBossStage* pElectriceelBossStage = new CElectriceelBossStage(pGraphicDev);

    return pElectriceelBossStage;   
}

void CElectriceelBossStage::Free()
{
    Engine::CScene::Free();
}
