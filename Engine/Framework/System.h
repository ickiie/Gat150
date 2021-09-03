#pragma once


namespace nc {

	class System {

	public:
		virtual void Startup() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;
	};

	class GraphicsSystem : public System {

	public:
		virtual void Draw(class Renderer* renderer) = 0;
	};
}