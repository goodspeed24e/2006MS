

#ifndef _StructDef_H_
#define _StructDef_H_


#define SCREEN_WIDTH	512	
#define SCREEN_HEIGHT	512
// struct of vertex
class vertex2D{
public:
	int x,y;
	vertex2D *link;
	vertex2D();

};

class sPolygon2D{
public:
	int num_verts;
	DWORD color;
	vertex2D *vlist;
};

class sPoint2D{
public:
	double h, v; 
};

class CUSTOMVERTEX4F{
public:
    FLOAT x, y, z, rhw; // The transformed position for the vertex.
    DWORD color;        // The vertex color.
//	CUSTOMVERTEX4F *link;
};
#define D3DFVF_CUSTOMVERTEX4F (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

// ---------------------------------------------------------------------------
// 自訂polygon物件
// ---------------------------------------------------------------------------
enum {
	OBJ_TYPE_SPHERE = 0,
	OBJ_TYPE_TRIANGLE,
};

typedef struct{
	float	COLOR_AMB[4];	// ambient light
	float	COLOR_DIF[4];	// diffuse light
	float	COLOR_SPE[4];	// specular light
	float	speq_power;		// specular weight
	float   reflection;     // surface reflection ratio
	float   refraction;		// surface refraction ratio
	float   diffuse;		// diffuse reflection ratio
}Material;

// ---------------------------------------------------------------------------
typedef struct{
	int type;

	Material material;
	
	struct{
		float x0[3];	// vertex 1
		float x1[3];	// vertex 2
		float x2[3];	// vertex 3
	} triangle;
	struct {
		float center[3];// x,y,z 中心
		float radius;	// 半徑
	} sphere;

}OBJ_DATA;

// ---------------------------------------------------------------------------
class CObject
{
public:
	enum {
		INFINTY_DIST = 10000,	//'無限大'的程度的距離��
	};
	int m_type;					// 物件型態
	Material m_material;		// 物件的material

	void Init(OBJ_DATA *pData);
	float IsAcross(D3DXVECTOR4 *n, D3DXVECTOR4 *p, const D3DXVECTOR4 *x, const D3DXVECTOR4 *v){return INFINTY_DIST;}
	D3DXVECTOR3 *GetColor(D3DXVECTOR3 *dest, float LN, float HN );
};
// ---------------------------------------------------------------------------
// 球
// ---------------------------------------------------------------------------
class CSphere : public CObject
{
private:
	D3DXVECTOR4 center;	// 中心位置
	float radius_sq;	// 半徑值
public:
	CSphere();

	void Init(OBJ_DATA *pData);
	float IsAcross(D3DXVECTOR4 *n, D3DXVECTOR4 *p, const D3DXVECTOR4 *x, const D3DXVECTOR4 *v);
};

// ---------------------------------------------------------------------------
// 三角形
// ---------------------------------------------------------------------------
class CTriangle : public CObject
{
private:
	D3DXVECTOR4 pos[3];			// 頂點座標
	D3DXVECTOR4 normal;			// 法向量
public:
	CTriangle();

	void Init(OBJ_DATA *pData);
	float IsAcross(D3DXVECTOR4 *n, D3DXVECTOR4 *p, const D3DXVECTOR4 *x, const D3DXVECTOR4 *v);
};

#endif