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
	
	struct PathFinderAvatarDesc
	{
		::AxeProtocol::Position pos;
		float speed;
		float radius;
	};
	
	
	typedef int AvatarId;
	
	struct PathFinderCluster
	{
		int type;
	};
	
	
	typedef std::vector<PathFinderCluster> TVectorPathFinderClusters;
	
	struct PathFinderSpaceDesc
	{
		int width;
		int height;
		TVectorPathFinderClusters m_clusters;
	};
	
	
	typedef AxeHandle<class Bellhop_PathFinderSpace_addAvatar> Bellhop_PathFinderSpace_addAvatarPtr;
	typedef AxeHandle<class Bellhop_PathFinderSpace_moveTo> Bellhop_PathFinderSpace_moveToPtr;
	
	class Servant_PathFinderSpace
		: virtual public Axe::Servant
	{
	public:
		static const std::string & getTypeId();
	
	public:
		virtual void addAvatar_async( const Bellhop_PathFinderSpace_addAvatarPtr & _cb, const PathFinderAvatarDesc & _desc ) = 0;
		virtual void moveTo_async( const Bellhop_PathFinderSpace_moveToPtr & _cb, const AvatarId & _id, const ::AxeProtocol::Position & _pos ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	
	protected:
		void _restore( Axe::ArchiveDispatcher & _ar ) override;
		void _evict( Axe::ArchiveInvocation & _aw ) override;
	
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
		void response( const AvatarId & );
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
		virtual void response( const AvatarId & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_PathFinderSpace_addAvatar> Response_PathFinderSpace_addAvatarPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_PathFinderSpace_moveTo
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_PathFinderSpace_moveTo> Response_PathFinderSpace_moveToPtr;
	
	class Proxy_PathFinderSpace
		: virtual public Axe::Proxy
	{
	public:
		Proxy_PathFinderSpace( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider );
	
	public:
		void addAvatar_async( const Response_PathFinderSpace_addAvatarPtr & _response, const PathFinderAvatarDesc & _desc );
		void moveTo_async( const Response_PathFinderSpace_moveToPtr & _response, const AvatarId & _id, const ::AxeProtocol::Position & _pos );
	};
	
	typedef AxeHandle<Proxy_PathFinderSpace> Proxy_PathFinderSpacePtr;
	
	typedef AxeHandle<class Bellhop_PathFinderManager_createSpace> Bellhop_PathFinderManager_createSpacePtr;
	
	class Servant_PathFinderManager
		: virtual public Axe::Servant
	{
	public:
		static const std::string & getTypeId();
	
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
	};
	
	typedef AxeHandle<Response_PathFinderManager_createSpace> Response_PathFinderManager_createSpacePtr;
	
	class Proxy_PathFinderManager
		: virtual public Axe::Proxy
	{
	public:
		Proxy_PathFinderManager( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider );
	
	public:
		void createSpace_async( const Response_PathFinderManager_createSpacePtr & _response, const PathFinderSpaceDesc & _desc );
	};
	
	typedef AxeHandle<Proxy_PathFinderManager> Proxy_PathFinderManagerPtr;
}
namespace Axe
{
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeLibProtocol::PathFinderAvatarDesc & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeLibProtocol::PathFinderAvatarDesc & _value );
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeLibProtocol::PathFinderCluster & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeLibProtocol::PathFinderCluster & _value );
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeLibProtocol::PathFinderSpaceDesc & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeLibProtocol::PathFinderSpaceDesc & _value );
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_PathFinderSpace_addAvatarPtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_PathFinderSpace_addAvatar, void(const ::AxeLibProtocol::AvatarId &)>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_PathFinderSpace_addAvatar, void(const ::AxeLibProtocol::AvatarId &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const ::AxeLibProtocol::AvatarId & _arg0 ) override;
	};
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_PathFinderSpace_moveToPtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_PathFinderSpace_moveTo, void()>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_PathFinderSpace_moveTo, void()> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response() override;
	};
	
	void operator << ( Axe::ArchiveInvocation & _ar, const ::AxeLibProtocol::Proxy_PathFinderSpacePtr & _value );
	
	template<>
	class BindResponse<::AxeLibProtocol::Response_PathFinderManager_createSpacePtr>
		: public BindResponseHelper<::AxeLibProtocol::Response_PathFinderManager_createSpace, void(const ::AxeLibProtocol::Proxy_PathFinderSpacePtr &)>
	{
	protected:
		typedef BindResponseHelper<::AxeLibProtocol::Response_PathFinderManager_createSpace, void(const ::AxeLibProtocol::Proxy_PathFinderSpacePtr &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const ::AxeLibProtocol::Proxy_PathFinderSpacePtr & _arg0 ) override;
	};
	
	void operator << ( Axe::ArchiveInvocation & _ar, const ::AxeLibProtocol::Proxy_PathFinderManagerPtr & _value );
}
