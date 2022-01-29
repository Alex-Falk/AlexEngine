#pragma once

#include <rpc.h>

class GameObject {

public:
	GameObject();

	UUID GetId();

protected:

private:

	UUID m_id;
};