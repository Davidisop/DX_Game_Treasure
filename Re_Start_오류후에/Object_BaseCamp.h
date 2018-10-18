#include "PipeLineSetup.h"

class Object_BaseCamp
{
public:
	PipeLineSetup  PipeLineSetup;
	D3DVECTOR      m_vCenter; // x,y,z
public:
	virtual bool	Init() { return true;}
	virtual bool	Frame(float fGameTimer, float fFps)	{return true;}
	virtual bool	PreRender(ID3D11DeviceContext* pContext)	{ PipeLineSetup.PreRender(pContext);	return true;}
	virtual bool	Render(ID3D11DeviceContext* pContext) { PipeLineSetup.Render(pContext); return true;}
	virtual bool	PostRender(ID3D11DeviceContext* pContext) { PipeLineSetup.PostRender(pContext); return true;}
	virtual bool	Release() { return true;}
public:
	Object_BaseCamp() {}
	virtual ~Object_BaseCamp() {}
};

