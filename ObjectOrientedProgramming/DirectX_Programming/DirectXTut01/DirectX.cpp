#include "DirectX.h"

DirectX::DirectX()
{
	m_d3d = NULL;
	m_d3dDevice = NULL;
}

DirectX::~DirectX()
{
	if( m_d3dDevice != NULL )
		m_d3dDevice = NULL;
	if( m_d3d != NULL )
		m_d3d = NULL;
}

void DirectX::Init(HWND hWnd)
{
	m_d3d = Direct3DCreate9( D3D_SDK_VERSION );

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;

	m_d3d->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
		&d3dpp,
		&m_d3dDevice );
}

void DirectX::Render(void)
{
	m_d3dDevice->Clear(
		0, NULL, D3DCLEAR_TARGET,
		D3DCOLOR_XRGB( 95, 140, 255 ),
		1.0f, 0 );

	m_d3dDevice->BeginScene();

	// Drawing code here

	m_d3dDevice->EndScene();

	m_d3dDevice->Present(
		NULL, NULL, NULL, NULL );
}

void DirectX::CleanDirectX(void)
{
	m_d3dDevice->Release();
	m_d3d->Release();
}