#pragma once
#include "Components/Component.h"
#include "Engine.h"

class EnemyComponent : public nc::Component {

public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<EnemyComponent>(*this); }

	virtual void Update() override;

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	float speed{ 0 };
};
