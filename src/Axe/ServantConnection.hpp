#	pragma once

#	include <Axe/Invocation.hpp>

namespace Axe
{
	class ServantConnection
		: public Invocation
	{
	public:
		Connection( const std::string & _uniqueId );

	protected:
		ArchiveInvocation & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;

	protected:
		std::string m_uniqueId;
	};
}