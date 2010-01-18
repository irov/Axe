#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	class Properties
		: virtual public AxeUtil::Shared
	{
	public:
		bool addProperty( const std::string & _key, const std::string & _value );

	public:
		const std::string & getProperty( const std::string & _key ) const;
		const std::string & getPropertyWithDefault( const std::string & _key, const std::string & _default ) const;

		int getPropertyInt( const std::string & _key ) const;
		int getPropertyIntWithDefault( const std::string & _key, int _default ) const;

		std::size_t getPropertySize( const std::string & _key ) const;
		std::size_t getPropertySizeWithDefault( const std::string & _key, std::size_t _default ) const;

		float getPropertyFloat( const std::string & _key ) const;
		float getPropertyFloatWithDefault( const std::string & _key, float _default ) const;

	protected:
		typedef std::map<std::string, std::string> TMapProperties;
		TMapProperties m_properties;

		std::string m_empty;
	};

	typedef AxeHandle<Properties> PropertiesPtr;
}