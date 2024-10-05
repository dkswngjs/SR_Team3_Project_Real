#include "pch.h"
#include "PlayerIdle.h"
#include "Player.h"

PlayerIdle* PlayerIdle::m_instance = nullptr;

void PlayerIdle::Enter()
{
    if (!m_pStateController)
        SetComponent();

    (dynamic_cast<CPlayer*>(m_CGameObject))->SetPlayerState(PLAYERSTATE::PLY_IDLE);

    m_fDuration = 0.f;
    m_fKeyDownTimer = 0.f;
}

void PlayerIdle::Update(const _float& fTimeDelta)
{
    // IdleDance
    m_fDuration += fTimeDelta;
    if (m_fDuration >= 3.f)
    {
        PlayerDance::GetInstance()->SetDanceType(0);
        m_pStateController->ChangeState(PlayerDance::GetInstance(), m_CGameObject);
    }

    // Move, Dash, Push
    if (Engine::GetKeyPress(CONTROL_KEY::PLY_UPKEY) ||
        Engine::GetKeyPress(CONTROL_KEY::PLY_DOWNKEY) ||
        Engine::GetKeyPress(CONTROL_KEY::PLY_LEFTKEY) ||
        Engine::GetKeyPress(CONTROL_KEY::PLY_RIGHTKEY))
    {
        CGameObject* obj = (dynamic_cast<CPlayer*>(m_CGameObject))->GetInteractingObj();

        if (obj && obj->IncludingType(OBJ_TYPE::PUSH_ABLE))
            m_pStateController->ChangeState(PlayerPush::GetInstance(), m_CGameObject);

        else
        {
            if (Engine::GetKeyPress(CONTROL_KEY::PLY_DASHKEY))
                m_pStateController->ChangeState(PlayerDash::GetInstance(), m_CGameObject);
            else
                m_pStateController->ChangeState(PlayerMove::GetInstance(), m_CGameObject);
        }
    }

    // Swing
    if (Engine::GetKeyPress(CONTROL_KEY::PLY_SWINGKEY))
        m_pStateController->ChangeState(PlayerSwing::GetInstance(), m_CGameObject);

    // Lift
    if (Engine::GetKeyDown(CONTROL_KEY::PLY_LIFTKEY))
    {
        CGameObject* obj = (dynamic_cast<CPlayer*>(m_CGameObject))->GetInteractingObj();

        if (obj && obj->IncludingType(OBJ_TYPE::LIFT_ABLE))
            m_pStateController->ChangeState(PlayerLift::GetInstance(), m_CGameObject);
    }

    // Dance
    if (Engine::GetKeyPress(CONTROL_KEY::PLY_DANCEKEY))
    {
        m_fKeyDownTimer += fTimeDelta;
        if (m_fKeyDownTimer > 1.f)
        {
            PlayerDance::GetInstance()->SetDanceType(1);
            m_pStateController->ChangeState(PlayerDance::GetInstance(), m_CGameObject);
        }
    }

    // Smash
    if (Engine::GetKeyDown(CONTROL_KEY::PLY_SMASHKEY))
    {
        m_pStateController->ChangeState(PlayerSmash::GetInstance(), m_CGameObject);
    }

    // Rolling
    if (Engine::GetKeyDown(CONTROL_KEY::PLY_ROLLKEY))
    {
        m_pStateController->ChangeState(PlayerRolling::GetInstance(), m_CGameObject);
    }
}


void PlayerIdle::Exit()
{
    m_fDuration = 0.f;
    m_fKeyDownTimer = 0.f;
}

