namespace Axe
{
	class Player
	{
		int test( string name, int id );
	};

	class SessionManager
	{
		Player login( string _login, string _password );
	};

	typedef map<std::string, size_t> TMapAdapterIds;

	class GridManager
	{
		size_t addAdapter( string _name );

		SessionManager getSessionManager();
		void setSessionManager( SessionManager _sessionManager );

		TMapAdapterIds m_adapterIds;
		size_t m_enumeratorID;
	};
}