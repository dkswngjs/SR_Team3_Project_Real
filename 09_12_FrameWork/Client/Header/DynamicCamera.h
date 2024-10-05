#pragma once

#include "Camera.h"
#include "Base.h"
#include "Define.h"

enum class CAMERASTATE
{
	DEBUG = 0,
	PLAYER,
	EVENT
};
BEGIN(Engine)

class CRcTex;
class CTransform;

END

class CPlayer;

class CDynamicCamera : public CCamera
{
private:
	explicit CDynamicCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CDynamicCamera();

public:
	HRESULT   Ready_GameObject(const _vec3* pEye
		, const _vec3* pAt
		, const _vec3* pUp
		, const _float& _fFov
		, const _float& _fAspect
		, const _float& _fNear
		, const _float& _fFar);

	virtual	  void		LateReady_GameObject();
	virtual   _int		Update_GameObject(const _float& fTimeDelta);
	virtual   void		LateUpdate_GameObject(const _float& fTimeDelta);
	virtual   void      Render_GameObject();

	void  ZoomTo(_float fRatio, _float fDuration);
	void  ShakeMove(_float fDuration);

private:
	void  Key_Input(const _float& fTimeDelta);
	void  Mouse_Move(const _float& fTimeDelta);
	void  MoveToPlayer(const _float& fTimeDelta);

	void  ZoomToTrigger(const _float& fTimeDelta);
	void  ResetZoom(const _float& fTimeDelta);

	void  ShakeMoveTrigger(const _float& fTimeDelta);
	void  GetPlayerInfo();

private:

	_matrix m_matCameraWorld;
	// 0923 ���� : ī�޶� ��忡 ���� ȭ�� ����� ���� ����
	CAMERASTATE m_eCameraState;

	CPlayer* m_Player;
	CTransform* m_playerTransform;
	_vec3 m_vPlayerPos; // �÷��̾��� ��ǥ

	_vec3 m_vIntervalPos; // �÷��̾� ��ǥ���� �̸�ŭ ������ ���� ī�޶� ��ġ��ŵ�ϴ�.
	_vec3 m_vOriginInterval; // ����� IntervalPos ��
	float m_fMoveToPlayerSpeed;

	// Zoom
	// �ܺο��� ZoomTo()�Լ��� ���� true�� ��, ������Ʈ���� ����/�ƿ��� ����
	bool m_bZoomTrigger;

	// �ð��� ����� ���� += fTimeDelta�Ͽ� duration���� Ŀ���� ����/�ƿ��� ������.
	float m_fZoomDeltaTime;

	// ī�޶� �� ���� 100�� �⺻ ��Ȳ / 50�̸� �⺻���� ���ݸ�ŭ ���, 150�̸� �⺻���� �ι踸ŭ Ȯ��
	float m_fZoomRatio;

	// ZoomRatio���� ������� �ɸ��� �ð�
	float m_fZoomDuration;

	// ��ǥ����
	_vec3 m_vTowardMove;

	// �ð��� ����� ���� += fTimeDelta�Ͽ� 3���� Ŀ���� ������ ���۵ȴ�.
	float m_fZoomInTimer;

	// Shake =========================================================
	float m_fShakeDeltaTime;
	bool m_bShakeTrigger;
	float fShakeTickTime;
	float m_fShakeDuration;
	float m_fShakePower;
	float m_fPrevShakeAtYPos;

	float elapsedTime = 0.0f;
	float shakeAmplitude = 0.1f;  // ��鸲�� ���� (������ ����)
	float shakeFrequency = 20.0f;  // ��鸲�� �� (�ʴ� ���� Ƚ��)
	float shakeDuration = 0.01f;   // ��鸲�� ���� �ð�

	// ���� ȿ���� ������ �ð�
	float shakeTimer = shakeDuration;

public:
	static  CDynamicCamera* Create(LPDIRECT3DDEVICE9 pGraphicDev
		, const _vec3* pEye
		, const _vec3* pAt
		, const _vec3* pUp
		, const _float& _fFov = D3DXToRadian(60.f)
		, const _float& _fAspect = (float)WINCX / WINCY
		, const _float& _Near = 0.1f
		, const _float& _fFar = 1000.f);

private:
	virtual  void Free();

};

