#pragma once

// �̹��� : Ư�� �ִϸ��̼� ����� ��� �ִ� png���� �� �� (Sprite_BabyOgu_Idle.png)
// ������ : �̹��� �ȿ� �ִ� �ִϸ��̼� �� ���� (Idle�̹����� 7x4 ������)

#include "VIBuffer.h"
#include "Export_Utility.h"
BEGIN(Engine)

class ENGINE_DLL CAnimation : public CVIBuffer//CComponent
{

private:
	explicit CAnimation();
	explicit CAnimation(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAnimation(const CAnimation& rhs);
	virtual ~CAnimation();

public:
	HRESULT					Ready_Animation(const vector<_vec2> _vecFrameCount,
		const vector<vector<int>*> _vecFramePlay);

	virtual  _int			Update_Component(const _float& fTimeDelta);
	virtual  void			LateUpdate_Component(const _float& fTimeDelta);
	virtual	 void   		Render_Buffer();

public:
	void SetAnimFrame(PLAYERSTATE _ePlayerState, bool _bDiagonal = false);
	void SetAnimDir(int _dir, bool& _bDiagonal)
	{
		if (m_iCurrentDir != _dir)
		{
			currentFrame = 0;
			m_iCurrentDir = _dir;
			switch (_dir)
			{
			case (int)OBJ_DIRECTION::OBJDIR_FRONT:
			case (int)OBJ_DIRECTION::OBJDIR_BACK:
			case (int)OBJ_DIRECTION::OBJDIR_LEFT:
			case (int)OBJ_DIRECTION::OBJDIR_RIGHT:
				m_eCurrentDir = log(_dir) / log(2); // 0,1,2,3
				_bDiagonal = false;
				break;

			case (int)OBJ_DIRECTION::OBJDIR_LEFTFRONT:
			case (int)OBJ_DIRECTION::OBJDIR_LEFTBACK:
			case (int)OBJ_DIRECTION::OBJDIR_RIGHTFRONT:
			case (int)OBJ_DIRECTION::OBJDIR_RIGHTBACK:
				m_eCurrentDir = round(_dir * 0.6 - 3);
				_bDiagonal = true;
				break;
			}

			if (m_bIsDiagonal != _bDiagonal)
			{
				m_bIsDiagonal = _bDiagonal;
				SetAnimFrame(m_eCurrentState, m_bIsDiagonal);
			}

			UpdateUV();
		}
	}

	void UpdateUV()
	{
		VTXTEX* pVertex = nullptr;
		m_pVB->Lock(0, 0, (void**)&pVertex, 0);

		int frameX = m_vecFramePlay[m_eCurrentState][m_eCurrentDir][currentFrame]
			% (int)m_currentFrameCount.x;
		int frameY = m_vecFramePlay[m_eCurrentState][m_eCurrentDir][currentFrame]
			/ m_currentFrameCount.x;

		pVertex[0].vTexUV = { frameX * m_vecCurrentFrameUV.x,
							  frameY * m_vecCurrentFrameUV.y };
		pVertex[1].vTexUV = { pVertex[0].vTexUV.x + m_vecCurrentFrameUV.x,
							  pVertex[0].vTexUV.y };
		pVertex[2].vTexUV = { pVertex[0].vTexUV.x + m_vecCurrentFrameUV.x,
							  pVertex[0].vTexUV.y + m_vecCurrentFrameUV.y };
		pVertex[3].vTexUV = { pVertex[0].vTexUV.x,
							  pVertex[0].vTexUV.y + m_vecCurrentFrameUV.y };

		m_pVB->Unlock();
	}
private:

	// Loading���� Animation.dat ������ �޾ƿͼ�
	// �ش� ������Ʈ�� ��� �ൿ �ִϸ��̼��� ��� ����
	vector<_vec2>		 m_vecFrameCount;
	vector<vector<int>*> m_vecFramePlay;

	// ���� �������� ���¿� ���� �ִϸ��̼� ����
	_vec2				 m_currentFrameCount; // ������ ����
	_vec2				 m_vecCurrentFrameUV; // ���� �������� ����ϱ� ���� UV ����
	vector<int>			 m_currentFramePlay[OBJ_DIRECTION::OBJDIR_END]; // ������ ��� ����


	PLAYERSTATE			m_eCurrentState;
	int					m_eCurrentDir;
	int					m_iCurrentDir;
	bool				m_bIsDiagonal;
	int					currentFrame;

	float				m_fAccTime;

public:
	static CAnimation* Create(LPDIRECT3DDEVICE9	      pGraphicDev,
		const vector<_vec2>		  _vecFrameCount,
		const vector<vector<int>*> _vecFramePlay);

	virtual CComponent* Clone();

private:
	virtual void			Free();


};

END