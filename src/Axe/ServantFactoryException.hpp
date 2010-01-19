#	pragma once

#	include <Axe/Exception.hpp>

namespace Axe
{
	class ServantFactoryException
		: public Exception
	{
	};

	class ServantFactoryGeneratorNotFoundException
		: public ServantFactoryException
	{
	public:
		void rethrow() const override;

	public:
		void write( ArchiveInvocation & _ar ) const override;
		void read( ArchiveDispatcher & _ar ) override;

	public:
		static const std::size_t exceptionId = EX_ServantFactoryGeneratorNotFoundException;

	public:
		std::size_t typeId;
	};
}