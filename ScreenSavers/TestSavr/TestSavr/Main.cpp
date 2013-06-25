#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <scrnsave.h>
#include "resource.h"

//get rid of these warnings:
//truncation from const double to float
//conversion from double to float
#pragma warning(disable: 4305 4244) 


//Define a Windows timer

#define TIMER 1



//These forward declarations are just for readability,
//so the big three functions can come first 

void InitGL(HWND hWnd, HDC & hDC, HGLRC & hRC);
void CloseGL(HWND hWnd, HDC hDC, HGLRC hRC);
void GetConfig();               
void WriteConfig(HWND hDlg);
void SetupAnimation(int Width, int Height);
void CleanupAnimation();
void OnTimer(HDC hDC);


int Width, Height; //globals for size of screen


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
bool bColor = true;


BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT message, 
	WPARAM wParam, LPARAM lParam)
{

	//InitCommonControls();  
	//would need this for slider bars or other common controls

	HWND aCheck, bCheck;

	switch ( message ) 
	{

	case WM_INITDIALOG:
		LoadString(hMainInstance, IDS_DESCRIPTION, szAppName, 40);

		GetConfig();

		aCheck = GetDlgItem( hDlg, IDC_TUMBLE );
		SendMessage( aCheck, BM_SETCHECK, 
			bTumble ? BST_CHECKED : BST_UNCHECKED, 0 );

		bCheck = GetDlgItem( hDlg, IDC_COLOR );
		SendMessage( bCheck, BM_SETCHECK,
			bTumble ? BST_CHECKED : BST_UNCHECKED, 0 );

		return TRUE;

	case WM_COMMAND:
		switch( LOWORD( wParam ) ) 
		{ 

		case IDC_TUMBLE:
			bTumble = (IsDlgButtonChecked( hDlg, IDC_TUMBLE ) == BST_CHECKED);
			return TRUE;

		case IDC_COLOR:
			bColor = (IsDlgButtonChecked( hDlg, IDC_COLOR ) == BST_CHECKED);
			return TRUE;

		case IDOK:
			WriteConfig(hDlg);      //get info from controls
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

	//background
	glClearColor(0.0, 0.0, 0.0, 0.0); //0.0s is black


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	glShadeModel(GL_SMOOTH); 

	//no need to initialize any objects
	//but this is where I'd do it
}

static GLfloat spin=0;   //a global to keep track of the square's spinning


void OnTimer(HDC hDC) //increment and display
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	spin = spin + 1; 

	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);

	glPushMatrix();

	glTranslatef(150, 0, 0);

	if(bTumble)
		glRotatef(spin * -3.0, 0.0, 0.0, 1.0); 
	else
		glRotatef(spin * -1.0, 0.0, 0.0, 1.0);  

	//draw the square (rotated to be a diamond)

	float xvals[] = {-30.0, 0.0, 30.0, 0.0};
	float yvals[] = {0.0, -30.0, 0.0, 30.0};

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();

	if(bColor)
	{
		glColor3ub(rand()%255,rand()%255,rand()%255);
		glBegin(GL_POLYGON);
			for(int i=0;i<4;i++)
				glVertex2f(xvals[i], yvals[i]);
		glEnd();
	}
	else
	{
		glColor3i(25, 255, 25);
		glBegin(GL_POLYGON);
			for(int i=0;i<4;i++)
				glVertex2f(xvals[i],yvals[i]);
		glEnd();
	}

	glPopMatrix();
	glPopMatrix();

	glFlush();
	SwapBuffers(hDC);
	glPopMatrix();
}

void CleanupAnimation()
{
	//didn't create any objects, so no need to clean them up
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
		DWORD dsize2 = sizeof(bColor);
		DWORD dwtype =  0;

		RegQueryValueEx(key,L"Tumble", NULL, &dwtype, 
			(BYTE*)&bTumble, &dsize);

		RegQueryValueEx(key,L"Flashing", NULL, &dwtype,
			(BYTE*)&bColor, &dsize2);


		//Finished with key
		RegCloseKey(key);
	}
	else //key isn't there yet--set defaults
	{
		bTumble = true;
		bColor = true;
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

		RegSetValueEx(key,L"Flashing", 0, REG_DWORD,
			(BYTE*)&bColor, sizeof(bColor));

		//Finished with keys
		RegCloseKey(key);
	}

}
