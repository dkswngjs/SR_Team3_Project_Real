#include "pch.h"
#include "Item.h"
#include "Player.h" //0924

CItem::CItem(LPDIRECT3DDEVICE9 pGraphicDev)
    :Engine::CGameObject(pGraphicDev)
{
}

CItem::~CItem()
{
}

HRESULT CItem::Ready_GameObject()
{
    //m_pTextureCom[EQUIP].resize(EQUIP_END);
    //m_pTextureCom[CONSUM].resize(CONSUM_END);
    //m_pTextureCom[OTHER].resize(OTHER_END);
    //m_pTextureCom[QUEST].resize(QUEST_END);

    //m_pTransformCom[EQUIP].resize(EQUIP_END);
    //m_pTransformCom[CONSUM].resize(CONSUM_END);
    //m_pTransformCom[OTHER].resize(OTHER_END);
    //m_pTransformCom[QUEST].resize(QUEST_END);

//    ITEM_INFO   tInfo = { EQUIP,
//          L"../Bin/Resource/Texture/Item/Explore.png",
//          L"Ž�� ����",
//          L"Ž���� �� �ʼ��� ì��� ����. \
//`           Ž�谡�� �� ���..!!! \
//            ���� -? ȣ!",
//              0 };
//    m_ItemArray[tInfo.tType].push_back(tInfo);

    /*tInfo = { EQUIP,
          L"../Bin/Resource/Texture/Item/Mini.png",
          L"��Ƽ ����",
          L"�����ϱ� ���� ����.",
          0 };
    m_ItemArray[tInfo.tType].push_back(tInfo);

    tInfo = { CONSUM,
          L"../Bin/Resource/Texture/Item/SmallFruit.png",
          L"�ǰ� ����",
          L"3��� ����. \
            ������ ���ִ�.",
          100 };
    m_ItemArray[tInfo.tType].push_back(tInfo);

    tInfo = { CONSUM,
          L"../Bin/Resource/Texture/Item/MiddleFruit.png",
          L"��� ����",
          L"2��� ����. \
            ��ŭ�� ������ �Ծȿ� ������.",
          200 };
    m_ItemArray[tInfo.tType].push_back(tInfo);

    tInfo = { CONSUM,
          L"../Bin/Resource/Texture/Item/BigFruit.png",
          L"ưư ����",
          L"1��� ����. \
            ũ��. ��δ�.",
          500 };
    m_ItemArray[tInfo.tType].push_back(tInfo);

    tInfo = { OTHER,
          L"../Bin/Resource/Texture/Item/Leaf.png",
          L"������",
          L"��𼭵� ���� �� �� �ִ� ������.",
          10 };
    m_ItemArray[tInfo.tType].push_back(tInfo);

    tInfo = { OTHER,
          L"../Bin/Resource/Texture/Item/Branch.png",
          L"��������",
          L"��𼭵� ���� �� �� �ִ� ��������.",
          10 };
    m_ItemArray[tInfo.tType].push_back(tInfo);

    tInfo = { QUEST,
          L"../Bin/Resource/Texture/Item/Net.png",
          L"���ڸ� ä",
          L"�Ʊ� ������ �Ƴ��� ���ڸ� ä.",
          0 };
    m_ItemArray[tInfo.tType].push_back(tInfo);

    tInfo = { QUEST,
          L"../Bin/Resource/Texture/Item/DarwTool.png",
          L"�׸� ����",
          L"�׸��� �׸� �� �ִ� ����.",
          0 };
    m_ItemArray[tInfo.tType].push_back(tInfo);*/

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    return S_OK;
}

_int CItem::Update_GameObject(const _float& fTimeDelta)
{
    //m_pPlayer = dynamic_cast<CPlayer*>(Engine::Get_GameObject(L"Layer_GameLogic", L"Player"));
    //NULL_CHECK_RETURN(m_pPlayer, 0);

    _int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

    Engine::Add_RenderGroup(RENDER_UI, this);

    return iExit;
}

void CItem::LateUpdate_GameObject(const _float& fTimeDelta)
{
    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CItem::Render_GameObject()
{
}

HRESULT CItem::Add_Component()
{
    return S_OK;
}

CItem* CItem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CItem* pItem = new CItem(pGraphicDev);

    if (FAILED(pItem->Ready_GameObject()))
    {
        Safe_Release(pItem);
        MSG_BOX("Item Create Failed");
        return nullptr;
    }

    return pItem;
}

void CItem::Free()
{
    Engine::CGameObject::Free();
}
