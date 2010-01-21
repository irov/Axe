#	pragma once

#	include <Axe/Bellhop.hpp>
#	include <Axe/Servant.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Exception.hpp>

#	include <AxeProtocols/Common.hpp>

namespace Axe
{
	class ArchiveInvocation;
	class ArchiveDispatcher;
}

namespace AxeLibProtocol
{
	
	typedef std::size_t AOIAvatarId;
	
	typedef std::size_t AOIPlayerId;
	
	typedef std::size_t AOITypeId;
	
	struct AOIPropagateAddAvatar
	{
		AOIPlayerId playerId;
		AOITypeId typeId;
		::AxeProtocol::Position pos;
		::AxeProtocol::Direction dir;
	};
	
	
	struct AOIPropagateRemoveAvatar
	{
		AOIPlayerId playerId;
	};
	
	
	struct AOIPropagateMoveAvatar
	{
		AOIPlayerId playerId;
		::AxeProtocol::MoveDesc steps;
	};
	
	
	typedef std::vector<AOIPropagateAddAvatar> AOIVectorAddAvatar;
	
	typedef std::vector<AOIPropagateMoveAvatar> AOIVectorMoveAvatar;
	
	typedef std::vector<AOIPropagateRemoveAvatar> AOIVectorRemoveAvatar;
	
	struct AOIPropagateDiffAvatar
	{
		AOIVectorAddAvatar add;
		AOIVectorMoveAvatar move;
		AOIVectorRemoveAvatar remove;
	};
	
	
	struct AOIAvatarDesc
	{
		AOIPlayerId playerId;
		AOITypeId typeId;
		::AxeProtocol::MoveDesc desc;
		float radius;
	};
	
	
	struct AOIAvatarMoveDesc
	{
		::AxeProtocol::MoveDesc desc;
	};
	
	
	typedef AxeHandle<class Bellhop_AOITile_insertAvatar> Bellhop_AOITile_insertAvatarPtr;
	typedef AxeHandle<class Bellhop_AOITile_removeAvatar> Bellhop_AOITile_removeAvatarPtr;
	typedef AxeHandle<class Bellhop_AOITile_moveAvatar> Bellhop_AOITile_moveAvatarPtr;
	typedef AxeHandle<class Bellhop_AOITile_updateAvatar> Bellhop_AOITile_updateAvatarPtr;
	
	class Servant_AOITile
		: virtual public Axe::Servant
	{
	public:
		static const std::string & getTypeId();
	
	public:
		virtual void insertAvatar_async( const Bellhop_AOITile_insertAvatarPtr & _cb, const AOIAvatarDesc & _desc, bool _master ) = 0;
		virtual void removeAvatar_async( const Bellhop_AOITile_removeAvatarPtr & _cb, const AOIAvatarId & _avatarId ) = 0;
		virtual void moveAvatar_async( const Bellhop_AOITile_moveAvatarPtr & _cb, const AOIAvatarId & _avatarId, const AOIAvatarMoveDesc & _desc ) = 0;
		virtual void updateAvatar_async( const Bellhop_AOITile_updateAvatarPtr & _cb, const AOIAvatarId & _avatarId ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	};
	
	typedef AxeHandle<Servant_AOITile> Servant_AOITilePtr;
	
	
	class Bellhop_AOITile_insertAvatar
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOITile_insertAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITilePtr & _servant );
	
	public:
		void response( const AOIAvatarId & );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOITilePtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOITile_insertAvatar> Bellhop_AOITile_insertAvatarPtr;
	class Bellhop_AOITile_removeAvatar
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOITile_removeAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITilePtr & _servant );
	
	public:
		void response();
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOITilePtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOITile_removeAvatar> Bellhop_AOITile_removeAvatarPtr;
	class Bellhop_AOITile_moveAvatar
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOITile_moveAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITilePtr & _servant );
	
	public:
		void response();
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOITilePtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOITile_moveAvatar> Bellhop_AOITile_moveAvatarPtr;
	class Bellhop_AOITile_updateAvatar
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOITile_updateAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITilePtr & _servant );
	
	public:
		void response( const AOIPropagateDiffAvatar & );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOITilePtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOITile_updateAvatar> Bellhop_AOITile_updateAvatarPtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_AOITile_insertAvatar
		: public Axe::Response
	{
	protected:
		virtual void response( const AOIAvatarId & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITile_insertAvatar> Response_AOITile_insertAvatarPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_AOITile_removeAvatar
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITile_removeAvatar> Response_AOITile_removeAvatarPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_AOITile_moveAvatar
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITile_moveAvatar> Response_AOITile_moveAvatarPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_AOITile_updateAvatar
		: public Axe::Response
	{
	protected:
		virtual void response( const AOIPropagateDiffAvatar & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITile_updateAvatar> Response_AOITile_updateAvatarPtr;
	
	class Proxy_AOITile
		: virtual public Axe::Proxy
	{
	public:
		Proxy_AOITile( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider );
	
	public:
		void insertAvatar_async( const Response_AOITile_insertAvatarPtr & _response, const AOIAvatarDesc & _desc, bool _master );
		void removeAvatar_async( const Response_AOITile_removeAvatarPtr & _response, const AOIAvatarId & _avatarId );
		void moveAvatar_async( const Response_AOITile_moveAvatarPtr & _response, const AOIAvatarId & _avatarId, const AOIAvatarMoveDesc & _desc );
		void updateAvatar_async( const Response_AOITile_updateAvatarPtr & _response, const AOIAvatarId & _avatarId );
	};
	
	typedef AxeHandle<Proxy_AOITile> Proxy_AOITilePtr;
	
	typedef AxeHandle<class Bellhop_AOITileFactory_createTile> Bellhop_AOITileFactory_createTilePtr;
	typedef AxeHandle<class Bellhop_AOITileFactory_destroyTile> Bellhop_AOITileFactory_destroyTilePtr;
	
	class Servant_AOITileFactory
		: virtual public Axe::Servant
	{
	public:
		static const std::string & getTypeId();
	
	public:
		virtual void createTile_async( const Bellhop_AOITileFactory_createTilePtr & _cb ) = 0;
		virtual void destroyTile_async( const Bellhop_AOITileFactory_destroyTilePtr & _cb, const Proxy_AOITilePtr & _tileProxy ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	};
	
	typedef AxeHandle<Servant_AOITileFactory> Servant_AOITileFactoryPtr;
	
	
	class Bellhop_AOITileFactory_createTile
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOITileFactory_createTile( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITileFactoryPtr & _servant );
	
	public:
		void response( const Proxy_AOITilePtr & );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOITileFactoryPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOITileFactory_createTile> Bellhop_AOITileFactory_createTilePtr;
	class Bellhop_AOITileFactory_destroyTile
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOITileFactory_destroyTile( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITileFactoryPtr & _servant );
	
	public:
		void response();
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOITileFactoryPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOITileFactory_destroyTile> Bellhop_AOITileFactory_destroyTilePtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_AOITileFactory_createTile
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_AOITilePtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITileFactory_createTile> Response_AOITileFactory_createTilePtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_AOITileFactory_destroyTile
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITileFactory_destroyTile> Response_AOITileFactory_destroyTilePtr;
	
	class Proxy_AOITileFactory
		: virtual public Axe::Proxy
	{
	public:
		Proxy_AOITileFactory( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider );
	
	public:
		void createTile_async( const Response_AOITileFactory_createTilePtr & _response );
		void destroyTile_async( const Response_AOITileFactory_destroyTilePtr & _response, const Proxy_AOITilePtr & _tileProxy );
	};
	
	typedef AxeHandle<Proxy_AOITileFactory> Proxy_AOITileFactoryPtr;
	
	typedef AxeHandle<class Bellhop_AOISpace_insertAvatar> Bellhop_AOISpace_insertAvatarPtr;
	typedef AxeHandle<class Bellhop_AOISpace_removeAvatar> Bellhop_AOISpace_removeAvatarPtr;
	typedef AxeHandle<class Bellhop_AOISpace_moveAvatar> Bellhop_AOISpace_moveAvatarPtr;
	typedef AxeHandle<class Bellhop_AOISpace_updateAvatar> Bellhop_AOISpace_updateAvatarPtr;
	typedef AxeHandle<class Bellhop_AOISpace_finalize> Bellhop_AOISpace_finalizePtr;
	
	class Servant_AOISpace
		: virtual public Axe::Servant
	{
	public:
		static const std::string & getTypeId();
	
	public:
		virtual void insertAvatar_async( const Bellhop_AOISpace_insertAvatarPtr & _cb, const AOIAvatarDesc & _desc ) = 0;
		virtual void removeAvatar_async( const Bellhop_AOISpace_removeAvatarPtr & _cb, const AOIAvatarId & _userId ) = 0;
		virtual void moveAvatar_async( const Bellhop_AOISpace_moveAvatarPtr & _cb, const AOIAvatarId & _userId, const AOIAvatarMoveDesc & _moveDesc ) = 0;
		virtual void updateAvatar_async( const Bellhop_AOISpace_updateAvatarPtr & _cb, const AOIAvatarId & _userId ) = 0;
		virtual void finalize_async( const Bellhop_AOISpace_finalizePtr & _cb ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	
	protected:
		void _restore( Axe::ArchiveDispatcher & _ar ) override;
		void _evict( Axe::ArchiveInvocation & _aw ) override;
	
	protected:
		Proxy_AOITilePtr m_tileProxy;
	};
	
	typedef AxeHandle<Servant_AOISpace> Servant_AOISpacePtr;
	
	
	class Bellhop_AOISpace_insertAvatar
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOISpace_insertAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpacePtr & _servant );
	
	public:
		void response( const AOIAvatarId & );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOISpacePtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOISpace_insertAvatar> Bellhop_AOISpace_insertAvatarPtr;
	class Bellhop_AOISpace_removeAvatar
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOISpace_removeAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpacePtr & _servant );
	
	public:
		void response();
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOISpacePtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOISpace_removeAvatar> Bellhop_AOISpace_removeAvatarPtr;
	class Bellhop_AOISpace_moveAvatar
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOISpace_moveAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpacePtr & _servant );
	
	public:
		void response();
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOISpacePtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOISpace_moveAvatar> Bellhop_AOISpace_moveAvatarPtr;
	class Bellhop_AOISpace_updateAvatar
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOISpace_updateAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpacePtr & _servant );
	
	public:
		void response( const AOIPropagateDiffAvatar & );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOISpacePtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOISpace_updateAvatar> Bellhop_AOISpace_updateAvatarPtr;
	class Bellhop_AOISpace_finalize
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOISpace_finalize( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpacePtr & _servant );
	
	public:
		void response( const Proxy_AOITilePtr & );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOISpacePtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOISpace_finalize> Bellhop_AOISpace_finalizePtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpace_insertAvatar
		: public Axe::Response
	{
	protected:
		virtual void response( const AOIAvatarId & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpace_insertAvatar> Response_AOISpace_insertAvatarPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpace_removeAvatar
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpace_removeAvatar> Response_AOISpace_removeAvatarPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpace_moveAvatar
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpace_moveAvatar> Response_AOISpace_moveAvatarPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpace_updateAvatar
		: public Axe::Response
	{
	protected:
		virtual void response( const AOIPropagateDiffAvatar & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpace_updateAvatar> Response_AOISpace_updateAvatarPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpace_finalize
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_AOITilePtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpace_finalize> Response_AOISpace_finalizePtr;
	
	class Proxy_AOISpace
		: virtual public Axe::Proxy
	{
	public:
		Proxy_AOISpace( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider );
	
	public:
		void insertAvatar_async( const Response_AOISpace_insertAvatarPtr & _response, const AOIAvatarDesc & _desc );
		void removeAvatar_async( const Response_AOISpace_removeAvatarPtr & _response, const AOIAvatarId & _userId );
		void moveAvatar_async( const Response_AOISpace_moveAvatarPtr & _response, const AOIAvatarId & _userId, const AOIAvatarMoveDesc & _moveDesc );
		void updateAvatar_async( const Response_AOISpace_updateAvatarPtr & _response, const AOIAvatarId & _userId );
		void finalize_async( const Response_AOISpace_finalizePtr & _response );
	};
	
	typedef AxeHandle<Proxy_AOISpace> Proxy_AOISpacePtr;
	
	typedef AxeHandle<class Bellhop_AOISpaceFactory_createSpace> Bellhop_AOISpaceFactory_createSpacePtr;
	typedef AxeHandle<class Bellhop_AOISpaceFactory_destroySpace> Bellhop_AOISpaceFactory_destroySpacePtr;
	
	class Servant_AOISpaceFactory
		: virtual public Axe::Servant
	{
	public:
		static const std::string & getTypeId();
	
	public:
		virtual void createSpace_async( const Bellhop_AOISpaceFactory_createSpacePtr & _cb ) = 0;
		virtual void destroySpace_async( const Bellhop_AOISpaceFactory_destroySpacePtr & _cb, const Proxy_AOISpacePtr & spaceProxy ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	};
	
	typedef AxeHandle<Servant_AOISpaceFactory> Servant_AOISpaceFactoryPtr;
	
	
	class Bellhop_AOISpaceFactory_createSpace
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOISpaceFactory_createSpace( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpaceFactoryPtr & _servant );
	
	public:
		void response( const Proxy_AOISpacePtr & );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOISpaceFactoryPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOISpaceFactory_createSpace> Bellhop_AOISpaceFactory_createSpacePtr;
	class Bellhop_AOISpaceFactory_destroySpace
		: public Axe::Bellhop
	{
	public:
		Bellhop_AOISpaceFactory_destroySpace( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpaceFactoryPtr & _servant );
	
	public:
		void response();
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_AOISpaceFactoryPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_AOISpaceFactory_destroySpace> Bellhop_AOISpaceFactory_destroySpacePtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpaceFactory_createSpace
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_AOISpacePtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpaceFactory_createSpace> Response_AOISpaceFactory_createSpacePtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpaceFactory_destroySpace
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpaceFactory_destroySpace> Response_AOISpaceFactory_destroySpacePtr;
	
	class Proxy_AOISpaceFactory
		: virtual public Axe::Proxy
	{
	public:
		Proxy_AOISpaceFactory( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider );
	
	public:
		void createSpace_async( const Response_AOISpaceFactory_createSpacePtr & _response );
		void destroySpace_async( const Response_AOISpaceFactory_destroySpacePtr & _response, const Proxy_AOISpacePtr & spaceProxy );
	};
	
	typedef AxeHandle<Proxy_AOISpaceFactory> Proxy_AOISpaceFactoryPtr;
}
namespace Axe
{
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeLibProtocol::AOIPropagateAddAvatar & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeLibProtocol::AOIPropagateAddAvatar & _value );
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeLibProtocol::AOIPropagateRemoveAvatar & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeLibProtocol::AOIPropagateRemoveAvatar & _value );
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeLibProtocol::AOIPropagateMoveAvatar & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeLibProtocol::AOIPropagateMoveAvatar & _value );
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeLibProtocol::AOIPropagateDiffAvatar & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeLibProtocol::AOIPropagateDiffAvatar & _value );
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeLibProtocol::AOIAvatarDesc & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeLibProtocol::AOIAvatarDesc & _value );
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeLibProtocol::AOIAvatarMoveDesc & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeLibProtocol::AOIAvatarMoveDesc & _value );
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOITile_insertAvatarPtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOITile_insertAvatar, void(const ::AxeLibProtocol::AOIAvatarId &)>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOITile_insertAvatar, void(const ::AxeLibProtocol::AOIAvatarId &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const ::AxeLibProtocol::AOIAvatarId & _arg0 ) override;
	};
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOITile_removeAvatarPtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOITile_removeAvatar, void()>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOITile_removeAvatar, void()> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response() override;
	};
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOITile_moveAvatarPtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOITile_moveAvatar, void()>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOITile_moveAvatar, void()> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response() override;
	};
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOITile_updateAvatarPtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOITile_updateAvatar, void(const ::AxeLibProtocol::AOIPropagateDiffAvatar &)>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOITile_updateAvatar, void(const ::AxeLibProtocol::AOIPropagateDiffAvatar &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const ::AxeLibProtocol::AOIPropagateDiffAvatar & _arg0 ) override;
	};
	
	void operator << ( Axe::ArchiveInvocation & _ar, const ::AxeLibProtocol::Proxy_AOITilePtr & _value );
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOITileFactory_createTilePtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOITileFactory_createTile, void(const ::AxeLibProtocol::Proxy_AOITilePtr &)>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOITileFactory_createTile, void(const ::AxeLibProtocol::Proxy_AOITilePtr &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const ::AxeLibProtocol::Proxy_AOITilePtr & _arg0 ) override;
	};
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOITileFactory_destroyTilePtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOITileFactory_destroyTile, void()>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOITileFactory_destroyTile, void()> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response() override;
	};
	
	void operator << ( Axe::ArchiveInvocation & _ar, const ::AxeLibProtocol::Proxy_AOITileFactoryPtr & _value );
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOISpace_insertAvatarPtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOISpace_insertAvatar, void(const ::AxeLibProtocol::AOIAvatarId &)>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOISpace_insertAvatar, void(const ::AxeLibProtocol::AOIAvatarId &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const ::AxeLibProtocol::AOIAvatarId & _arg0 ) override;
	};
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOISpace_removeAvatarPtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOISpace_removeAvatar, void()>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOISpace_removeAvatar, void()> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response() override;
	};
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOISpace_moveAvatarPtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOISpace_moveAvatar, void()>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOISpace_moveAvatar, void()> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response() override;
	};
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOISpace_updateAvatarPtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOISpace_updateAvatar, void(const ::AxeLibProtocol::AOIPropagateDiffAvatar &)>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOISpace_updateAvatar, void(const ::AxeLibProtocol::AOIPropagateDiffAvatar &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const ::AxeLibProtocol::AOIPropagateDiffAvatar & _arg0 ) override;
	};
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOISpace_finalizePtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOISpace_finalize, void(const ::AxeLibProtocol::Proxy_AOITilePtr &)>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOISpace_finalize, void(const ::AxeLibProtocol::Proxy_AOITilePtr &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const ::AxeLibProtocol::Proxy_AOITilePtr & _arg0 ) override;
	};
	
	void operator << ( Axe::ArchiveInvocation & _ar, const ::AxeLibProtocol::Proxy_AOISpacePtr & _value );
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOISpaceFactory_createSpacePtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOISpaceFactory_createSpace, void(const ::AxeLibProtocol::Proxy_AOISpacePtr &)>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOISpaceFactory_createSpace, void(const ::AxeLibProtocol::Proxy_AOISpacePtr &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const ::AxeLibProtocol::Proxy_AOISpacePtr & _arg0 ) override;
	};
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_AOISpaceFactory_destroySpacePtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_AOISpaceFactory_destroySpace, void()>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_AOISpaceFactory_destroySpace, void()> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response() override;
	};
	
	void operator << ( Axe::ArchiveInvocation & _ar, const ::AxeLibProtocol::Proxy_AOISpaceFactoryPtr & _value );
}
