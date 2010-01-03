namespace Axe
{
	typedef map<string, size_t> TMapAdapterIds;

	exception AdapterAlreadyExistException
	{
		string name;
	};

	exception HostNotFoundException
	{
		size_t hostId;
	};

	exception UniqueAlreadyExistException
	{
		string name;
	};

	exception UniqueNotFoundException
	{
		string name;
	};

	class Unique
	{
	};

	class GridManager
	{
		size_t addAdapter( string _name, string _endpoint ) throws AdapterAlreadyExistException;
		string getAdapterEndpoint( size_t _hostId ) throws HostNotFoundException;

		void addUnique( string _name, Unique _unique ) throws UniqueAlreadyExistException;
		Unique getUnique( string _name ) throws UniqueNotFoundException;

		TMapAdapterIds m_adapterIds;
		size_t m_enumeratorID;
	};

	exception EvictingNotFoundException
	{
		size_t servantId;
	};

	class EvictorManager
	{
		Archive get( size_t _servantId ) throws EvictingNotFoundException;
	};

	struct PlayerInfo
	{
		string name;
		int id;
	};

	class Player
	{
		int test( PlayerInfo info );
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
}