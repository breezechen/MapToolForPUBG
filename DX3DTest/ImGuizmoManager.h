#pragma once
//#include <fstream>
class IDisplayObject;
class Camera;
//string ComboObjList[] = { "Church","Tree","Rock","Ware House" };
enum ObjList {
    CHURCH,
    TREE,
    ROCK,
    WAREHOUSE,
    COUNT
};
struct ObjInfo 
{
    int                 ID;
    ObjList             list;
    string              m_ObjName;
    D3DXVECTOR3         m_Position;
    D3DXVECTOR3         m_Rotation;
    D3DXVECTOR3         m_Scale;
    D3DXMATRIXA16       m_matTransform;
    IDisplayObject*     objPtr;
    
    ObjInfo()
        :  m_Position(0.0f, 0.0f, 0.0f), 
           m_Rotation(0.0f, 0.0f, 0.0f), 
           m_Scale(1.0f, 1.0f, 1.0f)
    {
        D3DXMatrixIdentity(&m_matTransform);
    }
    ObjInfo(int id, ObjList _list)
        : ObjInfo()
    {
        ID = id;
        list = _list;
    }

};

class ImGuizmoManager 
{
public:
    Camera* m_pCamera;
    LPDIRECT3DTEXTURE9 pButtonTexture;

    ImGuizmoManager();
    ~ImGuizmoManager();

    vector<IDisplayObject*> m_vecObjectContainer;

    map<string, ObjInfo*> m_mapObject;
    ObjInfo* m_pCurrentObject;

    int comboSelect;

    int churchCount=0;
    int treeCount=0;
    int rockCount=0;
    int wareHouseCount=0;

    // Camera projection
    bool isPerspective;
    float viewWidth;
    float cameraProjection[16];
    float cameraView[16];
    float objectMatrix[16];

public:
    void Init();
    void Update();
    void Render();

    void SetCurrentObject(ObjInfo* obj)
    {
        m_pCurrentObject = obj;
        //resetting the position to origin
        MatChangeDX2Float(objectMatrix, &m_pCurrentObject->m_matTransform);
    }

    void HierarchyImGui();
    void LoadObjectImGui();
    void InspectorImGui();

    void ContainObject();
    void EditTransform(const float *cameraView, float *cameraProjection, float* matrix);
    void ObjectLoader(int index);
    void SaveObjInfo2File();

    void MatChangeDX2Float(OUT float * m16, IN D3DXMATRIXA16 * mat);
    void MatChangeFloat2DX(OUT D3DXMATRIXA16 * mat, IN float * m16);
};
