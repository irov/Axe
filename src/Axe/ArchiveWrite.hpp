#	pragma once

#	include "Archive.hpp"

#	include <string>

namespace Axe
{
	class ArchiveWrite
	{
	public:
		ArchiveWrite( Archive & _archive );

	public:
		template<class T>
		void write_t( const T & _value )
		{
			writeBuffer( &_value,  &_value + 1 );
		}

		void writeSize( std::size_t _size );
		void writeString( const std::string & _value );

	protected:
		void writeBuffer( const void * _begin, const void * _end );

	protected:
		std::size_t m_begin;
		Archive & m_archive;	
	};

	void operator << ( ArchiveWrite & ar, const std::string & _value );

	template<class T>
	void operator << ( ArchiveWrite & ar, const T & _value )
	{
		ar.write_t( _value );
	}
}