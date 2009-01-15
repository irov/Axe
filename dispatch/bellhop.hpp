#	pragma once

class adapter_session;

class bellhop
{
public:
	bellhop( std::size_t _requestId, adapter_session * _session );

protected:
	std::size_t m_requestId;
	adapter_session * m_session;
};