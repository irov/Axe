#	pragma once

#	include <AxeUtil/ArchiveRead.hpp>

#	include "TypeVisitorAdapter.hpp"

#	include "TypeNumeric.hpp"

namespace AxeProperty
{
	class ArchiveToProperty
		: public TypeVisitorAdapter<ArchiveToProperty>
	{
	public:
		ArchiveToProperty( AxeUtil::ArchiveRead & _archive, const BasePtr & _property );

	public:
		template<class T>
		void process( TypeNumeric<T> * _type )
		{
			typedef AxeHandle< Numeric<T> > NumericPtr;

			NumericPtr pr = AxeUtil::handleCast<NumericPtr>(m_property);

			T value;
			m_archive.read( value );

			pr->setValue( value );
		}

		void process( TypeString * _type );
		void process( TypeArray * _type );

	protected:
		AxeUtil::ArchiveRead & m_archive;
		BasePtr m_property;
	};

	void blobjectToProperty( const TypePtr & _type, AxeUtil::ArchiveRead & _archive, const BasePtr & _property );
}