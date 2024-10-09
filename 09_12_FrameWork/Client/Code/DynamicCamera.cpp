#include "pch.h"
#include "DynamicCamera.h"
#include "Export_System.h"
#include "Export_Utility.h"
#include "Player.h"

//IMPLEMENT_SINGLETON(CDynamicCamera)

//CDynamicCamera::CDynamicCamera()
//{
//}

CDynamicCamera::CDynamicCamera(LPDIRECT3DDEVICE9 pGraphicDev)
    :CCamera(pGraphicDev)
    , m_Player(nullptr)
    , m_playerTransform(nullptr)
    , m_eCameraState(CAMERASTATE::PLAYER)
    , m_fZoomDeltaTime(0.f)
    , m_fZoomInTimer(0.f)
    , m_bZoomTrigger(false)
    , m_fZoomRatio(100.f)
    , m_fMoveToPlayerSpeed(0.f)
    , m_bMoveTrigger(false)
    , m_fShakeDeltaTime(0.f)
    , m_bShakeTrigger(false)
    , fShakeTickTime(0.f)
    , m_fShakeDuration(0.f)
    , m_fShakePower(0.3f)
{


}

CDynamicCamera::~CDynamicCamera()
{
}

HRESULT CDynamicCamera::Ready_GameObject(const _vec3* pEye
    , const _vec3* pAt
    , const _vec3* pUp
    , const _float& _fFov
    , const _float& _fAspect
    , const _float& _fNear
    , const _float& _fFar)
{
    m_vEye = *pEye;
    m_vAt = *pAt;
    m_vUp = *pUp;

    m_fFov = _fFov;
    m_fAspect = _fAspect;
    m_fNear = _fNear;
    m_fFar = _fFar;



    FAILED_CHECK_RETURN(CCamera::Ready_GameObject(), E_FAIL);

    return S_OK;
}

void CDynamicCamera::LateReady_GameObject()
{
    m_Player = dynamic_cast<CPlayer*>(Engine::Get_GameObject(
        L"Layer_GameLogic", L"Player"));
    dynamic_cast<CPlayer*>(m_Player)->SetCamera(this);

    m_playerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(
        ID_DYNAMIC, L"Layer_GameLogic", L"Player", L"Com_Transform"));
    NULL_CHECK_RETURN(m_playerTransform, );

    m_vIntervalPos.x = 0;
    m_vIntervalPos.y = 160;
    m_vIntervalPos.z = -160;
    m_vOriginInterval = m_vIntervalPos;

    m_playerTransform->Get_Info(INFO_POS, &m_vPlayerPos);
    m_vEye = m_vPlayerPos;
    m_vEye.y += m_vIntervalPos.y;
    m_vEye.z += m_vIntervalPos.z;
    m_vAt = { 0.f, -1.f, 1.f };
    m_vAt += m_vEye;

    srand((unsigned int)time(NULL));

    CCamera::LateReady_GameObject();
}

_int CDynamicCamera::Update_GameObject(const _float& fTimeDelta)
{
    _int iExit = CCamera::Update_GameObject(fTimeDelta);

    m_playerTransform->Get_Info(INFO_POS, &m_vPlayerPos);

    Key_Input(fTimeDelta);

    Add_RenderGroup(RENDER_UI, this);
    return iExit;
}

void CDynamicCamera::LateUpdate_GameObject(const _float& fTimeDelta)
{
    //D3DXMatrixInverse(&m_matCameraWorld, 0, &m_matView);
    //m_Player = dynamic_cast<CPlayer*>(Engine::Get_GameObject(
    //    L"Layer_GameLogic", L"Player"));
    m_fMoveToPlayerSpeed = dynamic_cast<CPlayer*>(m_Player)->GetMoveSpeed();
    /*ResetZoom(fTimeDelta);

    if (m_bZoomTrigger)
        ZoomToTrigger(fTimeDelta);*/

    if (m_bShakeTrigger)
        ShakeMoveTrigger(fTimeDelta);

    if (m_eCameraState == CAMERASTATE::PLAYER)
    {
        m_playerTransform->Get_Info(INFO_POS, &m_vPlayerPos);
        if (m_bMoveTrigger)
            MoveToPlayer(fTimeDelta);
        else
            CheckMoveTrigger();
    }

    else if (m_eCameraState == CAMERASTATE::DEBUG)
    {
        Mouse_Move(fTimeDelta);
    }

    RayTransfer();
    CCamera::LateUpdate_GameObject(fTimeDelta);
}

void CDynamicCamera::Render_GameObject()
{
    _vec2 vCountPos(100, 150);
    wchar_t str[32] = L"";
}

CDynamicCamera* CDynamicCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev
    , const _vec3* pEye
    , const _vec3* pAt
    , const _vec3* pUp
    , const _float& _fFov
    , const _float& _fAspect
    , const _float& _fNear
    , const _float& _fFar)
{

    CDynamicCamera* pCDynamicCamera = new CDynamicCamera(pGraphicDev);
    if (FAILED(pCDynamicCamera->Ready_GameObject(pEye, pAt, pUp, _fFov, _fAspect, _fNear, _fFar)))
    {

        Safe_Release(pCDynamicCamera);
        MSG_BOX("Dynamic Camera Create Failed");
        return nullptr;
    }

    return pCDynamicCamera;
}


void CDynamicCamera::Free()
{
    CCamera::Free();
}

void CDynamicCamera::Key_Input(const _float& fTimeDelta)
{
    if (Engine::GetKeyDown(DIK_F1))
    {
        m_eCameraState = CAMERASTATE::PLAYER;
        m_vEye = m_vPlayerPos;
        //  m_vAt = m_vToPlayerAt;
    }

    if (Engine::GetKeyDown(DIK_F2))
    {
        m_eCameraState = CAMERASTATE::DEBUG;
    }

    if (Engine::GetKeyDown(DIK_F3))
        m_eCameraState = CAMERASTATE::EVENT;

    if (m_eCameraState != CAMERASTATE::DEBUG)
        return;

    // ������� ����� �ϸ� ī�޶� ���� ����� ������ �� �ִ�.
    _matrix		matCamWorld;
    D3DXMatrixInverse(&matCamWorld, 0, &m_matView);

    // ī�޶� �̵�
    _vec3	vRight;
    memcpy(&vRight, &matCamWorld.m[0][0], sizeof(_vec3));

    _vec3	vLength = *D3DXVec3Normalize(&vRight, &vRight) * fTimeDelta * 5.f;
    if (Engine::Get_DIKeyState(DIK_D) & 0x80)
    {
        m_vEye += vLength;
        m_vAt += vLength;
    }
    if (Engine::Get_DIKeyState(DIK_A) & 0x80)
    {
        m_vEye -= vLength;
        m_vAt -= vLength;
    }

    _vec3	vFront{ 0.f, 0.f, 1.f };
    vLength = *D3DXVec3Normalize(&vFront, &vFront) * fTimeDelta * 5.f;

    if (Engine::Get_DIKeyState(DIK_W) & 0x80)
    {
        m_vEye += vLength;
        m_vAt += vLength;
    }
    if (Engine::Get_DIKeyState(DIK_S) & 0x80)
    {
        m_vEye -= vLength;
        m_vAt -= vLength;
    }


}

void CDynamicCamera::Mouse_Move(const _float& fTimeDelta)
{
    _matrix		matCamWorld;
    D3DXMatrixInverse(&matCamWorld, 0, &m_matView);

    _long	dwMouseMove(0);

    // ī�޶� �� ��/�ƿ�
    if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_Z))
    {
        _vec3	vLook;
        memcpy(&vLook, &matCamWorld.m[2][0], sizeof(_vec3));

        _vec3	vLength = *D3DXVec3Normalize(&vLook, &vLook)
            * fTimeDelta * dwMouseMove;

        m_vEye += vLength;
        m_vAt += vLength;
    }

    if (Engine::Get_DIMouseState(DIM_MB))
    {
        // ī�޶� �����¿� �̵�
        _vec3	vUp{ 0.f, 1.f, 0.f };
        _vec3 vLength = *D3DXVec3Normalize(&vUp, &vUp) * fTimeDelta;
        if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_Y))
        {
            m_vEye += vLength * dwMouseMove * 50.f;
            m_vAt += vLength * dwMouseMove * 50.f;
        }

        _vec3	vRight;
        memcpy(&vRight, &matCamWorld.m[0][0], sizeof(_vec3));
        vLength = *D3DXVec3Normalize(&vRight, &vRight) * fTimeDelta;
        if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_X))
        {
            m_vEye += vLength * -dwMouseMove * 50.f;
            m_vAt += vLength * -dwMouseMove * 50.f;
        }
    }

    if (Engine::Get_DIMouseState(DIM_RB))
    {
        // ī�޶� ȸ��
        if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_Y))
        {
            _vec3	vRight;
            memcpy(&vRight, &matCamWorld.m[0][0], sizeof(_vec3));

            _vec3	vLook = m_vAt - m_vEye;

            _matrix		matRot;
            D3DXMatrixRotationAxis(&matRot, &vRight, D3DXToRadian(dwMouseMove / 10.f));
            D3DXVec3TransformNormal(&vLook, &vLook, &matRot);

            m_vAt = m_vEye + vLook;
        }
        if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_X))
        {
            _vec3	vUp{ 0.f, 1.f, 0.f };

            _vec3	vLook = m_vAt - m_vEye;

            _matrix		matRot;
            D3DXMatrixRotationAxis(&matRot, &vUp, D3DXToRadian(dwMouseMove / 10.f));
            D3DXVec3TransformNormal(&vLook, &vLook, &matRot);

            m_vAt = m_vEye + vLook;
        }
    }
}

void CDynamicCamera::CheckMoveTrigger()
{
    // ī�޶� �����̴� ���̸� ������� ����
    // �÷��̾ ����Ʈ �� ������ ����� movetrigger = true
    _vec2 softZoneLT(m_vEye.x - 20, m_vEye.z + 20);
    _vec2 softZoneRB(m_vEye.x + 20, m_vEye.z - 20);

    _vec3 vTargetPos = m_vPlayerPos;
    vTargetPos.y += m_vIntervalPos.y;
    vTargetPos.z += m_vIntervalPos.z;

    _bool value = false;
    value |= softZoneLT.x >= vTargetPos.x || softZoneRB.x <= vTargetPos.x;
    value |= softZoneLT.y <= vTargetPos.z || softZoneRB.y >= vTargetPos.z;

    m_bMoveTrigger = value;
}

void CDynamicCamera::MoveToPlayer(const _float& fTimeDelta)
{
    _vec3 TargetPos = m_vPlayerPos;
    TargetPos.y += m_vIntervalPos.y;
    TargetPos.z += m_vIntervalPos.z;

    _vec3 vDir = TargetPos - m_vEye;
    m_fDistance = D3DXVec3Length(&vDir);

    vMoveDir = *D3DXVec3Normalize(&vDir, &vDir)
        * fTimeDelta * m_fMoveToPlayerSpeed * (m_fDistance / 5.f);

    if (m_fDistance < 1.f)
    {
        m_bMoveTrigger = false;
        return;
    }
    m_vEye += vMoveDir;
    m_vAt += vMoveDir;

}

void CDynamicCamera::ZoomTo(_float fRatio, _float fDuration)
{
    if (m_bZoomTrigger)
        return;

    m_bZoomTrigger = true;
    m_fZoomDeltaTime = 0.f;
    m_fZoomDuration = fDuration;

    // �������� ��ġ�� �� 
    m_vTowardMove = m_vOriginInterval * (abs(fRatio - m_fZoomRatio) / 100.f);
    // �ʴ� �̵��ӵ�
    m_vTowardMove /= m_fZoomDuration;

    if (fRatio > m_fZoomRatio)
        m_vTowardMove *= -1;

    m_fZoomRatio = fRatio;
}

void CDynamicCamera::ZoomToTrigger(const _float& fTimeDelta)
{
    // timedelta�� �̵��ӵ�
    m_vIntervalPos += (m_vTowardMove * fTimeDelta);

    m_fZoomDeltaTime += fTimeDelta;
    if (m_fZoomDeltaTime >= m_fZoomDuration)
    {
        m_bZoomTrigger = false;
    }

}

void CDynamicCamera::ResetZoom(const _float& fTimeDelta)
{
    /*if (m_fZoomRatio == 100)
        return;

    if (m_Player->GetPlayerState() == PLAYERSTATE::PLY_DASH ||
        m_Player->GetPlayerState() == PLAYERSTATE::PLY_DASHDIAGONAL)
        return;

    m_fZoomInTimer += fTimeDelta;
    if (m_fZoomInTimer >= 3.f)
    {
        ZoomTo(100.f, 2.f);
        m_fZoomInTimer = 0.f;
    }*/
}

void CDynamicCamera::ShakeMove(_float fDuration)
{
    shakeTimer = shakeDuration = fDuration;
    m_bShakeTrigger = true;
    m_fPrevShakeAtYPos = m_vAt.y;
}

void CDynamicCamera::ShakeMoveTrigger(const _float& fTimeDelta)
{
    if (shakeTimer > 0.0f)
    {
        // ��鸲�� ��� �ð� ���
        elapsedTime += fTimeDelta;

        // ���� �Լ��� ����� ���� ���� ���
        float offsetY = shakeAmplitude * sinf(elapsedTime * shakeFrequency * 2.0f * 3.141592f);  // ���� �Լ� ����

        // ���ο� ī�޶� ��ġ ����
        m_vAt.y += offsetY;

        // ���� Ÿ�̸� ����
        shakeTimer -= fTimeDelta;

        shakeAmplitude -= 0.01f;
    }

    else
    {
        m_bShakeTrigger = false;
        elapsedTime = 0.0f;
        shakeAmplitude = 0.1f;
        shakeTimer = shakeDuration;
        m_vAt.y = m_fPrevShakeAtYPos;
    }
}

void CDynamicCamera::RayTransfer()
{
    Ray ray;
    ray.origin = m_vEye;
    ray.direction = m_vAt - m_vEye;

    _float fU, fV, fDist;

    auto objectMap = Get_Layer(L"Layer_GameLogic")->GetLayerGameObjectPtr();
    for (auto objectIter = objectMap.begin(); objectIter != objectMap.end(); ++objectIter)
    {
        CTransform* objectTransform = dynamic_cast<CTransform*>(
            (*objectIter).second->Get_Component(ID_DYNAMIC, L"Com_Transform"));

        if (!objectTransform)
            continue;

        _matrix matWorld;
        objectTransform->Get_WorldMatrix(&matWorld);

        _vec3 objectPos;
        objectTransform->Get_Info(INFO_POS, &objectPos);

        CRcTex* objectRcTex = dynamic_cast<CRcTex*>(
            (*objectIter).second->Get_Component(ID_STATIC, L"Com_Buffer"));

        if (!objectRcTex)
            continue;

        // ������Ʈ�� �� ������ * ���� ��� -> ���� �������� ������Ʈ �Ǻ�
        _vec3* pos = objectRcTex->Get_VtxPos();
        _vec3* pWorldPos = new _vec3[4];
        for (int i = 0; i < 4; i++)
        {
            D3DXVec3TransformCoord(&pWorldPos[i], &pos[i], &matWorld);
        }

        //01
        //32
        _bool bCheck = false;

        // ��������
        bCheck |= D3DXIntersectTri(
            &pWorldPos[1],
            &pWorldPos[2],
            &pWorldPos[0],
            &ray.origin, &ray.direction, &fU, &fV, &fDist);

        // ���ʾƷ�
        bCheck |= D3DXIntersectTri(
            &pWorldPos[0],
            &pWorldPos[2],
            &pWorldPos[3],
            &ray.origin, &ray.direction, &fU, &fV, &fDist);

        (*objectIter).second->SetTransparent(bCheck);
    }
}
