#include "pch.h"
#include "PlayerSwing.h"
#include "Player.h"

PlayerSwing* PlayerSwing::m_instance = nullptr;

void PlayerSwing::Enter()
{
    if (!m_pStateController)
        SetComponent();

    (dynamic_cast<CPlayer*>(m_CGameObject))->SetPlayerState(PLAYERSTATE::PLY_SWING);

    m_pAnimationCom->SetTextureScale(1.5f);
}

void PlayerSwing::Update(const _float& fTimeDelta)
{
    if (m_pAnimationCom->IsAnimationEnd())
        m_pStateController->ChangeState(PlayerIdle::GetInstance(), m_CGameObject);

    if (m_pAnimationCom->GetCurrentFrame() >= 2)
        dynamic_cast<CPlayer*>(m_CGameObject)->SetSwingTrigger(true);

}

void PlayerSwing::Exit()
{
    CTransform* m_playerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(
        ID_DYNAMIC, L"Layer_GameLogic", L"Player", L"Com_Transform"));

    m_pAnimationCom->SetTextureScale(1.f);

    dynamic_cast<CPlayer*>(m_CGameObject)->SetSwingTrigger(false);

}