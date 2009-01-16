struct base_info
{
	int id;
};

struct servant_info
	: public base_info
{
	string enpoint;
	size_t id;		
};

typedef vector<int> vector_int;

class grid
{
	servant_info get_servand_endpoint( string _name, vector_int vec );
};

class box
	: public grid
{
	void add();
};