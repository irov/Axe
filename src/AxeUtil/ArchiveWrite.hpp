#	pragma once

#	include <AxeUtil/Archive.hpp>

#	include <string>

namespace AxeUtil
{
	class ArchiveWrite
	{
	public:
		void begin();

	public:
		template<class T>
		void write( const T & _value )
		{
			*this << _value;
		}

		template<class T>
		void writePOD( const T & _value )
		{
			writeBuffer( &_value,  &_value + 1 );
		}

		void writeSize( std::size_t _size );
		void writeString( const std::string & _value );
		void writeArchive( const AxeUtil::Archive::value_type * _buffer, std::size_t _size );

		Archive::iterator selectArchive( std::size_t _size );

	public:
		const Archive & getArchive() const;
	
		void swap( Archive & _ar );
		void clear();
		bool empty() const;

	protected:
		void writeBuffer( const void * _begin, const void * _end );

	protected:
		std::size_t m_begin;
		Archive m_archive;	
	};

	void operator << ( ArchiveWrite & ar, const std::string & _value );

	template<class T>
	void operator << ( ArchiveWrite & ar, const T & _value )
	{
		ar.writePOD( _value );
	}
}