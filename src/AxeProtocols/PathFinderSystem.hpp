#	pragma once

#	include <Axe/Bellhop.hpp>
#	include <Axe/Servant.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Exception.hpp>

#	include <../AxeProtocols/Common.hpp>

namespace Axe
{
	class ArchiveInvocation;
	class ArchiveDispatcher;
}

namespace Axe
{
	
	struct PathFinderAvatarDesc
	{
		AxeProtocol::Position pos;
		float speed;
		float radius;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const PathFinderAvatarDesc & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, PathFinderAvatarDesc & _value );
	
	typedef int AvatarId;
	
	struct PathFinderCluster
	{
		int type;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const PathFinderCluster & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, PathFinderCluster & _value );
	
	typedef std::vector<PathFinderCluster> TVectorPathFinderClusters;
	
	struct PathFinderSpaceDesc
	{
		int width;
		int height;
		TVectorPathFinderClusters m_clusters;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const PathFinderSpaceDesc & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, PathFinderSpaceDesc & _value );
	
	typedef AxeHandle<class Bellhop_PathFinderSpace_addAvatar> Bellhop_PathFinderSpace_addAvatarPtr;
	typedef AxeHandle<class Bellhop_PathFinderSpace_moveTo> Bellhop_PathFinderSpace_moveToPtr;
	
	class Servant_PathFinderSpace
		: virtual public Axe::Servant
	{
	public:
		virtual void addAvatar_async( const Bellhop_PathFinderSpace_addAvatarPtr & _cb, const PathFinderAvatarDesc & _desc ) = 0;
		virtual void moveTo_async( const Bellhop_PathFinderSpace_moveToPtr & _cb, __compiler__type__error _id, const AxeProtocol::Position & _pos ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	
	protected:
		void _restore( ArchiveDispatcher & _ar ) override;
		void _evict( ArchiveInvocation & _aw ) override;
	
	protected:
		PathFinderSpaceDesc m_desc;
	};
	
	typedef AxeHandle<Servant_PathFinderSpace> Servant_PathFinderSpacePtr;
	
	
	class Bellhop_PathFinderSpace_addAvatar
		: public Axe::Bellhop
	{
	public:
		Bellhop_PathFinderSpace_addAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_PathFinderSpacePtr & _servant );
	
	public:
		void response( __compiler__type__error );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_PathFinderSpacePtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_PathFinderSpace_addAvatar> Bellhop_PathFinderSpace_addAvatarPtr;
	class Bellhop_PathFinderSpace_moveTo
		: public Axe::Bellhop
	{
	public:
		Bellhop_PathFinderSpace_moveTo( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_PathFinderSpacePtr & _servant );
	
	public:
		void response();
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_PathFinderSpacePtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_PathFinderSpace_moveTo> Bellhop_PathFinderSpace_moveToPtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_PathFinderSpace_addAvatar
		: public Axe::Response
	{
	protected:
		virtual void response( __compiler__type__error ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_PathFinderSpace_addAvatar> Response_PathFinderSpace_addAvatarPtr;
	
	template<>
	class BindResponse<Response_PathFinderSpace_addAvatarPtr>
		: public Response_PathFinderSpace_addAvatar
	{
		typedef boost::function<void(__compiler__type__error)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( __compiler__type__error _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_PathFinderSpace_moveTo
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_PathFinderSpace_moveTo> Response_PathFinderSpace_moveToPtr;
	
	template<>
	class BindResponse<Response_PathFinderSpace_moveToPtr>
		: public Response_PathFinderSpace_moveTo
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
	
	class Proxy_PathFinderSpace
		: virtual public Axe::Proxy
	{
	public:
		Proxy_PathFinderSpace( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider );
	
	public:
		void addAvatar_async( const Response_PathFinderSpace_addAvatarPtr & _response, const PathFinderAvatarDesc & _desc );
		void moveTo_async( const Response_PathFinderSpace_moveToPtr & _response, __compiler__type__error _id, const AxeProtocol::Position & _pos );
	};
	
	typedef AxeHandle<Proxy_PathFinderSpace> Proxy_PathFinderSpacePtr;
	
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_PathFinderSpacePtr & _value );
	
	typedef AxeHandle<class Bellhop_PathFinderManager_createSpace> Bellhop_PathFinderManager_createSpacePtr;
	
	class Servant_PathFinderManager
		: virtual public Axe::Servant
	{
	public:
		virtual void createSpace_async( const Bellhop_PathFinderManager_createSpacePtr & _cb, const PathFinderSpaceDesc & _desc ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	};
	
	typedef AxeHandle<Servant_PathFinderManager> Servant_PathFinderManagerPtr;
	
	
	class Bellhop_PathFinderManager_createSpace
		: public Axe::Bellhop
	{
	public:
		Bellhop_PathFinderManager_createSpace( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_PathFinderManagerPtr & _servant );
	
	public:
		void response( const Proxy_PathFinderSpacePtr & );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_PathFinderManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_PathFinderManager_createSpace> Bellhop_PathFinderManager_createSpacePtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_PathFinderManager_createSpace
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_PathFinderSpacePtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_PathFinderManager_createSpace> Response_PathFinderManager_createSpacePtr;
	
	template<>
	class BindResponse<Response_PathFinderManager_createSpacePtr>
		: public Response_PathFinderManager_createSpace
	{
		typedef boost::function<void(const Proxy_PathFinderSpacePtr &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const Proxy_PathFinderSpacePtr & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_PathFinderManager
		: virtual public Axe::Proxy
	{
	public:
		Proxy_PathFinderManager( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider );
	
	public:
		void createSpace_async( const Response_PathFinderManager_createSpacePtr & _response, const PathFinderSpaceDesc & _desc );
	};
	
	typedef AxeHandle<Proxy_PathFinderManager> Proxy_PathFinderManagerPtr;
	
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_PathFinderManagerPtr & _value );
}
