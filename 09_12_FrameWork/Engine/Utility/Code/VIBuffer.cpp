#include "VIBuffer.h"

CVIBuffer::CVIBuffer()
	:m_pVB(nullptr)
	,m_pIB(nullptr)
	,m_dwFVF(0)
	,m_dwTriCnt(0)
	,m_dwVtxCnt(0)
	,m_dwVtxSize(0)
	,m_dwIdxSize(0)
{

}

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev)
	,m_pVB(nullptr)
	,m_pIB(nullptr)
	,m_dwFVF(0)
	,m_dwTriCnt(0)
	,m_dwVtxCnt(0)
	,m_dwVtxSize(0)
	,m_dwIdxSize(0)
{

}

CVIBuffer::CVIBuffer(const CVIBuffer& rhs)
	: CComponent(rhs)
	, m_pVB(rhs.m_pVB)
	, m_pIB(rhs.m_pIB)
	, m_dwFVF(rhs.m_dwFVF)
	, m_dwTriCnt(rhs.m_dwTriCnt)
	, m_dwVtxCnt(rhs.m_dwVtxCnt)
	, m_dwVtxSize(rhs.m_dwVtxSize)
	, m_dwIdxSize(rhs.m_dwIdxSize)
	, m_IdxFmt(rhs.m_IdxFmt)
{
	m_pVB->AddRef();
}

CVIBuffer::~CVIBuffer()
{
}

HRESULT CVIBuffer::Ready_Buffer()
{
	// ���ؽ� ���۸� �����ϴ� �Լ� 
	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexBuffer(m_dwVtxCnt * m_dwVtxSize, // ���ؽ� ������ ũ��
															0,                      // ���뵵(0�� ��� ���� ����)
															m_dwFVF,                // ���ؽ��� �Ӽ� �� 
															D3DPOOL_MANAGED,
															&m_pVB,
															NULL), 
															E_FAIL);

	FAILED_CHECK_RETURN(m_pGraphicDev->CreateIndexBuffer(m_dwTriCnt * m_dwIdxSize,
															0,
															m_IdxFmt,
															D3DPOOL_MANAGED,
															&m_pIB,
															NULL),
															E_FAIL);


	return S_OK;
}

void CVIBuffer::Render_Buffer()
{
	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);

	m_pGraphicDev->SetFVF(m_dwFVF);

	//m_pGraphicDev->SetTexture(0, NULL); //�ؽ�ó ���� ���ִ°� 
	//m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_dwTriCnt);

	
	m_pGraphicDev->SetIndices(m_pIB);

	//m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);// �̰� ��ĭ �׸��¹��
	//m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 4);  // �̰� ��ĭ �׸��¹��
	//m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 1, 0, 4, 0, 2);
	//m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);// 
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);

	//m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 4);
	//m_pGraphicDev->SetTexture(0, NULL);
	//
	////�� 6�̴�.�ε��� 3���� ����������ϱ� 1���� �ﰢ���� �׷��� 3x2= 6 �� �ǹ̴� 2���� �ﰢ�� 
	//m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt-8, 12, m_dwTriCnt-4);
}

void CVIBuffer::Free()
{
	Safe_Release(m_pIB);
	Safe_Release(m_pVB);


	CComponent::Free();

}
