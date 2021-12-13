#pragma once
#include "Renderer.h"
#include "ConstantBuffer.h"

class CameraRenderer : public Renderer {
public:
	CameraRenderer(Actor* const& actor);

	void SetViewport() const noexcept;
protected:
	virtual void LoadConstantBuffers();
private:
	struct CameraCbuf {
		Vector3 pos;
		float padding;
	};

	mutable CameraCbuf cbData;
	mutable PixelConstantBuffer<CameraCbuf> cbuf;
};

