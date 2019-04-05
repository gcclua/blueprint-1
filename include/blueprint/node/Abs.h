#pragma once

#include "blueprint/Node.h"
#include "blueprint/Pin.h"

namespace bp
{
namespace node
{

class Abs : public Node
{
public:
    Abs()
        : Node("Abs")
    {
        AddPin(std::make_shared<Pin>(true, 0, PIN_ANY_VAR, "In", *this));
        AddPin(std::make_shared<Pin>(false, 0, PIN_ANY_VAR, "Out", *this));
        Layout();
    }

    RTTR_ENABLE(Node)

}; // Abs

}
}