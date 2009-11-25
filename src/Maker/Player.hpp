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

	exception AdapterAlreadyExistetException
	{
		string name;
	};

	exception HostNotFoundException
	{
		size_t hostId;
	};

	exception UniqueAlreadyExistetException
	{
		string name;
	};

	exception UniqueNotFoundException
	{
		string name;
	};

	class GridManager
	{
		size_t addAdapter( string _name, string _endpoint ) throws AdapterAlreadyExistetException;
		string getAdapterEndpoint( size_t _hostId ) throws HostNotFoundException;

		void addUnique( string _name, Unique _unique ) throws UniqueAlreadyExistetException;
		Unique getUnique( string _name ) throws UniqueNotFoundException;

		TMapAdapterIds m_adapterIds;
		size_t m_enumeratorID;
	};
}