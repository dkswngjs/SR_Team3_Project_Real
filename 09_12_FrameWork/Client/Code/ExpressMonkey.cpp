#include "pch.h"
#include "ExpressMonkey.h"

CExpressMonkey::CExpressMonkey(LPDIRECT3DDEVICE9 pGraphicDev)
    :CNPC(pGraphicDev)
{
}

CExpressMonkey::~CExpressMonkey()
{
}

HRESULT CExpressMonkey::Ready_GameObject()
{
    CNPC::Ready_GameObject();

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    //D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/NPC/MonkeyIDLE2.png", &m_pNPCTex);
    //m_pAnimatorCom->CreateAnimation(L"MonkeyIDLE", m_pNPCTex, _vec2(0.f, 0.f), _vec2(180.f, 200.f), _vec2(180.f, 0.f), 0.12f, 7);

    D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/NPC/MonkeyIDLE.png", &m_pNPCTex);
    m_pAnimatorCom->CreateAnimation(L"MonkeyIDLE", m_pNPCTex, _vec2(0.f, 0.f), _vec2(136.5f, 145.f), _vec2(136.5f, 0.f), 0.12f, 14); 

    //D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/NPC/M.png", &m_pNPCTex);
    //m_pAnimatorCom->CreateAnimation(L"MonkeyIDLE", m_pNPCTex, _vec2(0.f, 0.f), _vec2(256.f, 256.f), _vec2(256.f, 0.f), 0.12f, 7, _vec2(2048.f, 256.f));

    m_tInfo.pName = L"���� �ͽ�������";
    m_tInfo.pContent = L"�ͽ������� �̿���� ������ �¿��� �� �����. �̿���� ������ �ٽ� �� �ɾ��ּ���.";

    m_tQuestInfo.pQuestTitle = L"���� �ͽ������� �̿�� ã��";
    m_tQuestInfo.pQuestContent = L"���� �ͽ������� �̿���� ������ ���� �ͽ��������� �̿��� �� ���ٰ�?! �̿���� ã�Ƽ� �ٽ� ����!";

    _vec3 vMarkPos = m_pTransformCom->m_vInfo[INFO_POS];
    vMarkPos.y += 35.f;
    m_pMarkTransformCom->m_vInfo[INFO_POS] = vMarkPos;


    return S_OK;
}

void CExpressMonkey::LateReady_GameObject()
{
    CNPC::LateReady_GameObject();
}

_int CExpressMonkey::Update_GameObject(const _float& fTimeDelta)
{
    CNPC::Update_GameObject(fTimeDelta);

    _int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

    if (!m_bQuestClear && m_bQuestAccept)
    {
        //if (m_pInven->Find_Item(CItem::QUEST, CItem::EXTICKET));
        if (m_pInven->Find_Item(CItem::CONSUM, CItem::SMALL_FRUIT))
        {
            m_bQuestSucess = true;
        }
    }
    Add_RenderGroup(RENDER_ALPHA, this);

    return iExit;
}

void CExpressMonkey::LateUpdate_GameObject(const _float& fTimeDelta)
{
    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CExpressMonkey::Render_GameObject()
{
    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

    //m_pTextureCom->Set_Texture();
    m_pGraphicDev->SetTexture(0, m_pNPCTex);
    m_pAnimatorCom->Play(L"MonkeyIDLE", true);
    m_pAnimatorCom->render();


    //m_pBufferCom->Render_Buffer();
    m_pColliderCom->Render_Buffer();

    if (!m_bQuestClear)
    {
        m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pMarkTransformCom->Get_WorldMatrix());

        if (!m_bQuestAccept)
        {
            m_pGraphicDev->SetTexture(0, m_pTex[EXCLAMATION]);
            m_pMarkAnimatorCom->Play(L"ExclamMarkAnim", true);
            m_pMarkAnimatorCom->render();
            return;
        }
        if (m_bQuestSucess)
        {
            m_pGraphicDev->SetTexture(0, m_pTex[YELLOWQUEST]);
            m_pMarkAnimatorCom->Play(L"YellowQuestAnim", true);
            m_pMarkAnimatorCom->render();
            return;
        }

        m_pGraphicDev->SetTexture(0, m_pTex[GRAYQUEST]);
        m_pMarkAnimatorCom->Play(L"GrayQuestAnim", true);
        m_pMarkAnimatorCom->render();

    }

}

void CExpressMonkey::OnCollision(CGameObject* _pOther)
{
    // [S]��ư ���.
    // [S]��ư Ŭ�� �� �ؽ�Ʈ�ڽ� ��� + �ؽ�Ʈ ���
    if (Engine::GetKeyDown(DIK_S))
    {
        m_bConversation = m_bConversation ? false : true;
        // ��ȭ���϶� S�� ������ ��ȭ����
        // ��ȭ���� �ƴҶ� S�� ������ ��ȭ����
        if (!m_bConversation)
        {
            if (!m_bQuestAccept)
            {
                m_bConversation = m_bConversation ? false : true;
                // ���⿡ new����Ʈ UI ����
                m_bQuestAccept = true; // ���� �� �ڿ� true�� �ٲ���.
                m_pQuestUI->Add_Quest(m_tQuestInfo);

                m_pQuestAcceptUI->CallQuestAcceptUI(true);
                m_pQuestAcceptUI->Set_Text(m_tQuestInfo);
                //m_pInterButton->CallButton(true); // ��ȭ���� �ƴ� �� ��ư Ȱ��ȭ

                return;
            }
        }

        if (m_bConversation)
        {
            m_pInterButton->CallButton(false); // ��ȭ ���� ��� ��ư ����� �ʿ� ����!!!!

            m_pTextBox->Set_Text(m_tInfo); //��ȭâ �ؽ�Ʈ ����
            m_pTextBox->CallTextBox(true); //��ȭâ ȣ��

            // ���ʿ��� �⺻ ����Ʈ ��ǳ�� ��������ؼ� �������� ������ �ִ��� false ���·� ����ϱ� ����
            //if (!m_bQuestClear && m_bQuestAccept)
            if (m_bQuestSucess)
            {
                m_bQuestClear = true;
                m_tInfo.pContent = L"��..�̿���� ������ ��ô±���............... ����!!! ���� �̵��ұ��??";
                m_pTextBox->Set_Text(m_tInfo); //��ȭâ �ؽ�Ʈ ����
                m_pQuestUI->Get_QuestArray()->pop_back();
            }
        }

    }

    if (!m_bConversation)
    {
        m_pInterButton->CallButton(true); // ��ȭ���� �ƴ� �� ��ư Ȱ��ȭ
        // ��ȭ�ϱ�[S]
    }

}

void CExpressMonkey::OnCollisionEnter(CGameObject* _pOther)
{
    // ǳ��Ŀ���� + �ݰ����ϴ� ���� �ִϸ��̼�
}

void CExpressMonkey::OnCollisionExit(CGameObject* _pOther)
{
    m_pInterButton->CallButton(false);
}



HRESULT CExpressMonkey::Add_Component()
{
    CComponent* pComponent = NULL;

    //pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

    //pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_ExpressMonkey"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_Texture",pComponent });

    pComponent = m_pAnimatorCom = dynamic_cast<CAnimator2*>(Engine::Clone_Proto(L"Proto_Animator"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Ani_Buffer", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });
    m_pTransformCom->m_vScale = { 20.f, 20.f, 20.f };
    m_pTransformCom->Set_Pos(200.f, 50.f, 800.f);

    pComponent = m_pColliderCom = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_pColliderCom->SetGameObjectPtr(this);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });


    return S_OK;
}

CExpressMonkey* CExpressMonkey::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CExpressMonkey* pNPC = new CExpressMonkey(pGraphicDev);

    if (FAILED(pNPC->Ready_GameObject()))
    {
        Safe_Release(pNPC);
        MSG_BOX("ExpressMonkey Create Failed");
        return nullptr;
    }

    return pNPC;
}

void CExpressMonkey::Free()
{
    Engine::CGameObject::Free();
}
