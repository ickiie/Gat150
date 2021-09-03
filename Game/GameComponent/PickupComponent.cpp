#include "PickupComponent.h"
#include "Engine.h"

using namespace nc;

PickupComponent::~PickupComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}

void PickupComponent::Create() {

	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PickupComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit", std::bind(&PickupComponent::OnCollisionExit, this, std::placeholders::_1), owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("coin", "audio/coin.wav");
}

void PickupComponent::Update()
{
	Vector2 force = Vector2::zero;

	PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
	assert(physicsComponent);

	physicsComponent->ApplyForce(force);

	SpriteAnimationComponent* spriteAnimationComponent = owner->GetComponent<SpriteAnimationComponent>();
	assert(spriteAnimationComponent);

	if (startLifetime == true) {

		lifetime -= owner->scene->engine->time.deltaTime;
		if (lifetime <= 0) {
			owner->destroy = true;
		}
	}
}

void PickupComponent::OnCollisionEnter(const nc::Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "player")) {

		owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");
		owner->destroy = true;

		Event event;
		event.name = "add_score";
		event.data = 1;

		owner->scene->engine->Get<EventSystem>()->Notify(event);
	}
	if (istring_compare(actor->tag, "ground")) {

		owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");

		startLifetime = true;
	}
}

void PickupComponent::OnCollisionExit(const nc::Event& event)
{
}

bool PickupComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PickupComponent::Read(const rapidjson::Value& value)
{
	return true;
}
