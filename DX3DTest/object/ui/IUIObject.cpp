#include "stdafx.h"
#include "IUIObject.h"

IUIObject::IUIObject(LPD3DXSPRITE pSprite, int uiTag)
	: m_bDrawBorder(true)
	, m_pSprite(pSprite)
	, m_uiTag(uiTag)
	, m_color(D3DXCOLOR(1, 1, 1, 1))
{
}

IUIObject::~IUIObject()
{
}

void IUIObject::Init()
{
}

void IUIObject::Update()
{
	UpdateCombinedPosition();

	for (auto p : m_vecChild)
	{
		p->Update();
	}
}


void IUIObject::Render()
{
	if (m_bDrawBorder) DrawBorder();

	for (auto p : m_vecChild)
	{
		p->Render();
	}
}


void IUIObject::UpdateCombinedPosition()
{
	m_combinedPos = m_pos;

	if (m_pParent)
	{
		m_combinedPos += static_cast<IUIObject*>(m_pParent)->GetCombinedPosition();
	}
}


void IUIObject::DrawBorder()
{
	RECT r;
	GetFinalRect(&r);
	
	vector<VERTEX_RHWC> vecVertex;
	vecVertex.reserve(5);
	D3DCOLOR c = WHITE;
	vecVertex.push_back(VERTEX_RHWC(D3DXVECTOR4(r.left, r.top, 0, 1), c));
	vecVertex.push_back(VERTEX_RHWC(D3DXVECTOR4(r.right, r.top, 0, 1), c));
	vecVertex.push_back(VERTEX_RHWC(D3DXVECTOR4(r.right, r.bottom, 0, 1), c));
	vecVertex.push_back(VERTEX_RHWC(D3DXVECTOR4(r.left, r.bottom, 0, 1), c));
	vecVertex.push_back(VERTEX_RHWC(D3DXVECTOR4(r.left, r.top, 0, 1), c));

	DX::GetDevice()->SetFVF(VERTEX_RHWC::FVF);
	DX::GetDevice()->DrawPrimitiveUP(D3DPT_LINESTRIP, vecVertex.size() - 1, &vecVertex[0], sizeof(VERTEX_RHWC));
}


IUIObject* IUIObject::FindChildByUITag(int nTag)
{
	if (m_uiTag == nTag)
		return this;

	for (auto p : m_vecChild)
	{
		IUIObject* pChild = ((IUIObject*)p)->FindChildByUITag(nTag);

		if (pChild)
			return pChild;
	}
	return NULL;
}

void IUIObject::GetFinalRect(RECT *rect)
{
	D3DXMATRIXA16 mat;
	m_pSprite->GetTransform(&mat);
	int left = mat._41 + m_combinedPos.x * mat._11;
	int top = mat._42 + m_combinedPos.y * mat._22;
	int right = left + m_size.x * mat._11;
	int bottom = top + m_size.y * mat._22;

	SetRect(rect, left, top, right, bottom);
}


