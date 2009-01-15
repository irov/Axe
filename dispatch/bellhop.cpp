#	include "pch.hpp"
#	include "bellhop.hpp"

bellhop::bellhop( std::size_t _requestId, adapter_session * _session )
: m_requestId(_requestId)
, m_session(_session)
{

}