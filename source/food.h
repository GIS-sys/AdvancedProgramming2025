#pragma once

class IFood
{

public:
    virtual void on_consume(GameObjectPtr consumer) = 0;
};