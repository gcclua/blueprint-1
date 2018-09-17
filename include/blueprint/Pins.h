#pragma once

#include <painting2/BezierShape.h>
#include <painting2/Color.h>

#include <string>
#include <memory>

namespace bp
{

class Node;
class Connecting;

enum PinsType
{
	PINS_PORT = 0,

	// variable
	PINS_BOOLEAN,
	PINS_INTEGER,
	PINS_FLOAT,
	PINS_STRING,
	PINS_TEXT,
	PINS_VECTOR,
	PINS_ROTATOR,
	PINS_TRANSFORM,
	PINS_OBJECT,
};

class Pins
{
public:
	Pins(bool is_input, int pos, int type, const std::string& name, const Node& parent);
	~Pins();

	// for draw
	virtual std::string GetDesc() const { return m_name; }
	virtual const pt2::Color& GetColor() const;

	virtual bool CanTypeCast(int type) const;

	bool IsInput() const { return m_is_input; }
	int  GetPosIdx() const { return m_pos; }

	int  GetType() const { return m_type; }
	void SetType(int type) { m_type = type; }

	bool IsTypeStatic() const { return m_type_static; }
	void SetTypeStatic(bool is_static) { m_type_static = is_static; }

	auto& GetParent() const { return m_parent; }

	void AddConnecting(const std::shared_ptr<Connecting>& conn);
	void RemoveConnecting(const std::shared_ptr<Connecting>& conn);
	void ClearConnecting();

	auto& GetConnecting() const { return m_connecting; }

	auto& GetName() const { return m_name; }

private:
	// for parent
	bool m_is_input;
	int  m_pos;

	int m_type;
	bool m_type_static = false;	// disable type promote

	std::string m_name;

	const Node& m_parent;

	std::vector<std::shared_ptr<Connecting>> m_connecting;

}; // Pins

}