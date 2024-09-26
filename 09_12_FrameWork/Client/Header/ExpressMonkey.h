#pragma once
#include "NPC.h"


class CExpressMonkey : public CNPC
{
	// 1. �浹 �� S��ư Ȱ��ȭ (��ȭ�ϱ�[S])
	// 2. TextBoxUI�� NPC �̸�, NPC ��ȭ���� ��� �۾� �ϳ��� ���
	//	  0.05�ʿ� �ѱ��ھ�..? ���^_^;;
	//    1) ��ǳ �ϳ��� �������
	//    2) ��ǳ ���� �� ���� �����̽��� Ŭ�� �� �ؽ�Ʈ ���� ��� + ���� �ؽ�Ʈ ��� 
	// 3. �÷��̾�� ����Ʈ �ֱ�
private:
	explicit CExpressMonkey(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual	 ~CExpressMonkey();

public:
	virtual   HRESULT   Ready_GameObject();
	virtual   _int      Update_GameObject(const _float& fTimeDelta);
	virtual   void	    LateUpdate_GameObject(const _float& fTimeDelta);
	virtual   void      Render_GameObject();

private:
	HRESULT    Add_Component();

public:
	static CExpressMonkey* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

