#	pragma once

namespace Axe
{
	namespace Declaration
	{
		struct Type
		{
			std::string name;
		};

		typedef std::vector<Type> TVectorTypes;

		struct Typedef
		{
			std::string name;
			std::string type;

			TVectorTypes templates;
		};

		typedef std::vector<Typedef> TVectorTypedefs;

		struct Argument
		{
			std::string name;
			Type type;
		};

		typedef std::vector<Argument> TVectorArguments;

		struct Member
		{
			std::string name;
			Type type;
		};

		typedef std::vector<Member> TVectorMembers;

		struct Method
		{
			std::string name;
		
			TVectorArguments inArguments;
			TVectorArguments outArguments;
		};

		typedef std::vector<Method> TVectorMethods;

		struct Parent
		{
			std::string name;
			std::string inheritance;
		};

		typedef std::vector<Parent> TVectorParents;

		struct Struct
		{
			std::string name;

			TVectorParents parents;
			TVectorMembers members;
		};

		typedef std::vector<Struct> TVectorStructs;
		

		struct Class
		{
			std::string name;
			
			TVectorParents parents;
			TVectorMembers members;
			TVectorMethods methods;
		};

		typedef std::vector<Class> TVectorClasses;

		enum EOrder
		{
			DECL_TYPEDEF,
			DECL_STRUCT,
			DECL_CLASS
		};

		typedef std::vector<EOrder> TVectorOrder;
	}
}