#pragma once

class HeightMap :	public IMap
{
protected:
	LPD3DXMESH	m_pMesh;
	MTLTEX*		m_pMtlTex;
	
	vector<D3DXVECTOR3>	m_vecSurfaceVertex;
	vector<D3DXVECTOR3>	m_vecObstacleVertex;

public:
	HeightMap();
	virtual ~HeightMap();

	void Load(LPCTSTR fullPath, D3DXMATRIXA16 * pMat = NULL);
	void SetMtlTex(D3DMATERIAL9 &Mtl, LPDIRECT3DTEXTURE9 pTex);

	// IMap��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual bool GetHeight(OUT float & height, const D3DXVECTOR3 & pos) override;
	virtual bool CalcPickedPosition(D3DXVECTOR3 &vOut, WORD screenX, WORD screenY) override;
	
	void SetSurface();
	void SetObstacle();
	
};


/*
���� ���� �б�
fopen_s(&fp, szFullPath, "rb");
y = (unsigned char)fgetc(fp)

����Ʈ�� ������ 257 * 257

���ؽ��� ���� 257 * 257
Ÿ���� ���� 256 * 256

1. ���ؽ� ��ǥ ����(�븻�� 0, 1, 0)
�ε��� ��ȣ = z * 257 + x
y = ������ / 10.0f; �и�� ���� ����

2. �ε��� ����(�ð����)
1--3	0 = z * 257 + x
|\ |	1 = (z + 1) * 257 + x
| \|	2 = z * 257 + x + 1
0--2	3 = (z + 1) * 257 + x + 1

3. �븻�� ����
---u---
|\ |\ |
| \| \|
l--n--r
|\ |\ |
| \| \|
---d---

du ���Ϳ� lr ���͸� �����ؼ�
n��ġ�� �븻 ���� ���Ѵ�.

4. �޽��� ����(����ȭ����)

5. MtlTex ���� ����

== == == == == == == == == == == == == == == == == == ==
GetHeight �Լ�
ĳ������ ���� ����
1. ���� ���̽� ����
1--3	0�� x y ��ǥ ã��
|\ |	x = (int)��ġx
| \|	y = (int)��ġy
0--2	deltaX = ��ġx - x
deltaY = ��ġy - y

deltaX + deltaY <  1 : �Ʒ��� �ﰢ��
deltaX + deltaY	>= 1 : ���� �ﰢ��

2. ���� ���� ����ϱ�

1--3	�� �� ������ ���� ���� ���
|\ |	�Ʒ��� �ﰢ���� ��� : 0 + �������� * ��Ÿ��
| \|	���� �ﰢ���� ��� : 3 + �������� * ��Ÿ��
0--2
*/