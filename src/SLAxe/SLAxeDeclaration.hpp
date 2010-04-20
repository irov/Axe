#	pragma once

namespace Axe
{
	namespace Declaration
	{
		struct Namespace;

		struct Type
		{
			Type(): proxy(false){}

			std::string name;
			bool proxy;
		};

		typedef std::vector<Type> TVectorTypes;

		struct Include
		{
			std::string path;
		};

		typedef std::vector<Include> TVectorIncludes;

		struct Typedef
		{
			std::string name;
			std::string type;

			TVectorTypes templates;

			Namespace * owner;
		};

		typedef std::vector<Typedef> TVectorTypedefs;

		struct Argument
		{
			Argument(): out(false){};

			std::string name;
			Type type;
			bool out;
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

			Namespace * owner;
		};

		typedef std::vector<Struct> TVectorStructs;
		
		struct Exception
		{
			std::string name;

			TVectorParents parents;
			TVectorMembers members;

			Namespace * owner;
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

			Namespace * owner;
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
			Namespace( Namespace * _parent )
				: parent(_parent)
			{
			}

			Namespace * parent;
			std::string name;

			template<class T>
			std::vector<T> & getVector();

			template<> TVectorClasses & getVector(){ return classes; }
			template<> TVectorStructs & getVector(){ return structs; }
			template<> TVectorExceptions & getVector(){ return exceptions; }
			template<> TVectorTypedefs & getVector(){ return typedefs; }

			TVectorClasses classes;
			TVectorStructs structs;
			TVectorExceptions exceptions;
			TVectorTypedefs typedefs;

			TVectorOrder order;

			typedef std::list<Namespace> TListNamespaces;
			TListNamespaces namespaces;
		};

		typedef Namespace::TListNamespaces TListNamespaces;
	}
}