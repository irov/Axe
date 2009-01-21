#	pragma once

#	include "Shared.hpp"

#	include "Connection.hpp"

namespace Axe
{
	typedef AxeHandle<class Response> ResponsePtr;

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
		const ConnectionPtr & getConnection() const;

	protected:
		std::size_t m_servantId;
		ConnectionPtr m_connection;
	};

	typedef AxeHandle<Proxy> ProxyPtr;

	template<class T>
	inline AxeHandle<T> uncheckedCast( const ProxyPtr & _proxy )
	{
		std::size_t servantId = _proxy->getServantId();
		const ConnectionPtr & connection = _proxy->getConnection();

		return new T( servantId, connection );
	}

	template<class T>
	AxeHandle<T> makeProxy( ArchiveWrite & ar )
	{
		std::size_t servantId;
		std::size_t endpointId;

		ar >> servantId;
		ar >> endpointId;

		const ConnectionPtr & connection = 
			this->getConnection( endpointId );

		return new T( servantId, connection );
	}


	void operator << ( ArchiveWrite & ar, const ProxyPtr & _value );	
}