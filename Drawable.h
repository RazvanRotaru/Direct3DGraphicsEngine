#pragma once
#include "Graphics.h"
#include "Math.h"
#include <memory>

class Bindable;
class IndexBuffer;

class Drawable {
	template<class T>
	friend class DrawableBase;
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual ~Drawable() = default;

	void Draw(Graphics& gfx) const noexcept(!IS_DEBUG);

	virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;
	virtual void Update(float dt) noexcept = 0;
	virtual void Update(float dx, float dy) noexcept = 0;
protected:
	template<class T>
	T* QueryBindable() noexcept {
		for (auto& pb : binds) {
			if (auto pt = dynamic_cast<T*>(pb.get())) {
				return pt;
			}
		}
		return nullptr;
	}
	void AddBind(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG);
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> ibuf) noexcept(!IS_DEBUG);
private:
	virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept = 0;
private:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> binds;
};