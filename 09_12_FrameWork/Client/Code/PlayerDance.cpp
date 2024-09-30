#include "pch.h"
#include "PlayerDance.h"
#include "Player.h"

PlayerDance* PlayerDance::m_instance = nullptr;

void PlayerDance::Enter()
{
    (dynamic_cast<CPlayer*>(m_CGameObject))->FixPlayerDir(OBJDIR_FRONT);
    switch (m_iDanceType)
    {
        // ������ �� ���� �� ������ ����
    case 0:
        (dynamic_cast<CPlayer*>(m_CGameObject))->SetPlayerState(
            PLAYERSTATE::PLY_IDLEDANCE);

        break;
        // eŰ ���� ü�� ȸ�� �ϴ� ����
    case 1:
        (dynamic_cast<CPlayer*>(m_CGameObject))->SetPlayerState(
            PLAYERSTATE::PLY_DANCE);

        m_fTickTime = 0.f;
        m_iPlayerMaxHP = (dynamic_cast<CPlayer*>(m_CGameObject))->GetPlayerHP().iMaxHP;
        break;
    }
    
    if (!m_pStateController)
        SetComponent();
}

void PlayerDance::Update(const _float& fTimeDelta)
{
    switch (m_iDanceType)
    {
    case 0:
        if(Engine::GetAnyActionKeyDown())
            m_pStateController->ChangeState(PlayerIdle::GetInstance(), m_CGameObject);
        break;

    case 1:
        if (Engine::GetKeyDown(CONTROL_KEY::PLY_DANCEKEY))
            m_pStateController->ChangeState(PlayerIdle::GetInstance(), m_CGameObject);

        m_fTickTime += fTimeDelta;
        if (m_fTickTime > 3.f)
        {
            m_fTickTime = 0.f;
            int iPlayerCurHP = (dynamic_cast<CPlayer*>(m_CGameObject))->GetPlayerHP().iCurHP;
            if (iPlayerCurHP < m_iPlayerMaxHP / 2)
                (dynamic_cast<CPlayer*>(m_CGameObject))->SetPlayerCurHP(1);
        }
        break;
    default:
        break;
    }

}


void PlayerDance::Exit()
{
}

