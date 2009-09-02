#	include "ArchiveToProperty.hpp"

#	include "String.hpp"
#	include "Array.hpp"

namespace AxeProperty
{
	//////////////////////////////////////////////////////////////////////////
	ArchiveToProperty::ArchiveToProperty( AxeUtil::ArchiveRead & _archive, const BasePtr & _property )
		: m_archive(_archive)
		, m_property(_property)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveToProperty::process( TypeString * _type )
	{
		StringPtr pr = AxeUtil::handleCast<StringPtr>(m_property);

		std::string value;

		m_archive.read( value );

		pr->setValue( value );
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveToProperty::process( TypeArray * _type )
	{
		ArrayPtr pr = AxeUtil::handleCast<ArrayPtr>(m_property);

		pr->clearValue();

		std::size_t size;
		m_archive.readSize( size );

		const TypePtr & elementType = _type->getElementType();

		for( std::size_t 
			it = 0,
			it_end = size;
		it != it_end;
		++it )
		{
			BasePtr elementpr = elementType->gen();
			ArchiveToProperty ap( m_archive, elementpr );
			elementType->visit( &ap );

			pr->addElement( elementpr );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void archiveToProperty( AxeUtil::ArchiveRead & _archive, const BasePtr & _property )
	{
		ArchiveToProperty ap( _archive, _property );
		const TypePtr & type = _property->getType();
		type->visit( &ap );
	}
}