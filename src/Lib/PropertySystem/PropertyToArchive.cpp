#	include "PropertyToArchive.hpp"

namespace AxeProperty
{
	//////////////////////////////////////////////////////////////////////////
	PropertyToArchive::PropertyToArchive( AxeUtil::ArchiveWrite & _archive )
		: m_archive(_archive)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void PropertyToArchive::process( String * _property )
	{
		const std::string & value = _property->getValue();

		m_archive.writeString( value );
	}
	//////////////////////////////////////////////////////////////////////////
	void PropertyToArchive::process( Array * _property )
	{
		std::size_t size = _property->countElement();
		m_archive.writeSize( size );

		for( TVectorElements::size_type
			it = 0,
			it_end = size;
		it != it_end;
		++it )
		{
			const BasePtr & value = _property->getElement( it );

			value->visit( this );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void propertyToArchive( const BasePtr & _property, AxeUtil::ArchiveWrite & _archive )
	{
		PropertyToArchive pa( _archive );
		_property->visit( &pa );
	}
}