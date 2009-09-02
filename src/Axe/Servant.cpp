#	include "pch.hpp"

#	include <Axe/Servant.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Exception.hpp>

#	include <Axe/ArchiveInvocation.hpp>


#	include <Axe/ConnectionCache.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Servant::Servant()
		: m_servantId(-1)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::setServantId( std::size_t _servantId )
	{
		m_servantId = _servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Servant::getServantId() const
	{
		return m_servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::setHost( const HostPtr & _host )
	{
		m_host = _host;
	}
	//////////////////////////////////////////////////////////////////////////
	const HostPtr & Servant::getHost() const
	{
		return m_host;
	}
	//////////////////////////////////////////////////////////////////////////
	ProxyPtr Servant::getProxy( const ConnectionCachePtr & _connectionCache )
	{
		std::size_t hostId = m_host->getHostId();

		const ConnectionPtr & cn = _connectionCache->getConnection( hostId );

		return new Proxy( m_servantId, cn );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::write( ArchiveInvocation & _ar ) const
	{
		_ar << m_servantId;

		std::size_t hostId = m_host->getHostId();
		_ar << hostId;
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::writeExceptionFilter( ArchiveInvocation & _ar )
	{
		try
		{
			throw;
		}
		catch( const ::Axe::Exception & _ex )
		{
			const char * ch_what = _ex.what();
			std::string message = ( ch_what )?ch_what:std::string();
			::Axe::LocalException lex( message );
			_ar.writeSize( 1 );
			lex.write( _ar );
		}
		catch( const std::exception & _ex )
		{
			const char * ch_what = _ex.what();
			std::string message = ( ch_what )?ch_what:std::string();
			::Axe::StdException lex( message );
			_ar.writeSize( 2 );
			lex.write( _ar );
		}
		catch( ... )
		{
			::Axe::UnknownException uex;
			_ar.writeSize(0);
			uex.write( _ar );
		}
	}
}