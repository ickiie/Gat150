#pragma once
#include "Components/Component.h"
#include "Framework/EventSystem.h"

class PlayerComponent : public nc::Component {

public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<PlayerComponent>(*this); }
	virtual ~PlayerComponent();

	void Create() override;
	virtual void Update() override;

	virtual void OnCollisionEnter(const nc::Event& event);
	virtual void OnCollisionExit(const nc::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	float speed{ 0 };
	float jump{ 0 };

private:
	std::list<nc::Actor*> contacts;
};
