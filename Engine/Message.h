#include <typeinfo>

namespace ae
{
	using MessageHash = size_t;

	class Message
	{
	public:
		Message() = default;

		MessageHash GetId();
	private:
	};
}