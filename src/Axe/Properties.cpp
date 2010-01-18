#	include <Axe/pch.hpp>

#	include <Axe/Properties.hpp>

#	include <boost/lexical_cast.hpp>

namespace Axe
{
	namespace
	{
		class Helper
			: public Properties
		{
		public:
			static const std::string & s_getProperty( const TMapProperties & _properties, const std::string & _key, const std::string & _default )
			{
				TMapProperties::const_iterator it_found = _properties.find( _key );

				if( it_found == _properties.end() )
				{
					return _default;
				}

				return it_found->second;
			}

			template<class T>
			static T s_getProperty( const TMapProperties & _properties, const std::string & _key, T _default )
			{
				TMapProperties::const_iterator it_found = _properties.find( _key );

				if( it_found == _properties.end() )
				{
					return _default;
				}

				return boost::lexical_cast<T>( it_found->second );
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	bool Properties::addProperty( const std::string & _key, const std::string & _value )
	{
		return m_properties.insert( std::make_pair( _key, _value ) ).second;
	}
	//////////////////////////////////////////////////////////////////////////
	const std::string & Properties::getProperty( const std::string & _key ) const
	{
		return getPropertyWithDefault( _key, m_empty );
	}
	//////////////////////////////////////////////////////////////////////////
	const std::string & Properties::getPropertyWithDefault( const std::string & _key, const std::string & _default ) const
	{
		return Helper::s_getProperty( m_properties, _key, _default );
	}
	//////////////////////////////////////////////////////////////////////////
	int Properties::getPropertyInt( const std::string & _key ) const
	{
		return getPropertyIntWithDefault( _key, 0 );
	}
	//////////////////////////////////////////////////////////////////////////
	int Properties::getPropertyIntWithDefault( const std::string & _key, int _default ) const
	{
		return Helper::s_getProperty<int>( m_properties, _key, _default );
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Properties::getPropertySize( const std::string & _key ) const
	{
		return getPropertySizeWithDefault( _key, 0 );
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Properties::getPropertySizeWithDefault( const std::string & _key, std::size_t _default ) const
	{
		return Helper::s_getProperty<std::size_t>( m_properties, _key, _default );
	}
	//////////////////////////////////////////////////////////////////////////
	float Properties::getPropertyFloat( const std::string & _key ) const
	{
		return getPropertyFloatWithDefault( _key, 0.f );
	}
	//////////////////////////////////////////////////////////////////////////
	float Properties::getPropertyFloatWithDefault( const std::string & _key, float _default ) const
	{
		return Helper::s_getProperty<float>( m_properties, _key, _default );
	}
}