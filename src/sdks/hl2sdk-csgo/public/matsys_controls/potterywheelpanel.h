//====== Copyright � 1996-2005, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#ifndef POTTERYWHEELPANEL_H
#define POTTERYWHEELPANEL_H

#ifdef _WIN32
#pragma once
#endif


#include "vgui_controls/EditablePanel.h"
#include "materialsystem/materialsystemutil.h"
#include "mathlib/camera.h"


//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class IManipulator;
class CPotteryWheelManip;
class CBaseManipulator;
class CTransformManipulator;
class CRotationManipulator;
class CTranslationManipulator;
class CZoomManipulator;
class CDmxElement;

namespace vgui
{
	class IScheme;
}


//-----------------------------------------------------------------------------
// Pottery wheel Panel
//-----------------------------------------------------------------------------
class CPotteryWheelPanel : public vgui::EditablePanel
{
	DECLARE_CLASS_SIMPLE( CPotteryWheelPanel, vgui::EditablePanel );

public:
	// constructor, destructor
	CPotteryWheelPanel( vgui::Panel *pParent, const char *pName );
	virtual ~CPotteryWheelPanel();

	// Overriden methods of vgui::Panel
	virtual void Paint();

	virtual void OnKeyCodePressed ( vgui::KeyCode code );
	virtual void OnKeyCodeReleased( vgui::KeyCode code );
	virtual void OnMousePressed ( vgui::MouseCode code );
	virtual void OnMouseDoublePressed( vgui::MouseCode code );
	virtual void OnMouseReleased( vgui::MouseCode code );
	virtual void OnCursorMoved( int x, int y );
	virtual void OnMouseWheeled( int delta );
	virtual void OnTick();

	virtual void OnMouseCaptureLost();

	// Sets the camera to look at the the thing we're spinning around
	void LookAt( const Vector &vecCenter, float flRadius );
	void LookAt( float flRadius );

	void ComputePanelPosition( const Vector &vecPosition, Vector2D *pPanelPos );

	void SetBackgroundColor( int r, int g, int b );
	void SetBackgroundColor( const Color& c );
	const Color& GetBackgroundColor() const;
	void SetGridColor( int r, int g, int b );

	// Light probe
	void SetLightProbe( CDmxElement *pLightProbe );

	// Camera.
	int	 GetCameraFOV( void );
	void SetCameraFOV( float flFOV );
	void SetCameraPositionAndAngles( const Vector &vecPos, const QAngle &angDir );
	void SetCameraOffset( const Vector &vecOffset );
	void ResetCameraPivot( void );
	void ComputeCameraTransform( matrix3x4_t *pWorldToCamera );
	void UpdateCameraTransform();
	virtual void ResetView();

	// Allow the parent to be notified of mouse actions
	void SetParentMouseNotify( bool bParentMouseNotify );



private:
	// Inherited classes must implement this
	virtual void OnPaint3D() = 0;

protected:



	enum ManipulationMode_t 
	{
		CAMERA_ROTATE,
		CAMERA_TRANSLATE,
		CAMERA_ZOOM,
		LIGHT_MODE,
	};

	virtual void EnterManipulationMode( ManipulationMode_t manipMode, bool bMouseCapture = true, vgui::MouseCode mouseCode = vgui::MouseCode( -1 ) );
	void Select();
	void AcceptManipulation( bool bReleaseMouseCapture = true );
	void CancelManipulation();
	void EnableMouseCapture( bool enable, vgui::MouseCode code = vgui::MouseCode( -1 ) );
	bool WarpMouse( int &x, int &y );
	
	void CreateDefaultLights();
	MaterialLightingState_t m_LightingState;	
	matrix3x4_t m_LightToWorld[MATERIAL_MAX_LIGHT_COUNT];

	
	IManipulator		*m_pCurrentManip;
	int m_nManipStartX, m_nManipStartY;

	bool HasLightProbe() const;
	ITexture *GetLightProbeCubemap( bool bHDR );
	void DrawGrid();
	CMaterialReference	m_Wireframe;

private:
	void SetupRenderState( int nDisplayWidth, int nDisplayHeight );
	void DestroyLights();

	CMaterialReference m_LightProbeBackground;
	CMaterialReference m_LightProbeHDRBackground;
	CTextureReference m_LightProbeCubemap;
	CTextureReference m_LightProbeHDRCubemap;

	Camera_t m_Camera;
	matrix3x4_t m_CameraPivot;

	Color m_ClearColor;
	Color m_GridColor;

	Vector					m_vecCameraOffset;
	CRotationManipulator	*m_pCameraRotate;
	CTranslationManipulator	*m_pCameraTranslate;
	CZoomManipulator		*m_pCameraZoom;
	CPotteryWheelManip		*m_pLightManip;
	vgui::MouseCode			m_nCaptureMouseCode;

	int m_xoffset, m_yoffset;

	bool	m_bHasLightProbe : 1;
	bool    m_bParentMouseNotify : 1;

	CPanelAnimationVar( bool, m_bUseParentBG, "useparentbg", "0" );
};


#endif // SIMPLEPOTTERYWHEELPANEL_H
