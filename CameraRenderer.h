#pragma once
#include "Renderer.h"
#include "ConstantBuffer.h"

class CameraRenderer : public Renderer {
public:
	CameraRenderer(Actor* const& actor);

	void SetViewport() const noexcept;
protected:
	virtual void LoadConstantBuffers() override;
private:
	struct CameraCbuf {
		alignas(16) Vector3 pos;
	};

	mutable CameraCbuf cbData;
	mutable PixelConstantBuffer<CameraCbuf> cbuf;
};

