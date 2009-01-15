------------------------------------------------------------------------------

MAKE_PROTOCOL( test, 
			  CARBON_METHOD_VOID( foo, (int)(float) )
			  CARBON_METHOD( bar, (int), (float) )
			  CARBON_METHOD( moo, (int)(float)(float), (float)(float) )
			  CARBON_METHOD_VOID( too, (float) )
			  );


MAKE_PROTOCOL( grid, 
			  CARBON_METHOD( add_adapter, (std::string)(std::string)(unsigned short), (std::size_t) )
			  CARBON_METHOD( get_adapter_name, (std::string), (std::string)(unsigned short) )
			  CARBON_METHOD( get_adapter_id, (size_t), (std::string)(unsigned short) )
			  );

MAKE_PROTOCOL( glacier, 
			  CARBON_METHOD( create, (std::string)(std::string), (std::size_t) )
			  );

------------------------------------------------------------------------------
#	include "some.hpp"

class test
{
	void foo( int a, float b );
	float bar( int a );
	int moo( int c, float b, float c, out float a, out float b );

public:
	int m_a;
	float m_b;

private:
	int m_c;
	float m_d;
};

class foo
	: public test
{
	void aa( test * t );
};

class bad
{
	void gg( test * t );
};

------------------------------------------------------------------------------

std::map<std::string, class_decl * > classes;

class class_decl
{
	std::map<std::string, method_decl * > methods;
	std::map<std::string, member_decl * > members;
	std::map<std::string, class_decl * > parents;
};

class member_decl
{
	std::string type;
	std::string name; 
};

class method_decl
{
	std::map<std::string, argument_decl *> in_args;
	std::map<std::string, argument_decl *> out_args;
};

class argument_decl
{
	std::string type;
	std::string name;	
};

------------------------------------------------------------------------------

[
bool
int
unsigned
float
double
TClass *
]

[
vector<T>
map<K,V>
]

[
typedef vector<T> TNew;
]

------------------------------------------------------------------------------

