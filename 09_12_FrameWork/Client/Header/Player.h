#pragma once
#include "GameObject.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerDash.h"
#include "PlayerSwing.h"
#include "PlayerLift.h"
#include "PlayerLiftMove.h"
#include "PlayerPush.h"
#include "PlayerDance.h"
#include "PlayerSmash.h"
#include "PlayerRolling.h"
#include "PlayerHurt.h"
#include "PlayerPickUp.h"
#include "EquipHat.h"
#include "Export_Utility.h"

//����
#pragma region ����
#include "PowerUI.h"
#include "SpeedUI.h"

#include "ExploreHat.h"
#include "PartyHat.h"
#include "Mohican.h"
#include "EnkyHat.h"
#include "AppleHat.h"
#include "Penguin.h"
#include "PoopHat.h"

#include "SmallFruit.h"
#include "MiddleFruit.h"
#include "BigFruit.h"
#include "SmallHerb.h"
#include "MiddleHerb.h"
#include "BigHerb.h"
#include "SmallRoot.h"
#include "MiddleRoot.h"
#include "BigRoot.h"
#include "CookSmallFish.h"
#include "CookMiddleFish.h"
#include "CookBigFish.h"

#include "Branch.h"
#include "Leaf.h"

#include "ExpressTicket.h"
#include "Net.h"

#include "QuestUI.h"
#include "QuickSlot.h"
#include "InvenUI.h"

#pragma endregion ����


BEGIN(Engine)

class CTexture;
class CRcTex;
class CTransform;
class CCamera;
class CCalculator;
class CStateController;

//0923 ��ȯ �浹 �׽�Ʈ
class CCollider;

END

class CBuffUI;//1003
class CPlayer : public Engine::CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayer();

public:
	struct PLAYERHP
	{
		_int	iCurHP;
		_int	iMaxHP;
	};

	virtual			HRESULT			Ready_GameObject();
	virtual			void			LateReady_GameObject();
	virtual			_int			Update_GameObject(const _float& fTimeDelta);
	virtual			void			LateUpdate_GameObject(const _float& fTimeDelta);
	virtual			void			Render_GameObject();

	virtual			void			OnCollisionEnter(CGameObject* _pOther);
	virtual			void			OnCollisionExit(CGameObject* _pOther);
public:
	// �ִϸ��̼� ���� /////////////////////////////////////////////////////////
	CAnimation* GetAnimationComp() { return m_pAnimationCom; }

	PLAYERSTATE		GetPlayerState() { return m_ePlayerState; }
	void			SetPlayerState(PLAYERSTATE _ePlayerState)
	{
		m_ePlayerState = _ePlayerState;
		m_pAnimationCom->SetAnimFrame(m_ePlayerState, m_bIsDiagonal);
	}

	_bool			GetSwingTrigger() { return m_bSwingTrigger; }
	void			SetSwingTrigger(_bool bSwing) { m_bSwingTrigger = bSwing; }
	_bool			GetPushTrigger() { return m_bPushTrigger; }
	void			SetPushTrigger(_bool bPush) { m_bPushTrigger = bPush; }
	
	CGameObject* GetInteractionBox() { return m_objInteractionBox; }
	void			SetInteractionBox(CGameObject* _obj) { m_objInteractionBox = _obj; }
	CGameObject* GetInteractingObj() { return m_objInteracting; }
	void			SetInteractingObj(CGameObject* _obj) { m_objInteracting = _obj; }

	_vec3			GetPlayerDirVector() { return m_vPlayerDir; }
	_vec3			GetPlayerDirVector2()
	{
		_vec3 returnValue = _vec3(0.f, 0.f, 0.f);
		if (m_iPlayerDir & OBJDIR_LEFT)
			returnValue.x = -1;
		else if (m_iPlayerDir & OBJDIR_RIGHT)
			returnValue.x = 1;
		else
			returnValue.x = 0;

		if (m_iPlayerDir & OBJDIR_BACK)
			returnValue.z = 1;
		else if (m_iPlayerDir & OBJDIR_FRONT)
			returnValue.z = -1;
		else
			returnValue.z = 0;

		return returnValue;

	}
	bool			IsPlayerDiagonal() { return m_bIsDiagonal; }
	void			SetPlayerDirection();
	void			FixPlayerDir(int _fixDir)
	{
		m_iPlayerDir = _fixDir;
		DisableDiagonal();
		m_pAnimationCom->SetAnimDir(m_ePlayerState, m_iPlayerDir, false);
	}
	void			DisableDiagonal() { m_bIsDiagonal = false; }
	_bool			GetPassAble() { return m_bPassAble; }

	// �÷��̾� ���¸� ������ ȹ�� ������� �����մϴ�.
	void			ChangePickUpState();
	
	// �÷��̾� �ɷ�ġ ���� //////////////////////////////////////////////////////
	float			GetMoveSpeed() { return m_fMoveSpeed; }
	void			SetMoveSpeed(float _fSpeed) { m_fMoveSpeed = _fSpeed; }
	float			GetItemMoveSpeed() { return m_fItemMoveSpeed; }
	void			SetItemMoveSpeed(float _itemSpeed) { m_fItemMoveSpeed += _itemSpeed; }

	int				GetItemAttackPower() { return m_iItemAttackPower; }
	void			SetItemAttackPower(int _itemPower) { m_iItemAttackPower += _itemPower; }
	//����

	_int			GetPlayerCoin() { return m_iPlayerCoin; }
	void			SetPlayerCoin(_int _iCoin) { m_iPlayerCoin += _iCoin; }
	_bool			GetVisitingStore() { return m_bStoreVisit; }
	void			SetVisitingStore(_bool _bVisit) { m_bStoreVisit = _bVisit; }

	PLAYERHP		GetPlayerHP() { return m_tPlayerHP; }
	_bool			GetPlayerQuestUI() { return m_bQuest; }//0928
	_bool			GetPlayerInven() { return m_bInven; }
	void			SetPlayerCurHP(_int _SetHP)
	{
		m_tPlayerHP.iCurHP += _SetHP;
		if (m_tPlayerHP.iCurHP > m_tPlayerHP.iMaxHP)
			m_tPlayerHP.iCurHP = m_tPlayerHP.iMaxHP;
		else if (m_tPlayerHP.iCurHP < 0)
			m_tPlayerHP.iCurHP = 0;
	}
	void			SetPlayerMaxHP(_int _SetHP)
	{
		m_tPlayerHP.iMaxHP = _SetHP;
	}
	//1003
	void			SetPowerTime(_int _SetTime, _float _SetPower = 10.f)
	{ 
		m_BuffArray[0]->Set_BuffTime(_SetTime);
		m_iItemAttackPower = _SetPower;
	}
	void			SetSpeedTime(_int _SetTime, _float _SetSpeed = 20.f)
	{ 
		m_BuffArray[1]->Set_BuffTime(_SetTime);
		m_fItemMoveSpeed = _SetSpeed;
	}


	void			SetInvincible(_bool value = true) { m_bInvincible = value; }
	bool			IsInvincible() { return m_bInvincible; }
	void			DurationInvincible(const _float& fTimeDelta);
	////////////////////////////////////////////////////////////////////////////
	CCamera*		GetCamera() { return m_pCamera; }
	void			SetCamera(CCamera* _camera) { m_pCamera = _camera; }


	void			SetEquipHat(CEquipHat* _equipHat) { m_equipHat = _equipHat; }
	CEquipHat*		GetEquipHat() { return m_equipHat; }
	//���� ���� 
	HRESULT			SetUp_Material();


private:
	HRESULT			Add_Component();
	void			Key_Input(const _float& fTimeDelta);
	_vec3			Piking_OnTerrain();
	void			Print_PlayerState();

private:
	Engine::CRcTex*				m_pBufferCom;
	Engine::CTransform*			m_pTransformCom;
	Engine::CTexture*			m_pTextureCom;
	Engine::CAnimation*			m_pAnimationCom;
	Engine::CCamera*			m_pCamera;
	Engine::CStateController*	m_pStateControlCom;
	Engine::CCollider*			m_pBoundBox;

	PLAYERSTATE					m_ePlayerState;

	_bool						m_bIsDiagonal;
	_vec3						m_vPlayerDir;
	_bool						m_bFixPlayerDir;

	_bool						m_bSwingTrigger;
	_bool						m_bPushTrigger;
	
	_vec3						m_vColPlayerPos;
	_vec3						m_vColliderPos;

	_bool						m_bPassAble;
	_bool						m_bInvincible;

	_int						m_iAttackPower;
	_int						m_iItemAttackPower;
	_float						m_fMoveSpeed;
	_float						m_fItemMoveSpeed;
	

	CGameObject*				m_objInteractionBox;  // ��ȣ�ۿ��� �ڽ�
	CGameObject*				m_objInteracting;     // �� �ڽ��� �浹 ���� ������Ʈ
	CEquipHat*					m_equipHat;

	//����
	CBuffUI*	m_BuffArray[2];

	CInvenUI*	m_pInven;
	CQuestUI*	m_pQuestUI;
	CQuickSlot* m_pQuickSlot;

	_int		m_iPlayerCoin;
	PLAYERHP	m_tPlayerHP;
	_bool		m_bInven;
	_bool		m_bQuest;
	_bool		m_bStoreVisit;

public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();

};

