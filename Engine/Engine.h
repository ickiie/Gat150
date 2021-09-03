#pragma once

#define REGISTER_CLASS(CLASS) nc::ObjectFactory::Instance().Register<CLASS>(#CLASS);


//core
#include "Core/Utilities.h"
#include "Core/FileSystem.h"
#include "Core/Timer.h"
#include "Core/Json.h"
#include "Core/Serializable.h"

//framework
#include "Framework/EventSystem.h"
#include "Framework/Singleton.h"
#include "Framework/Factory.h"

//math
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

// graphics
#include "Graphics/Renderer.h" 
#include "Graphics/Texture.h"
#include "Graphics/Font.h"
#include "Graphics/ParticleSystem.h"

// Physics System
#include "Physics/PhysicsSystem.h"

//audio
#include "Audio/AudioSystem.h"

//Input
#include "Input/InputSystem.h"

//Object
#include "Object/Actor.h"
#include "Object/Scene.h"
#include "Object/Tilemap.h"

//Components
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RBPhysicsComponent.h"
#include "Components/AudioComponent.h"
#include "Components/TextComponent.h"

//Resource
#include "Resource/ResourceSystem.h"

#include <vector>
#include <memory>
#include <algorithm>

namespace nc {

	using ObjectFactory = Singleton<Factory<std::string, Object>>;

	class Engine {

	public:
		void Startup();
		void Shutdown();

		void Update();
		void Draw(Renderer* renderer);

		template<typename T>
		T* Get();


	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get() {

		for (auto& system : systems) {

			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}

		return nullptr;
	}
}
