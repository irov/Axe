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
	
	struct AOIPropagateAddAvatar
	{
		int userId;
		int typeId;
		AxeProtocol::Position pos;
		AxeProtocol::Direction dir;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const AOIPropagateAddAvatar & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIPropagateAddAvatar & _value );
	
	struct AOIPropagateRemoveAvatar
	{
		int userId;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const AOIPropagateRemoveAvatar & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIPropagateRemoveAvatar & _value );
	
	struct AOIPropagateMoveAvatar
	{
		int userId;
		AxeProtocol::MoveDesc steps;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const AOIPropagateMoveAvatar & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIPropagateMoveAvatar & _value );
	
	typedef std::vector<AOIPropagateAddAvatar> AOIVectorAddAvatar;
	
	typedef std::vector<AOIPropagateMoveAvatar> AOIVectorMoveAvatar;
	
	typedef std::vector<AOIPropagateRemoveAvatar> AOIVectorRemoveAvatar;
	
	struct AOIPropagateDiffAvatar
	{
		AOIVectorAddAvatar add;
		AOIVectorMoveAvatar move;
		AOIVectorRemoveAvatar remove;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const AOIPropagateDiffAvatar & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIPropagateDiffAvatar & _value );
	
	struct AOIAvatarDesc
	{
		int typeId;
		AxeProtocol::MoveDesc desc;
		float radius;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const AOIAvatarDesc & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIAvatarDesc & _value );
	
	struct AOIAvatarMoveDesc
	{
		AxeProtocol::MoveDesc desc;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const AOIAvatarMoveDesc & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIAvatarMoveDesc & _value );
	
	typedef AxeHandle<class Bellhop_AOITile_insertAvatar> Bellhop_AOITile_insertAvatarPtr;
	typedef AxeHandle<class Bellhop_AOITile_removeAvatar> Bellhop_AOITile_removeAvatarPtr;
	typedef AxeHandle<class Bellhop_AOITile_moveAvatar> Bellhop_AOITile_moveAvatarPtr;
	typedef AxeHandle<class Bellhop_AOITile_updateAvatar> Bellhop_AOITile_updateAvatarPtr;
	
	class Servant_AOITile
		: virtual public Axe::Servant
	{
	public:
		virtual void insertAvatar_async( const Bellhop_AOITile_insertAvatarPtr & _cb, int _userId, const AOIAvatarDesc & _desc, bool _master ) = 0;
		virtual void removeAvatar_async( const Bellhop_AOITile_removeAvatarPtr & _cb, int _avatarId ) = 0;
		virtual void moveAvatar_async( const Bellhop_AOITile_moveAvatarPtr & _cb, const AOIAvatarMoveDesc & _desc ) = 0;
		virtual void updateAvatar_async( const Bellhop_AOITile_updateAvatarPtr & _cb, int _avatarId ) = 0;
	
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
		void response( int );
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
		virtual void response( int ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITile_insertAvatar> Response_AOITile_insertAvatarPtr;
	
	template<>
	class BindResponse<Response_AOITile_insertAvatarPtr>
		: public Response_AOITile_insertAvatar
	{
		typedef boost::function<void(int)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( int _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_AOITile_removeAvatar
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITile_removeAvatar> Response_AOITile_removeAvatarPtr;
	
	template<>
	class BindResponse<Response_AOITile_removeAvatarPtr>
		: public Response_AOITile_removeAvatar
	{
		typedef boost::function<void()> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response() override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_AOITile_moveAvatar
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITile_moveAvatar> Response_AOITile_moveAvatarPtr;
	
	template<>
	class BindResponse<Response_AOITile_moveAvatarPtr>
		: public Response_AOITile_moveAvatar
	{
		typedef boost::function<void()> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response() override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_AOITile_updateAvatar
		: public Axe::Response
	{
	protected:
		virtual void response( const AOIPropagateDiffAvatar & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITile_updateAvatar> Response_AOITile_updateAvatarPtr;
	
	template<>
	class BindResponse<Response_AOITile_updateAvatarPtr>
		: public Response_AOITile_updateAvatar
	{
		typedef boost::function<void(const AOIPropagateDiffAvatar &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const AOIPropagateDiffAvatar & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_AOITile
		: virtual public Axe::Proxy
	{
	public:
		Proxy_AOITile( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider );
	
	public:
		void insertAvatar_async( const Response_AOITile_insertAvatarPtr & _response, int _userId, const AOIAvatarDesc & _desc, bool _master );
		void removeAvatar_async( const Response_AOITile_removeAvatarPtr & _response, int _avatarId );
		void moveAvatar_async( const Response_AOITile_moveAvatarPtr & _response, const AOIAvatarMoveDesc & _desc );
		void updateAvatar_async( const Response_AOITile_updateAvatarPtr & _response, int _avatarId );
	};
	
	typedef AxeHandle<Proxy_AOITile> Proxy_AOITilePtr;
	
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_AOITilePtr & _value );
	
	typedef AxeHandle<class Bellhop_AOITileFactory_createTile> Bellhop_AOITileFactory_createTilePtr;
	typedef AxeHandle<class Bellhop_AOITileFactory_destroyTile> Bellhop_AOITileFactory_destroyTilePtr;
	
	class Servant_AOITileFactory
		: virtual public Axe::Servant
	{
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
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITileFactory_createTile> Response_AOITileFactory_createTilePtr;
	
	template<>
	class BindResponse<Response_AOITileFactory_createTilePtr>
		: public Response_AOITileFactory_createTile
	{
		typedef boost::function<void(const Proxy_AOITilePtr &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const Proxy_AOITilePtr & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_AOITileFactory_destroyTile
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOITileFactory_destroyTile> Response_AOITileFactory_destroyTilePtr;
	
	template<>
	class BindResponse<Response_AOITileFactory_destroyTilePtr>
		: public Response_AOITileFactory_destroyTile
	{
		typedef boost::function<void()> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response() override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_AOITileFactory
		: virtual public Axe::Proxy
	{
	public:
		Proxy_AOITileFactory( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider );
	
	public:
		void createTile_async( const Response_AOITileFactory_createTilePtr & _response );
		void destroyTile_async( const Response_AOITileFactory_destroyTilePtr & _response, const Proxy_AOITilePtr & _tileProxy );
	};
	
	typedef AxeHandle<Proxy_AOITileFactory> Proxy_AOITileFactoryPtr;
	
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_AOITileFactoryPtr & _value );
	
	typedef AxeHandle<class Bellhop_AOISpace_insertAvatar> Bellhop_AOISpace_insertAvatarPtr;
	typedef AxeHandle<class Bellhop_AOISpace_removeAvatar> Bellhop_AOISpace_removeAvatarPtr;
	typedef AxeHandle<class Bellhop_AOISpace_moveAvatar> Bellhop_AOISpace_moveAvatarPtr;
	typedef AxeHandle<class Bellhop_AOISpace_updateAvatar> Bellhop_AOISpace_updateAvatarPtr;
	typedef AxeHandle<class Bellhop_AOISpace_finalize> Bellhop_AOISpace_finalizePtr;
	
	class Servant_AOISpace
		: virtual public Axe::Servant
	{
	public:
		virtual void insertAvatar_async( const Bellhop_AOISpace_insertAvatarPtr & _cb, __compiler__type__error _userPrx, const AOIAvatarDesc & _desc ) = 0;
		virtual void removeAvatar_async( const Bellhop_AOISpace_removeAvatarPtr & _cb, int _userId ) = 0;
		virtual void moveAvatar_async( const Bellhop_AOISpace_moveAvatarPtr & _cb, int _userId, const AOIAvatarMoveDesc & _moveDesc ) = 0;
		virtual void updateAvatar_async( const Bellhop_AOISpace_updateAvatarPtr & _cb, int _userId ) = 0;
		virtual void finalize_async( const Bellhop_AOISpace_finalizePtr & _cb ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	
	protected:
		void _restore( ArchiveDispatcher & _ar ) override;
		void _evict( ArchiveInvocation & _aw ) override;
	
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
		void response( int );
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
		virtual void response( int ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpace_insertAvatar> Response_AOISpace_insertAvatarPtr;
	
	template<>
	class BindResponse<Response_AOISpace_insertAvatarPtr>
		: public Response_AOISpace_insertAvatar
	{
		typedef boost::function<void(int)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( int _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpace_removeAvatar
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpace_removeAvatar> Response_AOISpace_removeAvatarPtr;
	
	template<>
	class BindResponse<Response_AOISpace_removeAvatarPtr>
		: public Response_AOISpace_removeAvatar
	{
		typedef boost::function<void()> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response() override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpace_moveAvatar
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpace_moveAvatar> Response_AOISpace_moveAvatarPtr;
	
	template<>
	class BindResponse<Response_AOISpace_moveAvatarPtr>
		: public Response_AOISpace_moveAvatar
	{
		typedef boost::function<void()> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response() override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpace_updateAvatar
		: public Axe::Response
	{
	protected:
		virtual void response( const AOIPropagateDiffAvatar & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpace_updateAvatar> Response_AOISpace_updateAvatarPtr;
	
	template<>
	class BindResponse<Response_AOISpace_updateAvatarPtr>
		: public Response_AOISpace_updateAvatar
	{
		typedef boost::function<void(const AOIPropagateDiffAvatar &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const AOIPropagateDiffAvatar & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpace_finalize
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_AOITilePtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpace_finalize> Response_AOISpace_finalizePtr;
	
	template<>
	class BindResponse<Response_AOISpace_finalizePtr>
		: public Response_AOISpace_finalize
	{
		typedef boost::function<void(const Proxy_AOITilePtr &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const Proxy_AOITilePtr & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_AOISpace
		: virtual public Axe::Proxy
	{
	public:
		Proxy_AOISpace( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider );
	
	public:
		void insertAvatar_async( const Response_AOISpace_insertAvatarPtr & _response, __compiler__type__error _userPrx, const AOIAvatarDesc & _desc );
		void removeAvatar_async( const Response_AOISpace_removeAvatarPtr & _response, int _userId );
		void moveAvatar_async( const Response_AOISpace_moveAvatarPtr & _response, int _userId, const AOIAvatarMoveDesc & _moveDesc );
		void updateAvatar_async( const Response_AOISpace_updateAvatarPtr & _response, int _userId );
		void finalize_async( const Response_AOISpace_finalizePtr & _response );
	};
	
	typedef AxeHandle<Proxy_AOISpace> Proxy_AOISpacePtr;
	
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_AOISpacePtr & _value );
	
	typedef AxeHandle<class Bellhop_AOISpaceFactory_createSpace> Bellhop_AOISpaceFactory_createSpacePtr;
	typedef AxeHandle<class Bellhop_AOISpaceFactory_destroySpace> Bellhop_AOISpaceFactory_destroySpacePtr;
	
	class Servant_AOISpaceFactory
		: virtual public Axe::Servant
	{
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
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpaceFactory_createSpace> Response_AOISpaceFactory_createSpacePtr;
	
	template<>
	class BindResponse<Response_AOISpaceFactory_createSpacePtr>
		: public Response_AOISpaceFactory_createSpace
	{
		typedef boost::function<void(const Proxy_AOISpacePtr &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const Proxy_AOISpacePtr & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_AOISpaceFactory_destroySpace
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_AOISpaceFactory_destroySpace> Response_AOISpaceFactory_destroySpacePtr;
	
	template<>
	class BindResponse<Response_AOISpaceFactory_destroySpacePtr>
		: public Response_AOISpaceFactory_destroySpace
	{
		typedef boost::function<void()> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response() override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_AOISpaceFactory
		: virtual public Axe::Proxy
	{
	public:
		Proxy_AOISpaceFactory( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider );
	
	public:
		void createSpace_async( const Response_AOISpaceFactory_createSpacePtr & _response );
		void destroySpace_async( const Response_AOISpaceFactory_destroySpacePtr & _response, const Proxy_AOISpacePtr & spaceProxy );
	};
	
	typedef AxeHandle<Proxy_AOISpaceFactory> Proxy_AOISpaceFactoryPtr;
	
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_AOISpaceFactoryPtr & _value );
}
