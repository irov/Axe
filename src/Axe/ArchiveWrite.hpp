#	pragma once

#	include <vector>
#	include <string>

namespace Axe
{
	typedef std::vector<char> TBlobject;

	class ArchiveWrite
	{
	public:
		ArchiveWrite( TBlobject & _blob );

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
		TBlobject & m_blob;	
	};

	template<class T>
	void operator << ( ArchiveWrite & ar, const T & _value )
	{
		ar.write_t( _value );
	}
}