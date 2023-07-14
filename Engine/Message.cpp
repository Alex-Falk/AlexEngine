#include "Message.h"

ae::MessageHash ae::Message::GetId()
{
	return typeid(*this).hash_code();
}
