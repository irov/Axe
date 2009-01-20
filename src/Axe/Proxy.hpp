#	pragma once

#	include "Shared.hpp"

#	include "Connection.hpp"

namespace Axe
{
	typedef AxeHandle<class Response> ResponsePtr;
	//typedef AxeHandle<class Connection> ConnectionPtr;

	class ArchiveWrite;

	class Proxy
		: public Shared
	{
	public:
		Proxy( std::size_t _servantId, const ConnectionPtr & _connection );

	public:
		ArchiveWrite & beginMessage( std::size_t _methodId, const ResponsePtr & _response );
		void process();

	public:
		std::size_t getServantId() const;

	protected:
		std::size_t m_servantId;
		ConnectionPtr m_connection;
	};
}