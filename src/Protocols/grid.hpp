#	pragma once

#	include <Axe/Bellhop.hpp>
#	include <Axe/Servant.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Response.hpp>

namespace Axe
{
	class ArchiveWrite;
	class ArchiveRead;
}

namespace Protocol
{
	
	struct base_info
	{
		int id;
	};
	
	void operator << ( Axe::ArchiveWrite & ar, const base_info & _value );
	void operator >> ( Axe::ArchiveRead & ar, base_info & _value );
	
	struct servant_info
		: public base_info
	{
		std::string enpoint;
		std::size_t id;
	};
	
	void operator << ( Axe::ArchiveWrite & ar, const servant_info & _value );
	void operator >> ( Axe::ArchiveRead & ar, servant_info & _value );
	
	typedef std::vector<int> vector_int;
	
	class Bellhop_grid_get_servand_endpoint
		: public Axe::Bellhop
	{
	public:
		Bellhop_grid_get_servand_endpoint( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response( const servant_info & );
	};
	
	typedef AxeHandle<Bellhop_grid_get_servand_endpoint> Bellhop_grid_get_servand_endpointPtr;
	
	class Servant_grid
		: virtual public Axe::Servant
	{
	public:
		virtual void get_servand_endpoint( const Bellhop_grid_get_servand_endpointPtr & _cb, const std::string & _name, const vector_int & vec ) = 0;
	
	protected:
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_grid> Servant_gridPtr;
	
	class Response_grid_get_servand_endpoint
		: public Axe::Response
	{
	protected:
		virtual void response( const servant_info & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_grid_get_servand_endpoint> Response_grid_get_servand_endpointPtr;
	
	
	class Proxy_grid
		: virtual public Axe::Proxy
	{
	public:
		Proxy_grid( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void get_servand_endpoint( const std::string & _name, const vector_int & vec, const Response_grid_get_servand_endpointPtr & _response );
	};
	
	typedef AxeHandle<Proxy_grid> Proxy_gridPtr;
	
	class Bellhop_box_add
		: public Axe::Bellhop
	{
	public:
		Bellhop_box_add( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response();
	};
	
	typedef AxeHandle<Bellhop_box_add> Bellhop_box_addPtr;
	
	class Servant_box
		:	public Servant_grid
	{
	public:
		virtual void add( const Bellhop_box_addPtr & _cb ) = 0;
	
	protected:
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_box> Servant_boxPtr;
	
	class Response_box_add
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_box_add> Response_box_addPtr;
	
	
	class Proxy_box
		:	public Proxy_grid
	{
	public:
		Proxy_box( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void add( const Response_box_addPtr & _response );
	};
	
	typedef AxeHandle<Proxy_box> Proxy_boxPtr;
	
	struct vec2f
	{
		float x;
		float y;
	};
	
	void operator << ( Axe::ArchiveWrite & ar, const vec2f & _value );
	void operator >> ( Axe::ArchiveRead & ar, vec2f & _value );
	
	class Bellhop_Player_moveTo
		: public Axe::Bellhop
	{
	public:
		Bellhop_Player_moveTo( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response();
	};
	
	typedef AxeHandle<Bellhop_Player_moveTo> Bellhop_Player_moveToPtr;
	class Bellhop_Player_teleportTo
		: public Axe::Bellhop
	{
	public:
		Bellhop_Player_teleportTo( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response();
	};
	
	typedef AxeHandle<Bellhop_Player_teleportTo> Bellhop_Player_teleportToPtr;
	
	class Servant_Player
		: virtual public Axe::Servant
	{
	public:
		virtual void moveTo( const Bellhop_Player_moveToPtr & _cb, const vec2f & _vec ) = 0;
		virtual void teleportTo( const Bellhop_Player_teleportToPtr & _cb, const vec2f & _vec ) = 0;
	
	protected:
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_Player> Servant_PlayerPtr;
	
	class Response_Player_moveTo
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_Player_moveTo> Response_Player_moveToPtr;
	
	class Response_Player_teleportTo
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_Player_teleportTo> Response_Player_teleportToPtr;
	
	
	class Proxy_Player
		: virtual public Axe::Proxy
	{
	public:
		Proxy_Player( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void moveTo( const vec2f & _vec, const Response_Player_moveToPtr & _response );
		void teleportTo( const vec2f & _vec, const Response_Player_teleportToPtr & _response );
	};
	
	typedef AxeHandle<Proxy_Player> Proxy_PlayerPtr;
	
	class Bellhop_Client_onConnect
		: public Axe::Bellhop
	{
	public:
		Bellhop_Client_onConnect( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response();
	};
	
	typedef AxeHandle<Bellhop_Client_onConnect> Bellhop_Client_onConnectPtr;
	
	class Servant_Client
		: virtual public Axe::Servant
	{
	public:
		virtual void onConnect( const Bellhop_Client_onConnectPtr & _cb, const Proxy_PlayerPtr & _player ) = 0;
	
	protected:
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_Client> Servant_ClientPtr;
	
	class Response_Client_onConnect
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_Client_onConnect> Response_Client_onConnectPtr;
	
	
	class Proxy_Client
		: virtual public Axe::Proxy
	{
	public:
		Proxy_Client( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void onConnect( const Proxy_PlayerPtr & _player, const Response_Client_onConnectPtr & _response );
	};
	
	typedef AxeHandle<Proxy_Client> Proxy_ClientPtr;
}
