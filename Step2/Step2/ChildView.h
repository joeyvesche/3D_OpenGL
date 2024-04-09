
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "graphics/OpenGLWnd.h"
#include "graphics/GrTexture.h"
#include "graphics/GrCamera.h"
#include "CMesh.h"


// CChildView window

class CChildView : public COpenGLWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:
	virtual void OnGLDraw(CDC* pDC);
	virtual void Box(GLdouble p_x, GLdouble p_y, GLdouble p_z, const GLdouble* p_color);
	static inline void Quad(GLdouble* v1, GLdouble* v2, GLdouble* v3, GLdouble* v4);
	virtual void OnStepstuffThicknessDlg();
// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
	CGrTexture m_wood;
	double m_spinAngle;
	UINT_PTR m_spinTimer;
	CGrCamera m_camera;
	CMesh m_mesh;
	int m_scene;
	CMesh m_surface;
	CMesh m_fish;
	CGrTexture m_bluegill;
	CGrTexture m_worldmap;
	CGrTexture m_marble1;
	CGrTexture m_marble2;
	double m_thickness;

	virtual void CreateMesh();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStepSpin();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStepMesh();
	afx_msg void OnCreateE();
	afx_msg void OnDrawE();
};

