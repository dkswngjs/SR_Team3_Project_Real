#pragma once
#include "GameObject.h"
#include "Export_System.h"
#include "Export_Utility.h"
#include "InteractionButton.h"
#include "Player.h"
#include "QuestUI.h"
#include "QuestAccept.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTriCol;
class CTransform;
class CCollider;

END
class CTextBox;

class CNPC : public Engine::CGameObject
{
protected:
	explicit CNPC(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CNPC();
public:
	struct NPC_INFO
	{
		const _tchar* pName;
		const _tchar* pContent; //��ȭ ����
	};
	enum MARKER { EXCLAMATION, GRAYQUEST, YELLOWQUEST, MARK_END };

public:
	virtual   HRESULT   Ready_GameObject();
	virtual	  void		LateReady_GameObject();
	virtual   _int      Update_GameObject(const _float& fTimeDelta);
	virtual   void	    LateUpdate_GameObject(const _float& fTimeDelta);
	virtual   void      Render_GameObject();

	virtual   void		OnCollision(CGameObject* _pOther) {}
	virtual   void		OnCollisionEnter(CGameObject* _pOther) {}
	virtual   void		OnCollisionExit(CGameObject* _pOther) {}

public:
	NPC_INFO	Get_Info() { return m_tInfo; }

protected:
	HRESULT    Add_Component();

protected:
	Engine::CRcTex* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CTransform* m_pTransformCom;
	Engine::CCollider* m_pColliderCom;

	Engine::CTexture* m_pMarkTextureCom[MARK_END];
	Engine::CTransform* m_pMarkTransformCom;

	NPC_INFO				m_tInfo;
	CQuestUI::QUEST_INFO	m_tQuestInfo;
	_bool					m_bConversation; // ��ȭ ��

	_bool					m_bQuestAccept; // ����Ʈ ��������
	// �̻��Ⱑ false�� �� ����ǥ / true�� �� ����ǥ 
	_bool					m_bQuestSucess; // Ŭ���� ����

	_bool					m_bQuestClear; // Ŭ���� ����
	// �̻��Ⱑ true �Ǹ� ����ǥ ����ǥ �Ѵ� ��� ����

	CInteractionButton* m_pInterButton;
	CTextBox* m_pTextBox;
	CPlayer* m_pPlayer;
	CInvenUI* m_pInven;
	CQuestUI* m_pQuestUI;
	CQuestAccept* m_pQuestAcceptUI;

protected:
	virtual void Free();

};

