#	pragma once

#	include <Axe/Exception.hpp>

namespace Axe
{
	class ConnectionSocketException
		: public Exception
	{
	public:
		ConnectionSocketException( const boost::system::error_code & _code );

	public:
		void rethrow() const override;

	public:
		void write( ArchiveInvocation & _ar ) const override;
		void read( ArchiveDispatcher & _ar ) override;

	public:
		static const std::size_t exceptionId = EX_ConnectionConnectException;

	public:
		boost::system::error_code code;
	};

	class ConnectionInvalidPermissionException
		: public Exception
	{
	public:
		void rethrow() const override;

	public:
		void write( ArchiveInvocation & _ar ) const override;
		void read( ArchiveDispatcher & _ar ) override;

	public:
		static const std::size_t exceptionId = EX_ConnectionInvalidPermissionException;
	};

}