#	include "pch.hpp"

#	include <Axe/Servant.hpp>
#	include <Axe/Session.hpp>
#	include <Axe/Bellhop.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Exception.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ConnectionCache.hpp>
#	include <Axe/ProxyAdapterProvider.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Servant::Servant()
		: m_servantId(-1)
		, m_adapterId(-1)
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
	void Servant::setAdapterId( std::size_t _adapterId )
	{
		m_adapterId = _adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Servant::getAdapterId() const
	{
		return m_adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	ProxyPtr Servant::getProxy( const ConnectionCachePtr & _connectionCache )
	{
		const ProxyAdapterProviderPtr & provider = _connectionCache->getProxyAdapterProvider( m_servantId, m_adapterId );

		return new Proxy( m_servantId, provider );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::dispatchMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session )
	{
		try
		{
			this->callMethod( _methodId, _requestId, _archive, _session );
		}
		catch( const ProtocolCallException & _ex )
		{
			this->responseException( _methodId, _requestId, _session, _ex );
		}
		catch( ... )
		{
			ArchiveInvocation & aw = _session->beginException( _requestId );

			writeExceptionFilter( aw );

			_session->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	class Bellhop_Servant_destroy
		: public Bellhop
	{
	public:
		Bellhop_Servant_destroy( std::size_t _requestId, const SessionPtr & _session, const ServantPtr & _servant )
			: Bellhop(_requestId, _session)
			, m_servant(_servant)
		{
		}

	public:
		void response()
		{
			Axe::ArchiveInvocation & ar = this->beginResponse();
			this->process();
		}

		void throw_exception( const Axe::Exception & _ex )
		{
			Axe::ArchiveInvocation & ar = this->beginException();
			writeExceptionFilter( ar );
			this->process();
		}

	protected:
		ServantPtr m_servant;
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant::destroy_async( const Bellhop_Servant_destroyPtr & _cb )
	{
		_cb->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session )
	{
		std::size_t internalMethodId = 0;
		_archive.readSize( internalMethodId );

		switch( internalMethodId )
		{
		case 1:
			{
				Bellhop_Servant_destroyPtr bellhop = new Bellhop_Servant_destroy( _requestId, _session, this );
				this->destroy_async( bellhop );
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::restore( ArchiveDispatcher & _ar )
	{
		this->_restore(_ar);
		this->onRestore();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::evict( ArchiveInvocation & _aw )
	{
		this->onEvict();
		this->_evict(_aw);
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::_restore( ArchiveDispatcher & _ar )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::_evict( ArchiveInvocation & _aw )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::onRestore()
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::onEvict()
	{
		//Empty
	}
}