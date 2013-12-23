#ifndef DirectX_h
#define DirectX_h

#include <Windows.h>
#include <d3d9.h>

class DirectX
{
public:
	DirectX();
	virtual ~DirectX();

	//Main DirectX Functions
	void Init(HWND hWnd);
	void Render(void);
	void CleanDirectX(void);

private:
	LPDIRECT3D9 m_d3d;
	LPDIRECT3DDEVICE9 m_d3dDevice;
};

#endif