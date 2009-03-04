#	pragma once

#	include "Archive.hpp"

#	include "ConnectionCache.hpp"

namespace Axe
{
	class ArchiveRead
	{
	public:
		ArchiveRead( const ConnectionCachePtr & _connectionCache );

	public:
		void begin();

	public:
		template<class T>
		void read( T & _t )
		{
			*this >> _t;
		}

		template<class T>
		void readPOD( T & _t )
		{
			readBuffer( (void *)&_t, sizeof(T) );
		}

		void readBuffer( void * _begin, std::size_t _size );
		void readSize( std::size_t & _value );
		void readString( std::string & _value );

		const Archive::value_type * selectBuffer( std::size_t _size );

		Archive::value_type * keepBuffer( std::size_t _size );

		template<class T>
		T * keep()
		{
			return (T*)keepBuffer( sizeof(T) );
		}

	public:
		void clear();
		void seek( std::size_t _pos );
		std::size_t length( std::size_t _pos ) const;
		bool eof() const;

	public:
		const ConnectionCachePtr & getConnectionCache() const;

	protected:
		Archive m_archive;
		Archive::const_iterator m_seek;

		ConnectionCachePtr m_connectionCache;
	};

	void operator >> ( ArchiveRead & ar, std::string & _value );

	template<class T>
	void operator >> ( ArchiveRead & ar, T & _value )
	{
		ar.readPOD( _value );
	}
}