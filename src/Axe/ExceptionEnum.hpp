#	pragma once

namespace Axe
{
	enum ExceptionEnum
	{
		EX_BEGIN
		, EX_LocalException = 1
		, EX_StdException = 2
		, EX_UnknownException = 3
		, EX_CriticalException = 4
		, EX_ProtocolMismatchException = 5
		, EX_DispatcherServantRelocateException = 10
		, EX_DispatcherServantNotFoundException = 11
		, EX_DispatcherUniqueNotFoundException = 12
		, EX_AdapterServantAlreadyExistException = 20
		, EX_ServantFactoryGeneratorNotFoundException = 30
		, EX_ConnectionConnectException = 40
		, EX_ConnectionInvalidPermissionException = 41
	};
}