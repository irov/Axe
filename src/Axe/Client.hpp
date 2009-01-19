#	pragma once

namespace Axe
{
	class Client
	{
	public:
		virtual void onConnect( std::size_t _id ) = 0;
	};
}
