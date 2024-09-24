#include "pch.h"
#include "Object.h"
#include "Export_Utility.h"
#include "ImGuiManger.h"

CObject::CObject(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CGameObject(pGraphicDev)
{
}

CObject::~CObject()
{
}

HRESULT CObject::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//���⼭ �ؽ�ó �� ���� 

	m_vecTexture.resize(100);	
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/Object/object0.png", &m_vecTexture[0]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/Object/object1.png", &m_vecTexture[1]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/Object/object2.png", &m_vecTexture[2]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/Object/object3.png", &m_vecTexture[3]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/Object/object5.png", &m_vecTexture[4]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/Object/object6.png", &m_vecTexture[5]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/Object/object7.png", &m_vecTexture[6]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/Object/object8.png", &m_vecTexture[7]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/Object/object9.png", &m_vecTexture[8]);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/Object/object10.png", &m_vecTexture[9]);

		
		
	//D3DXCreateBox(m_pGraphicDev, 10.0f, 10.0f, 10.0f, &m_pMesh, NULL);		
	return S_OK;
}



_int CObject::Update_GameObject(const _float& fTimeDelta)
{

	Add_RenderGroup(RENDER_ALPHA, this);

	return Engine::CGameObject::Update_GameObject(fTimeDelta);
}

void CObject::LateUpdate_GameObject(const _float& fTimeDelta)
{
	Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CObject::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	

	//// ũ���̽� �ڽ� ������ �Ǵ°� 


	//LPD3DXMESH m_pMesh;
	//D3DXCreateBox(m_pGraphicDev, 1.5f, 1.5f, 1.5f, &m_pMesh, NULL);	
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_pMesh->DrawSubset(0);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//m_pGraphicDev->SetTexture(0, 0);

	if (m_strTextureKey == L"Wall") 
	{
		//auto iter = find_if(m_mapTexture.begin(), m_mapTexture.end(),);
		m_pGraphicDev->SetTexture(0, m_vecTexture[0]);
		
	}
	
	if (m_strTextureKey == L"Super")
	{
		//auto iter = find_if(m_mapTexture.begin(), m_mapTexture.end(),);
		m_pGraphicDev->SetTexture(0, m_vecTexture[1]);
	
	}
	
	if (m_strTextureKey == L"TelephonePole")
	{
		//auto iter = find_if(m_mapTexture.begin(), m_mapTexture.end(),);
		m_pGraphicDev->SetTexture(0, m_vecTexture[2]);
		
	}
	
	if (m_strTextureKey == L"BusStation")
	{
		//auto iter = find_if(m_mapTexture.begin(), m_mapTexture.end(),);
		m_pGraphicDev->SetTexture(0, m_vecTexture[3]);
		
	
	}
	
	if (m_strTextureKey == L"BreadStore")
	{
		m_pGraphicDev->SetTexture(0, m_vecTexture[4]);
		
		
	}
	
	if (m_strTextureKey == L"Telephone2Pole")
	{
		m_pGraphicDev->SetTexture(0, m_vecTexture[5]);
	
	
	}
	
	if (m_strTextureKey == L"Carpet")
	{
		m_pGraphicDev->SetTexture(0, m_vecTexture[6]);
		
		
	}
	
	if (m_strTextureKey == L"Ogu_House_Floor")
	{
		m_pGraphicDev->SetTexture(0, m_vecTexture[7]);
		
	}
	
	if (m_strTextureKey == L"Ogu_House_Table")
	{
		m_pGraphicDev->SetTexture(0, m_vecTexture[8]);
	}
	
	if (m_strTextureKey == L"Ogu_House")
	{
		m_pGraphicDev->SetTexture(0, m_vecTexture[9]);
	}


	//LPD3DXMESH* m_pMesh = new LPD3DXMESH;		
	//D3DXCreateBox(m_pGraphicDev, 1.0f, 1.0f, 1.0f, m_pMesh, NULL);	
	//(*m_pMesh)->DrawSubset(0);
	//m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());	

	m_pBufferCom->Render_Buffer();	
	

	m_pBoundBox->Render_Buffer();
	

	//m_pGraphicDev->SetTexture(0, 0);


	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//LPD3DXMESH pMesh = NULL;	
	//D3DXCreateBox(m_pGraphicDev, 1.5f, 1.5f, 1.5f, &pMesh, NULL);	
	//
	//// �޽��� FVF�� XYZ|DIFFUSE�� ��ȯ
	//LPD3DXMESH pTempMesh = NULL;	
	//pMesh->CloneMeshFVF(D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_DIFFUSE, m_pGraphicDev, &pTempMesh);	
	//
	//// ���� �޽��� �������ϰ� ��ȯ�� �޽��� ���
	//pMesh->Release();	
	//pMesh = pTempMesh;	
	//	
	//// ���ؽ� �����͸� �����ϱ� ���� ���ؽ� ���۸� ��(lock)��
	//struct CUSTOMVERTEX
	//{
	//	D3DXVECTOR3 position;   // ��ġ	
	//	D3DCOLOR    color;      // �÷�	
	//};
	//
	//CUSTOMVERTEX* pVertices = NULL;	
	//pMesh->LockVertexBuffer(0, (void**)&pVertices);	
	//
	//// ���ؽ� ���� Ȯ��
	//DWORD dwNumVertices = pMesh->GetNumVertices();	
	//
	//// �� ���ؽ��� �÷� ���� (����: ������)	
	//for (DWORD i = 0; i < dwNumVertices; ++i)	
	//{
	//	pVertices[i].color = D3DCOLOR_XRGB(255, 0, 0);  // ��� ���ؽ��� ������ ����	
	//}
	//
	//// ���ؽ� ���� ���	
	//pMesh->UnlockVertexBuffer();	
	//pMesh->DrawSubset(0);
	
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CObject::Add_Component()
{
	CComponent* pComponent = NULL;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });
	
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_PlayerTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture",pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });


	// 9�� 23�� �߰� ��ȯ �浹���� �ڽ� 
	pComponent = m_pBoundBox = dynamic_cast<CBoundBox*>(Engine::Clone_Proto(L"Proto_BoundBox"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);	
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_BoundBox", pComponent });	

	return S_OK;	
}

HRESULT CObject::SetUp_Material()
{
	return S_OK;
}

void CObject::Key_Input(const _float& fTimeDelta)
{
}

CObject* CObject::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CObject* pObject = new CObject(pGraphicDev);

	if(FAILED(pObject->Ready_GameObject()))
	{
		Safe_Release(pObject);
		MSG_BOX("pObject Create Failed");
		return nullptr;
	}

	return pObject;
}

void CObject::Free()
{
	Engine::CGameObject::Free();
}
