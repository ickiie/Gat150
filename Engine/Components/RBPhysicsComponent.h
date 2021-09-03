#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

namespace nc {

	class RBPhysicsComponent : public PhysicsComponent {

	public:
		RBPhysicsComponent() = default;
		RBPhysicsComponent(const RBPhysicsComponent& other);
		~RBPhysicsComponent();
		std::unique_ptr<Object> Clone() const { return std::make_unique<RBPhysicsComponent>(*this); }

		void Update() override;
		void ApplyForce(const Vector2& force) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		PhysicsSystem::RigidBodyData data;
		b2Body* body{ nullptr };
	};
}