#	pragma once

class adapter_session;

class servant_base
{
public:
	virtual void call_method( std::size_t _id, std::size_t _requestId, adapter_session * _session ) = 0;
};