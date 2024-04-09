
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Step2.h"
#include "ChildView.h"
#include "CThicknessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
    m_wood.LoadFile(L"textures/plank01.bmp");
    m_worldmap.LoadFile(L"textures/worldmap.bmp");
    m_marble1.LoadFile(L"textures/marble03.bmp");
    m_marble2.LoadFile(L"textures/marble10.bmp");
    m_spinAngle = 0;
    m_spinTimer = 0;
    m_camera.Set(20, 10, 50, 0, 0, 0, 0, 1, 0);
    m_scene = -1;
    m_bluegill.LoadFile(L"models/BLUEGILL.bmp");
    m_thickness = -0.75;


    CreateMesh();
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
    ON_WM_TIMER()
    ON_COMMAND(ID_STEP_SPIN, &CChildView::OnStepSpin)
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_STEP_MESH, &CChildView::OnStepMesh)
    ON_COMMAND(ID_STEP_THICKNESS, &CChildView::OnStepstuffThicknessDlg)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!COpenGLWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnGLDraw(CDC* pDC)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //
    // Set up the camera
    //

    int width, height;
    GetSize(width, height);
    m_camera.Apply(width, height);


    //
    // Some standard parameters
    //

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Cull backfacing polygons
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightpos[] = { 0.5, 2.0, 1.0, 0. };
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    glEnable(GL_LIGHT1);
    GLfloat light1pos[] = { 0.5, 2.0, -5.0, 0. };
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

    GLfloat lightDiffuse1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightSpecular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);

    // Draw a coordinate axis
    glColor3d(0., 1., 1.);

    glBegin(GL_LINES);
    glVertex3d(0., 0., 0.);
    glVertex3d(12., 0., 0.);
    glVertex3d(0., 0., 0.);
    glVertex3d(0., 12., 0.);
    glVertex3d(0., 0., 0.);
    glVertex3d(0., 0., 12.);
    glEnd();

    //
    // INSERT DRAWING CODE HERE
    //


    //
    // FRONT OF THE LETTER
    //
    glDisable(GL_CULL_FACE);

    GLdouble normal[] = { 1.0, 1.0, 1.0 };
    // Drawing the letter E
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_worldmap.TexName());
    glNormal3dv(normal);
    const GLdouble eColor[] = { 0.7, 0.0, 0.0 };

    // Translation amount on the x-axis
    const GLdouble translateX = 5.0;

    // Spine of the letter E translated to the right
    GLdouble spineTopLeft[] = { 0.0 + translateX, 0.0, 0.0 };
    GLdouble spineTopRight[] = { 0.5 + translateX, 0.0, 0.0 };
    GLdouble spineBottomRight[] = { 0.5 + translateX, 3.0, 0.0 };
    GLdouble spineBottomLeft[] = { 0.0 + translateX, 3.0, 0.0 };
    Quad(spineTopLeft, spineTopRight, spineBottomRight, spineBottomLeft);

    // Top bar of the letter E translated to the right
    GLdouble topBarTopLeft[] = { 0.5 + translateX, 2.5, 0.0 };
    GLdouble topBarTopRight[] = { 2.0 + translateX, 2.5, 0.0 };
    GLdouble topBarBottomRight[] = { 2.0 + translateX, 3.0, 0.0 };
    GLdouble topBarBottomLeft[] = { 0.5 + translateX, 3.0, 0.0 };
    Quad(topBarTopLeft, topBarTopRight, topBarBottomRight, topBarBottomLeft);

    // Middle bar of the letter E translated to the right
    GLdouble middleBarTopLeft[] = { 0.5 + translateX, 1.25, 0.0 };
    GLdouble middleBarTopRight[] = { 1.5 + translateX, 1.25, 0.0 };
    GLdouble middleBarBottomRight[] = { 1.5 + translateX, 1.75, 0.0 };
    GLdouble middleBarBottomLeft[] = { 0.5 + translateX, 1.75, 0.0 };
    Quad(middleBarTopLeft, middleBarTopRight, middleBarBottomRight, middleBarBottomLeft);

    // Bottom bar of the letter E translated to the right
    GLdouble bottomBarTopLeft[] = { 0.5 + translateX, 0.0, 0.0 };
    GLdouble bottomBarTopRight[] = { 2.0 + translateX, 0.0, 0.0 };
    GLdouble bottomBarBottomRight[] = { 2.0 + translateX, 0.5, 0.0 };
    GLdouble bottomBarBottomLeft[] = { 0.5 + translateX, 0.5, 0.0 };
    Quad(bottomBarTopLeft, bottomBarTopRight, bottomBarBottomRight, bottomBarBottomLeft);

    glDisable(GL_TEXTURE_2D);

    // 
    // BACK OF THE LETTER
    //

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_marble1.TexName());
    glNormal3dv(normal);

    // Translation amount on the x-axis
    //const GLdouble translateZ = -0.75;

    // Spine of the letter E translated to the right
    GLdouble spineTopLeftZ[] = { 0.0 + translateX, 0.0, m_thickness };
    GLdouble spineTopRightZ[] = { 0.5 + translateX, 0.0, m_thickness };
    GLdouble spineBottomRightZ[] = { 0.5 + translateX, 3.0, m_thickness };
    GLdouble spineBottomLeftZ[] = { 0.0 + translateX, 3.0, m_thickness };
    Quad(spineTopLeftZ, spineTopRightZ, spineBottomRightZ, spineBottomLeftZ);

    // Top bar of the letter E translated to the right
    GLdouble topBarTopLeftZ[] = { 0.5 + translateX, 2.5, m_thickness };
    GLdouble topBarTopRightZ[] = { 2.0 + translateX, 2.5, m_thickness };
    GLdouble topBarBottomRightZ[] = { 2.0 + translateX, 3.0, m_thickness };
    GLdouble topBarBottomLeftZ[] = { 0.5 + translateX, 3.0, m_thickness };
    Quad(topBarTopLeftZ, topBarTopRightZ, topBarBottomRightZ, topBarBottomLeftZ);

    // Middle bar of the letter E translated to the right
    GLdouble middleBarTopLeftZ[] = { 0.5 + translateX, 1.25, m_thickness };
    GLdouble middleBarTopRightZ[] = { 1.5 + translateX, 1.25, m_thickness };
    GLdouble middleBarBottomRightZ[] = { 1.5 + translateX, 1.75, m_thickness };
    GLdouble middleBarBottomLeftZ[] = { 0.5 + translateX, 1.75, m_thickness };
    Quad(middleBarTopLeftZ, middleBarTopRightZ, middleBarBottomRightZ, middleBarBottomLeftZ);

    // Bottom bar of the letter E translated to the right
    GLdouble bottomBarTopLeftZ[] = { 0.5 + translateX, 0.0, m_thickness };
    GLdouble bottomBarTopRightZ[] = { 2.0 + translateX, 0.0, m_thickness };
    GLdouble bottomBarBottomRightZ[] = { 2.0 + translateX, 0.5, m_thickness };
    GLdouble bottomBarBottomLeftZ[] = { 0.5 + translateX, 0.5, m_thickness };
    Quad(bottomBarTopLeftZ, bottomBarTopRightZ, bottomBarBottomRightZ, bottomBarBottomLeftZ);

    glDisable(GL_TEXTURE_2D);

    //
    // CONNECTING THE FRONT TO THE BACK
    //
    GLdouble spineSideNormal[] = { 1.0, 1.0, 1.0 }; 
    glNormal3dv(spineSideNormal);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_marble2.TexName());

    Quad(topBarBottomLeft, topBarBottomLeftZ, topBarBottomRightZ, topBarBottomRight);
    Quad(bottomBarTopLeft, bottomBarTopLeftZ, bottomBarTopRightZ, bottomBarTopRight);
    Quad(spineTopLeft, spineTopLeftZ, spineTopRightZ, spineTopRight);
    Quad(spineBottomLeft, spineBottomLeftZ, spineBottomRightZ, spineBottomRight); 
    Quad(spineTopLeft, spineTopLeftZ, spineBottomLeftZ, spineBottomLeft);
    Quad(topBarTopLeft, topBarTopLeftZ, topBarTopRightZ, topBarTopRight);
    Quad(topBarTopRight, topBarTopRightZ, topBarBottomRightZ, topBarBottomRight);
    Quad(middleBarTopRight, middleBarTopRightZ, middleBarBottomRightZ, middleBarBottomRight);
    Quad(bottomBarTopRight, bottomBarTopRightZ, bottomBarBottomRightZ, bottomBarBottomRight);
    Quad(spineTopRight, spineTopRightZ, spineBottomRightZ, spineBottomRight);
    Quad(topBarTopLeft, topBarTopLeftZ, topBarBottomLeftZ, topBarBottomLeft);
    Quad(topBarTopRight, topBarTopRightZ, topBarBottomRightZ, topBarBottomRight);
    Quad(middleBarTopLeft, middleBarTopLeftZ, middleBarBottomLeftZ, middleBarBottomLeft);
    Quad(middleBarTopRight, middleBarTopRightZ, middleBarBottomRightZ, middleBarBottomRight);
    Quad(bottomBarTopLeft, bottomBarTopLeftZ, bottomBarBottomLeftZ, bottomBarBottomLeft);
    Quad(bottomBarTopRight, bottomBarTopRightZ, bottomBarBottomRightZ, bottomBarBottomRight);
    Quad(topBarTopLeft, topBarTopRight, topBarTopRightZ, topBarTopLeftZ);
    Quad(bottomBarBottomLeft, bottomBarBottomRight, bottomBarBottomRightZ, bottomBarBottomLeftZ);
    Quad(middleBarTopLeft, middleBarTopRight, middleBarTopRightZ, middleBarTopLeftZ);
    Quad(middleBarBottomLeft, middleBarBottomRight, middleBarBottomRightZ, middleBarBottomLeftZ);

    glDisable(GL_TEXTURE_2D);

    const double RED[] = { 0.7, 0.0, 0.0 };

    switch (m_scene) {
        case ID_STEP_MESH:
            glPushMatrix();
            glRotated(m_spinAngle / 3, 0, 1, 0);

            glPushMatrix();
            glTranslated(0, 4, 0);
            m_mesh.Draw();
            glPopMatrix();

            m_surface.Draw();
            glPopMatrix();

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glBindTexture(GL_TEXTURE_2D, m_bluegill.TexName());
            //Rotate the Fish
            glTranslated(0, 4, 0);
            glRotated(-90, 1, 0, 0);

            //Draw the fish
            m_fish.Draw();

            glDisable(GL_TEXTURE_2D);
            glPopMatrix();

            break;
        default:
            glPushMatrix();
            glTranslated(1.5, 1.5, 1.5);
            glRotated(m_spinAngle, 0., 0., 1.);
            glTranslated(-1.5, -1.5, -1.5);
            Box(3., 3., 3., RED);
            glPopMatrix();
    }
 
}

//
//        Name : Quad()
// Description : Inline function for drawing 
//               a quadralateral.
//
inline void CChildView::Quad(GLdouble* v1, GLdouble* v2, GLdouble* v3, GLdouble* v4)
{
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3dv(v1);
    glTexCoord2f(1, 0);
    glVertex3dv(v2);
    glTexCoord2f(1, 1);
    glVertex3dv(v3);
    glTexCoord2f(0, 1);
    glVertex3dv(v4);
    glEnd();
}

//
//        Name : CChildView::Box()
// Description : Draw an arbitrary size box. p_x, 
//               p_y, an p_z are the height of
//               the box. We will use this 
//               as a common primitive.
//      Origin : The back corner is at 0, 0, 0, and
//               the box is entirely in the
//               positive octant.
//
void CChildView::Box(GLdouble p_x, GLdouble p_y, GLdouble p_z, const GLdouble* p_color)
{
    //GLfloat msugreen[] = { 0.f, .47f, .2f, 1.f };
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, msugreen);

    GLdouble a[] = { 0., 0., p_z };
    GLdouble b[] = { p_x, 0., p_z };
    GLdouble c[] = { p_x, p_y, p_z };
    GLdouble d[] = { 0., p_y, p_z };
    GLdouble e[] = { 0., 0., 0. };
    GLdouble f[] = { p_x, 0., 0. };
    GLdouble g[] = { p_x, p_y, 0. };
    GLdouble h[] = { 0., p_y, 0. };

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, m_wood.TexName());

    glNormal3d(0., 0., 1.);
    Quad(a, b, c, d); // Front

    glNormal3d(1., 0., 0.);
    Quad(c, b, f, g); // Right

    glNormal3d(0., 0., -1.);
    Quad(h, g, f, e); // Back

    glNormal3d(-1., 0., 0.);
    Quad(d, h, e, a); // Left

    glNormal3d(0., 1., 0.);
    Quad(d, c, g, h); // Top

    glNormal3d(0., -1., 0.);
    Quad(e, f, b, a); // Bottom

    glDisable(GL_TEXTURE_2D);
    
}




void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    m_spinAngle += 5;
    Invalidate();

    COpenGLWnd::OnTimer(nIDEvent);
}


void CChildView::OnStepSpin()
{
    // TODO: Add your command handler code here
    if (m_spinTimer == 0)
    {
        // Create the timer
        m_spinTimer = SetTimer(1, 30, NULL);
    }
    else
    {
        // Destroy the timer
        KillTimer(m_spinTimer);
        m_spinTimer = 0;
    }
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_camera.MouseDown(point.x, point.y);

    COpenGLWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_camera.MouseMove(point.x, point.y, nFlags))
        Invalidate();

    COpenGLWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
    m_camera.MouseDown(point.x, point.y, 2);

    COpenGLWnd::OnRButtonDown(nFlags, point);
}

void CChildView::OnStepMesh()
{
    	m_scene = ID_STEP_MESH;
	Invalidate();
}

void CChildView::CreateMesh()
{
    double v[8][4] = { {0, 0, 2, 1}, {2, 0, 2, 1}, {2, 2, 2, 1}, {0, 2, 2, 1},
    {0, 0, 0, 1}, {2, 0, 0, 1}, {2, 2, 0, 1}, {0, 2, 0, 1} };
    double n[6][4] = { {0, 0, 1, 0}, {1, 0, 0, 0}, {0, 0, -1, 0},
    {-1, 0, 0, 0}, {0, 1, 0, 0}, {0, -1, 0, 0} };

    for (int i = 0; i < 8; i++)
        m_mesh.AddVertex(v[i]);

    for (int i = 0; i < 6; i++)
        m_mesh.AddNormal(n[i]);

    m_mesh.AddFlatQuad(0, 1, 2, 3, 0);
    m_mesh.AddFlatQuad(1, 5, 6, 2, 1);
    m_mesh.AddFlatQuad(5, 4, 7, 6, 2);
    m_mesh.AddFlatQuad(4, 0, 3, 7, 3);
    m_mesh.AddFlatQuad(3, 2, 6, 7, 4);
    m_mesh.AddFlatQuad(0, 4, 5, 1, 5);

    //
    // Create a surface
    //

    double wid = 20;        // 20 units wide
    double dep = 20;        // 20 units deep
    int nW = 15;            // Number of quads across
    int nD = 15;            // Number of quads deep
    const double PI = 3.141592653;

    // Create the vertices and -temporary- normals
    // Note that the surface is nW+1 by nD+1 vertices
    for (int j = 0; j <= nD; j++)
    {
        for (int i = 0; i <= nW; i++)
        {
            double x = double(i) / double(nW) * wid - wid / 2;
            double z = double(j) / double(nD) * dep - dep / 2;
            double y = sin(double(i) / double(nW) * 4 * PI) +
                sin(double(j) / double(nD) * 3 * PI);

            CGrVector normal(-4 * PI / wid * cos(double(i) / double(nW) * 4 * PI),
                1., -3 * PI / dep * cos(double(j) / double(nD) * 3 * PI));
            normal.Normalize();


            m_surface.AddVertex(CGrVector(x, y, z, 1));
            m_surface.AddNormal(normal);
        }
    }

    // Create the quadrilaterals
    for (int j = 0; j < nD; j++)
    {
        for (int i = 0; i < nW; i++)
        {
            int a = j * (nW + 1) + i;
            int b = a + nW + 1;
            int c = b + 1;
            int d = a + 1;

            m_surface.AddQuad(a, b, c, d);
        }
    }
    m_fish.LoadOBJ("models\\fish4.obj");
    m_fish.SetTexture(&m_bluegill);
}

void CChildView::OnCreateE()
{
    // Define vertices for the letter E
    double topBar[][3] = { {0, 3, 0}, {2, 3, 0}, {2, 2.5, 0}, {0, 2.5, 0} };
    double middleBar[][3] = { {0, 1.75, 0}, {1.5, 1.75, 0}, {1.5, 1.25, 0}, {0, 1.25, 0} };
    double bottomBar[][3] = { {0, 0, 0}, {2, 0, 0}, {2, 0.5, 0}, {0, 0.5, 0} };
    double spine[][3] = { {0, 0, 0}, {0.5, 0, 0}, {0.5, 3, 0}, {0, 3, 0} };

    // Add the vertices to the mesh
    for (auto& vertex : topBar)
    {
        m_mesh.AddVertex(vertex);
    }
    for (auto& vertex : middleBar)
    {
        m_mesh.AddVertex(vertex);
    }
    for (auto& vertex : bottomBar)
    {
        m_mesh.AddVertex(vertex);
    }
    for (auto& vertex : spine)
    {
        m_mesh.AddVertex(vertex);
    }

    // Add quads to the mesh
    m_mesh.AddFlatQuad(0, 1, 2, 3, /* Normal Index */ 0);
    m_mesh.AddFlatQuad(4, 5, 6, 7, /* Normal Index */ 0);
    m_mesh.AddFlatQuad(8, 9, 10, 11, /* Normal Index */ 0);
    m_mesh.AddFlatQuad(12, 13, 14, 15, /* Normal Index */ 0);
}

void CChildView::OnDrawE()
{
    // Set color for the E
    glColor3d(1.0, 0.0, 0.0); // Red color

    // Draw each quad
    m_mesh.Draw();
}

void CChildView::OnStepstuffThicknessDlg() {

    CThicknessDlg dlg;

    dlg.m_thickness = m_thickness;


    if (dlg.DoModal() == IDOK)
    {
        m_thickness = dlg.m_thickness;

        Invalidate();
    }
}