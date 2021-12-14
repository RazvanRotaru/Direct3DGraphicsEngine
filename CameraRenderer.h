#pragma once
#include "Renderer.h"
#include "ConstantBuffer.h"

class CameraRenderer : public Renderer {
public:
	CameraRenderer(Actor* const& actor);

	void SetViewport() const noexcept;
	void SetMesh(Mesh* const& mesh) override {}
private:
	struct CameraCbuf {
		Vector3 pos;
		float padding;
	};

	mutable CameraCbuf cbData;
	mutable PixelConstantBuffer<CameraCbuf> cbuf;
};

