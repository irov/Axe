namespace Axe
{
	struct PlayerInfo
	{
		string name;
		int id;
	};

	class Player
	{
		int test( PlayerInfo info );
	};

	class Unique
	{
	};

	class PermissionsVerifier
		: public Unique
	{
		bool checkPermissions( string _login, string _password );
	};

	class SessionManager
		: public Unique
	{
		Player create( string _login );
	};

	typedef map<std::string, size_t> TMapAdapterIds;

	exception AdapterAlreadyExistet
	{
		string name;
	};

	class GridManager
	{
		size_t addAdapter( string _name, string _endpoint ) throws AdapterAlreadyExistet;
		string getAdapterEndpoint( size_t _hostId );


		void addUnique( string _name, Unique _unique );
		Unique getUnique( string _name );

		TMapAdapterIds m_adapterIds;
		size_t m_enumeratorID;
	};
}