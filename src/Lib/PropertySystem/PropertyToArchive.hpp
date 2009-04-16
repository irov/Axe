#	pragma once

#	include <AxeUtil/ArchiveWrite.hpp>

#	include "VisitorAdapter.hpp"

namespace AxeProperty
{
	//////////////////////////////////////////////////////////////////////////
	class PropertyToArchive
		: public VisitorAdapter<PropertyToArchive>
	{
	public:
		PropertyToArchive( AxeUtil::ArchiveWrite & _archive );

	public:
		template<class T>
		void process( Numeric<T> * _property )
		{
			T value = _property->getValue();
			m_archive.write( value );
		}

		void process( String * _property );
		void process( Array * _property );

	protected:
		AxeUtil::ArchiveWrite & m_archive;
	};

	void propertyToArchive( const BasePtr & _property, AxeUtil::ArchiveWrite & _archive );
}