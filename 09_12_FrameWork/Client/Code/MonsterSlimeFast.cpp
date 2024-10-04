#include "pch.h"
#include "MonsterSlimeFast.h"
#include "Define.h"
#include "Export_System.h"

CMonsterSlimeFast::CMonsterSlimeFast(LPDIRECT3DDEVICE9 pGraphicDev)
    :CMonster(pGraphicDev)
    , m_HPBar(nullptr)
    
{
}

CMonsterSlimeFast::~CMonsterSlimeFast()
{
}

HRESULT CMonsterSlimeFast::Ready_GameObject()
{
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
    m_pTransformCom->m_vScale = { 30.f, 30.f, 30.f };

    int type = OBJ_TYPE::DESTROY_ABLE + OBJ_TYPE::HURT_ABLE;
    SetObjectType(type);

   // D3DXCreateTextureFromFile(m_pGraphicDev, 
   //     L"../Bin/Resource/Texture/Monster/Sprite_MonsterTrashBig.png", &m_pTexture);

    vector<IDirect3DBaseTexture9*> textComp = m_pTextureCom->Get_Texture();

    m_pAnimatorCom->CreateAnimation(L"MoveFront", 
        (IDirect3DTexture9*)textComp[0], _vec2(0.f, 0.f),
      _vec2(582.f, 582.f), _vec2(582.f, 0.f), 0.2f, 5);

    m_pAnimatorCom->CreateAnimation(L"MoveFrontRight",
        (IDirect3DTexture9*)textComp[0], _vec2(582.f * 4, 0.f),
        _vec2(582.f, 582.f), _vec2(582.f, 582.f), 0.2f, 5);

    m_pAnimatorCom->CreateAnimation(L"MoveRight",
        (IDirect3DTexture9*)textComp[0], _vec2(582.f * 2, 582.f),
        _vec2(582.f, 582.f), _vec2(582.f, 582.f), 0.2f, 5);

    m_pAnimatorCom->CreateAnimation(L"MoveBackRight",
        (IDirect3DTexture9*)textComp[0], _vec2(582.f, 582.f * 2),
        _vec2(582.f, 582.f), _vec2(582.f, 582.f), 0.2f, 5);

    m_pAnimatorCom->CreateAnimation(L"MoveBack",
        (IDirect3DTexture9*)textComp[0], _vec2(0.f, 582.f * 3),
        _vec2(582.f, 582.f), _vec2(582.f, 582.f), 0.2f, 5);

    m_pAnimatorCom->CreateAnimation(L"MoveBackLeft",
        (IDirect3DTexture9*)textComp[0], _vec2(582.f * 4, 582.f * 3),
        _vec2(582.f, 582.f), _vec2(582.f, 582.f), 0.2f, 5);

    m_pAnimatorCom->CreateAnimation(L"MoveLeft",
        (IDirect3DTexture9*)textComp[0], _vec2(582.f * 3, 582.f * 4),
        _vec2(582.f, 582.f), _vec2(582.f, 582.f), 0.2f, 5);

    m_pAnimatorCom->CreateAnimation(L"MoveFrontLeft",
        (IDirect3DTexture9*)textComp[0], _vec2(582.f, 582.f * 5),
        _vec2(582.f, 582.f), _vec2(582.f, 582.f), 0.2f, 5);

    m_tMonsterHP.iCurHP = 3;
    m_tMonsterHP.iMaxHP = 3;
    m_fMoveSpeed = 10.f;

    return S_OK;
}

void CMonsterSlimeFast::LateReady_GameObject()
{
    Engine::CGameObject::LateReady_GameObject();

    CTransform* PlayerTrasform = static_cast<Engine::CTransform*>(
        m_CPlayer->Get_Component(ID_DYNAMIC, L"Com_Transform"));
    _vec3 PlayerPos;
    PlayerTrasform->Get_Info(INFO_POS, &PlayerPos);
    PlayerPos.x += 70;
    PlayerPos.z += 70;
    m_pTransformCom->Set_Pos(PlayerPos);

    CGameObject* HPBar = CMonsterHPUI::Create(m_pGraphicDev);
    NULL_CHECK_RETURN(HPBar, );
    FAILED_CHECK_RETURN(m_pLayer->Add_GameObject(L"MonsterHP_UI", HPBar), );


    static_cast<CMonsterHPUI*>(HPBar)->SetMonster(this);
}

_int CMonsterSlimeFast::Update_GameObject(const _float& fTimeDelta)
{
    if (!m_activation)
        return 0;
    Add_RenderGroup(RENDER_ALPHA, this);

    if (m_tMonsterHP.iCurHP == 0)
    {
        m_activation = false;
        return 0;
    }

    DurationInvincible(fTimeDelta);
    MoveToPlayer(fTimeDelta);
    return Engine::CGameObject::Update_GameObject(fTimeDelta);
}

void CMonsterSlimeFast::LateUpdate_GameObject(const _float& fTimeDelta)
{
    if (!m_activation)
        return;

    KnockBack(fTimeDelta, m_vKnockBackDir);
    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CMonsterSlimeFast::Render_GameObject()
{
    if (!m_activation)
        return;

    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
    m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    m_pTextureCom->Set_Texture();
    /*switch (num)
    {
    case 0:
        m_pAnimatorCom->Play(L"MoveFront", true);
        break;
    case 1:
        m_pAnimatorCom->Play(L"MoveFrontRight", true);
        break;
    case 2:
        m_pAnimatorCom->Play(L"MoveRight", true);
        break;
    case 3:
        m_pAnimatorCom->Play(L"MoveBackRight", true);
        break;
    case 4:
        m_pAnimatorCom->Play(L"MoveBack", true);
        break;
    case 5:
        m_pAnimatorCom->Play(L"MoveBackLeft", true);
        break;
    case 6:
        m_pAnimatorCom->Play(L"MoveLeft", true);
        break;
    case 7:
        m_pAnimatorCom->Play(L"MoveFrontLeft", true);
        break;
    default:
        break;
    }*/
    m_pAnimatorCom->Play(L"MoveFront", true);
    m_pAnimatorCom->render();

    //m_pTextureCom->Set_Texture(MONSTER);
    //m_pAnimationCom->Render_Buffer();
    if (!m_bInvincible)
        m_pBoundBox->Render_Buffer();

    m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  // �̰� ���������ָ� �ȵ� ���������� ��ġ������ ����Ǳ� ������
    m_pGraphicDev->SetTexture(0, NULL);  // �̰� ���������ָ� �״�� �ؽ�ó ���� �̰͵� ���������� ���������� ��ġ������ �ǹǷ�


}

void CMonsterSlimeFast::OnCollision(CGameObject* _pOther)
{
    if (!m_activation)
        return;

    if (_pOther->GetObjectKey() != L"PlayerInteractionBox")
        return;

    m_CPlayer = dynamic_cast<CPlayerInteractionBox*>(_pOther)->GetPlayer();
    if (m_CPlayer->GetSwingTrigger() && !m_bInvincible)
    {
        m_vKnockBackDir = m_CPlayer->GetPlayerDirVector2();
        m_bKnockBackTrigger = true;
        m_bInvincible = true;
        SetMonsterCurHP(-1);
    }
}

HRESULT CMonsterSlimeFast::Add_Component()
{
    CComponent* pComponent = NULL;

    pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

    pComponent = m_pBoundBox = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_pBoundBox->SetGameObjectPtr(this);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });

    /*pComponent = m_pAnimationCom = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Proto_PlayerAnim"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Animation", pComponent });*/

    pComponent = m_pAnimatorCom = dynamic_cast<CAnimator2*>(Engine::Clone_Proto(L"Proto_Animator"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Ani_Buffer", pComponent });

    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_MonsterTrashBig"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Texture", pComponent });

}

CMonsterSlimeFast* CMonsterSlimeFast::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CMonsterSlimeFast* pMonster = new CMonsterSlimeFast(pGraphicDev);

    if (FAILED(pMonster->Ready_GameObject()))
    {
        Safe_Release(pMonster);
        MSG_BOX("Monster Create Failed");
        return nullptr;
    }

    return pMonster;
}

void CMonsterSlimeFast::Free()
{
    Engine::CGameObject::Free();
}
