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
		
		struct Exception
		{
			std::string name;

			TVectorParents parents;
			TVectorMembers members;
		};

		typedef std::vector<Exception> TVectorExceptions;

		struct MethodException
		{
			std::string name;
		};

		typedef std::vector<MethodException> TVectorMethodExceptions;

		struct Method
		{
			std::string name;

			TVectorArguments inArguments;
			TVectorArguments outArguments;
			TVectorMethodExceptions exceptions;
		};

		typedef std::vector<Method> TVectorMethods;

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
			DECL_EXCEPTION,
			DECL_CLASS,
			DECL_NAMESPACE
		};

		typedef std::vector<EOrder> TVectorOrder;

		struct Namespace
		{
			std::string name;

			TVectorClasses classes;
			TVectorStructs structs;
			TVectorExceptions exceptions;
			TVectorTypedefs typedefs;

			TVectorOrder order;

			typedef std::vector<Namespace> TVectorNamespaces;
			TVectorNamespaces namespaces;
		};

		typedef Namespace::TVectorNamespaces TVectorNamespaces;
	}
}