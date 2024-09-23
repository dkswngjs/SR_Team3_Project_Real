#include "pch.h"
#include "Item.h"

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
    // �߰� �� �ֵ� �ֱ�
    //CComponent* pComponent = NULL;

    //// RC TEX
    //pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

    //Explore Hat
    //pComponent = m_pTextureCom[EQUIP][EXPLORE] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_ExploreHat"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TextureExploreHat", pComponent });
    //
    //pComponent = m_pTransformCom[EQUIP][EXPLORE] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TransformExploreHat", pComponent });
    ////m_pTransformCom[EQUIP][EXPLORE]->m_vInfo[INFO_POS] = { 0.f, 0.f, 0.9f };
    //m_pTransformCom[EQUIP][EXPLORE]->m_vScale = { 40.f, 40.f, 1.f };

    //MiniFruit
    //pComponent = m_pTextureCom[CONSUM][MINI_FRUIT] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_MiniFruit"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TextureMiniFruit", pComponent });

    //pComponent = m_pTransformCom[CONSUM][MINI_FRUIT] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TransformMiniFruit", pComponent });
    ////m_pTransformCom[EQUIP][EXPLORE]->m_vInfo[INFO_POS] = { 0.f, 0.f, 0.9f };
    //m_pTransformCom[CONSUM][MINI_FRUIT]->m_vScale = { 40.f, 40.f, 1.f };

    ////MiddleFruit
    //pComponent = m_pTextureCom[CONSUM][MIDDLE_FRUIT] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_MiddleFruit"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TextureMiddleFruit", pComponent });

    //pComponent = m_pTransformCom[CONSUM][MIDDLE_FRUIT] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TransformMiddleFruit", pComponent });
    ////m_pTransformCom[EQUIP][EXPLORE]->m_vInfo[INFO_POS] = { 0.f, 0.f, 0.9f };
    //m_pTransformCom[CONSUM][MIDDLE_FRUIT]->m_vScale = { 40.f, 40.f, 1.f };

    ////BigFruit
    //pComponent = m_pTextureCom[CONSUM][BIG_FRUIT] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_BigFruit"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TextureBigFruit", pComponent });

    //pComponent = m_pTransformCom[CONSUM][BIG_FRUIT] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TransformBigFruit", pComponent });
    ////m_pTransformCom[CONSUM][BIG_FRUIT]->m_vInfo[INFO_POS] = { 0.f, 0.f, 0.9f };
    //m_pTransformCom[CONSUM][BIG_FRUIT]->m_vScale = { 40.f, 40.f, 1.f };

    ////Leaf
    //pComponent = m_pTextureCom[OTHER][LEAF] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_Leaf"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TextureLeaf", pComponent });

    //pComponent = m_pTransformCom[OTHER][LEAF] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TransformLeaf", pComponent });
    ////m_pTransformCom[OTHER][LEAF]->m_vInfo[INFO_POS] = { 0.f, 0.f, 0.9f };
    //m_pTransformCom[OTHER][LEAF]->m_vScale = { 40.f, 40.f, 1.f };

    ////Branch
    //pComponent = m_pTextureCom[OTHER][BRANCH] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_Branch"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TextureBranch", pComponent });

    //pComponent = m_pTransformCom[OTHER][BRANCH] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TransformBranch", pComponent });
    ////m_pTransformCom[OTHER][BRANCH]->m_vInfo[INFO_POS] = { 0.f, 0.f, 0.9f };
    //m_pTransformCom[OTHER][BRANCH]->m_vScale = { 40.f, 40.f, 1.f };

    ////Net
    //pComponent = m_pTextureCom[QUEST][NET] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_Net"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TextureNet", pComponent });

    //pComponent = m_pTransformCom[QUEST][NET] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TransformNet", pComponent });
    ////m_pTransformCom[QUEST][NET]->m_vInfo[INFO_POS] = { 0.f, 0.f, 0.9f };
    //m_pTransformCom[QUEST][NET]->m_vScale = { 40.f, 40.f, 1.f };

    ////DrawTool
    //pComponent = m_pTextureCom[QUEST][DRAWTOOL] = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_DarwTool"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TextureDrawTool", pComponent });

    //pComponent = m_pTransformCom[QUEST][DRAWTOOL] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TransformDrawTool", pComponent });
    ////m_pTransformCom[QUEST][DRAWTOOL]->m_vInfo[INFO_POS] = { 0.f, 0.f, 0.9f };
    //m_pTransformCom[QUEST][DRAWTOOL]->m_vScale = { 40.f, 40.f, 1.f };

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
