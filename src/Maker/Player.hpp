namespace Axe
{
	class Player
	{
		int test( string name, int id );
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

	class GridManager
	{
		size_t addAdapter( string _name );

		void addUnique( string _name, Unique _unique );
		Unique getUnique( string _name );

		TMapAdapterIds m_adapterIds;
		size_t m_enumeratorID;
	};
}