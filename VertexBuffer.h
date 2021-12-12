#pragma once
#include "Bindable.h"
#include "GraphicsThrowMacros.h"

struct Vertex;

class VertexBuffer : public Bindable {
public:
	VertexBuffer(Graphics& gfx, const std::vector<Vertex>& vertices);
	void Bind(Graphics& gfx) noexcept override;
protected:
	UINT stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
};
