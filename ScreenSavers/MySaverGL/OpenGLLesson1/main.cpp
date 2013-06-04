//greensquare.cpp is an open-source example
//screensaver by Rachel Grey, lemming@alum.mit.edu.
//Paste into an IDE to compile if desired.
//I haven't chosen to include the resource file,
//so you'd need to provide a description string
//and so forth.


#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <ScrnSave.h>
#include <CommCtrl.h>

#include "resource.h"

//get rid of these warnings:
//truncation from const double to float
//conversion from double to float
#pragma warning(disable: 4305 4312 4244 4996)
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

#ifdef _UNICODE
#pragma comment(lib, "ScrnSavw.lib")
#else
#pragma comment(lib, "ScrnSave.lib")
#endif

#pragma comment(lib, "ComCtl32.lib")

//Define a Windows timer

#define TIMER 1



//These forward declarations are just for readability,
//so the big three functions can come first 

AUX_RGBImageRec *LoadBMP(char* Filename);
int LoadGLTextures();
void InitGL(HWND hWnd, HDC & hDC, HGLRC & hRC);
void CloseGL(HWND hWnd, HDC hDC, HGLRC hRC);
void GetConfig();               
void WriteConfig(HWND hDlg);
void SetupAnimation(int Width, int Height);
void CleanupAnimation();
void OnTimer(HDC hDC);

GLuint texture[1];

GLsizei Width, Height; //globals for size of screen
static HDC hDc;//global

//////////////////////////////////////////////////
////   INFRASTRUCTURE -- THE THREE FUNCTIONS   ///
//////////////////////////////////////////////////


// Screen Saver Procedure
LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message, 
							   WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	static HGLRC hRC;
	static RECT rect;

	switch ( message ) {

  case WM_CREATE: 
	  // get window dimensions
	  GetClientRect( hWnd, &rect );
	  Width = rect.right;         
	  Height = rect.bottom;

	  //get configuration from registry
	  GetConfig();

	  //get DeviceContext and put to global var
	  hDc = GetDC(hWnd);

	  // setup OpenGL, then animation
	  InitGL( hWnd, hDC, hRC );
	  SetupAnimation(Width, Height);

	  //set timer to tick every 10 ms
	  SetTimer( hWnd, TIMER, 10, NULL );
	  return 0;

  case WM_DESTROY:
	  KillTimer( hWnd, TIMER );
	  CleanupAnimation();
	  CloseGL( hWnd, hDC, hRC );
	  return 0;

  case WM_TIMER:
	  OnTimer(hDC);       //animate!      
	  return 0;                           

	}

	return DefScreenSaverProc( 
		hWnd, message, wParam, lParam );

}

bool bTumble = true;


BOOL WINAPI
ScreenSaverConfigureDialog(HWND hDlg, UINT message, 
						   WPARAM wParam, LPARAM lParam)
{

	//InitCommonControls();  
	//would need this for slider bars or other common controls

	//  HWND aCheck;

	switch ( message ) 
	{

	case WM_INITDIALOG:
		//                LoadString(hMainInstance, IDS_DESCRIPTION, szAppName, 40);

		/*                GetConfig();

		aCheck = GetDlgItem( hDlg, IDC_TUMBLE );
		SendMessage( aCheck, BM_SETCHECK, 
		bTumble ? BST_CHECKED : BST_UNCHECKED, 0 );
		*/
		return TRUE;

	case WM_COMMAND:
		switch( LOWORD( wParam ) ) 
		{ 

			/* case IDC_TUMBLE:
			bTumble = (IsDlgButtonChecked( hDlg, IDC_TUMBLE ) == BST_CHECKED);
			return TRUE;
			*/
			//cases for other controls would go here

		case IDOK:
			//    WriteConfig(hDlg);      //get info from controls
			EndDialog( hDlg, LOWORD( wParam ) == IDOK ); 
			return TRUE; 

		case IDCANCEL: 
			EndDialog( hDlg, LOWORD( wParam ) == IDOK ); 
			return TRUE;   
		}

	}     //end command switch

	return FALSE; 
}



// needed for SCRNSAVE.LIB
BOOL WINAPI RegisterDialogClasses(HANDLE hInst)
{
	return TRUE;
}


/////////////////////////////////////////////////
////   INFRASTRUCTURE ENDS, SPECIFICS BEGIN   ///
////                                          ///
////    In a more complex scr, I'd put all    ///
////     the following into other files.      ///
/////////////////////////////////////////////////


// Initialize OpenGL
static void InitGL(HWND hWnd, HDC & hDC, HGLRC & hRC)
{

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory( &pfd, sizeof pfd );
	pfd.nSize = sizeof pfd;
	pfd.nVersion = 1;
	//pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL; //blaine's
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;

	hDC = GetDC( hWnd );

	int i = ChoosePixelFormat( hDC, &pfd );  
	SetPixelFormat( hDC, i, &pfd );

	hRC = wglCreateContext( hDC );
	wglMakeCurrent( hDC, hRC );

}

// Shut down OpenGL
static void CloseGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( hRC );

	ReleaseDC( hWnd, hDC );
}

GLfloat x1=0.0,y1=0.0,x2=75.0,y2=75.0,xstep=1.0,ystep=1.0;

void SetupAnimation(int Width, int Height)
{
	//window resizing stuff
	glViewport(0, 0, (GLsizei) Width, (GLsizei) Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-300, 300, -240, 240, 25, 75);  
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//camera xyz, the xyz to look at, and the up vector (+y is up)

	if(!LoadGLTextures())
	{
		return;
	}

	glEnable(GL_TEXTURE_2D);

	//background
	glClearColor(0.0, 0.0, 1.0, 0.0); //0.0s is black


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	glShadeModel(GL_SMOOTH); 

	//no need to initialize any objects
	//but this is where I'd do it

	glColor3f(1.0f, 1.0f, 1.0f); //green
}

//static GLfloat spin=0;   //a global to keep track of the square's spinning

void OnTimer(HDC hDC) //increment and display
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(x1, y2);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(x2, y2);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(x2, y1);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(x1, y1);
	glEnd();
	glFlush();
	SwapBuffers(hDC);

    // Check bounds.  This is in case the window is made
    // smaller and the rectangle is outside the new
    // clipping volume
	if(x1 > Width || x1 < 0)
	{
		x1 += xstep;
	}
	else if(x1 > Height || x1 < 0)
	{
		x1 -= xstep;
	}
	else if(x2 > Width || x2 < 0)
	{
		x2 -= xstep;
	}
	else if(x2 > Height || x2 < 0)
	{
		x2 += xstep;
	}

	if(y1 > Height || y1 < 0)
	{
		y1 += ystep;
	}
	else if(y1 > Width || y1 < 0)
	{
		y1 -= ystep;
	}
	else if(y2 > Height || y2 < 0)
	{
		y2 += ystep;
	}
	else if(y2 > Width || y2 < 0)
	{
		y2 -= ystep;
	}

    // Actually move the square
    x1 += xstep;
	x2 += xstep;
    y1 += ystep;
	y2 += ystep;
}

void CleanupAnimation()
{
	//didn't create any objects, so no need to clean them up
	delete [] &texture;
}



/////////   REGISTRY ACCESS FUNCTIONS     ///////////

void GetConfig()
{

	HKEY key;
	//DWORD lpdw;

	if (RegOpenKeyEx( HKEY_CURRENT_USER,
		L"Software\\GreenSquare", //lpctstr
		0,                      //reserved
		KEY_QUERY_VALUE,
		&key) == ERROR_SUCCESS) 
	{
		DWORD dsize = sizeof(bTumble);
		DWORD dwtype =  0;

		RegQueryValueEx(key,L"Tumble", NULL, &dwtype, 
			(BYTE*)&bTumble, &dsize);


		//Finished with key
		RegCloseKey(key);
	}
	else //key isn't there yet--set defaults
	{
		bTumble = true;
	}

}

void WriteConfig(HWND hDlg)
{

	HKEY key;
	DWORD lpdw;

	if (RegCreateKeyEx( HKEY_CURRENT_USER,
		L"Software\\GreenSquare", //lpctstr
		0,                      //reserved
		L"",                     //ptr to null-term string specifying the object type of this key
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		NULL,
		&key,
		&lpdw) == ERROR_SUCCESS)

	{
		RegSetValueEx(key,L"Tumble", 0, REG_DWORD, 
			(BYTE*)&bTumble, sizeof(bTumble));

		//Finished with keys
		RegCloseKey(key);
	}

}

AUX_RGBImageRec *LoadBMP(char* Filename)
{
	FILE *File = NULL;

	if(!Filename)
		return NULL;

	File=fopen(Filename, "r");

	if(File)
	{
		fclose(File);
		return auxDIBImageLoadA(Filename);
	}

	return NULL;
}

int LoadGLTextures()
{
	int Status=FALSE;
	LPVOID lpBits = NULL;

	AUX_RGBImageRec *TextureImage[1];
	memset(TextureImage, 0, sizeof(void*)*1);

	if(TextureImage[0] = LoadBMP("texture.bmp"))
	{
		Status=TRUE;
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		// Generate the Texture
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	if(TextureImage[0])
	{
		if(TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}
		free(TextureImage[0]);
	}

	return Status;
}
