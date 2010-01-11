#	pragma once

#	include <vector>
#	include <map>
#	include <set>

namespace AxeUtil
{
	template<class TValue>
	class ForeachPoolMap
	{
		typedef std::vector<std::size_t> TVectorReference;
		typedef std::vector<TValue> TVectorValues;

		typedef std::set<std::size_t> TSetReference;
		typedef std::map<std::size_t, std::size_t> TMapReference;

	public:	
		typedef typename TVectorReference::iterator iterator;
		typedef typename TVectorReference::const_iterator const_iterator;

		iterator begin()
		{
			return m_current.begin();
		}

		const_iterator begin() const
		{
			return m_current.begin();
		}

		iterator end()
		{
			return m_current.end();
		}

		const_iterator end() const
		{
			return m_current.end();
		}

		void clear()
		{
			*this = ForeachPoolMap<TValue>();
		}

		bool empty() const
		{
			return m_current.empty();
		}

		typename TVectorValues::size_type value_size() const
		{
			return m_values.size();
		}

	public:
		TValue & operator [] ( std::size_t _index )
		{
			return m_values[_index];
		}

		const TValue & operator [] ( std::size_t _index ) const
		{
			return m_values[_index];
		}

	public:
		iterator find( std::size_t _index )
		{
			TMapReference::iterator it_found = m_currentMap.find( _index );

			if( it_found == m_currentMap.end() )
			{
				return m_current.end();
			}

			return m_current.begin() + it_found->second;
		}

		const_iterator find( std::size_t _index ) const
		{
			TMapReference::const_iterator it_found = m_currentMap.find( _index );

			if( it_found == m_currentMap.end() )
			{
				return m_current.end();
			}

			return m_current.begin() + it_found->second;
		}

		std::size_t prepare()
		{
			std::size_t pos = 0;

			if( m_free.empty() )
			{
				pos = m_values.size();
				m_values.resize( pos + 1 );
			}
			else
			{
				TSetReference::iterator it_free = m_free.begin();
				pos = *it_free;
				m_free.erase( it_free );
			}

			std::size_t refpos = m_current.size();
			m_currentMap.insert( std::make_pair( pos, refpos ) );
			m_current.push_back( pos );

			return pos;
		}

		void insert( std::size_t _index, const TValue & _value )
		{
			TMapReference::const_iterator it_current_find = m_currentMap.find( _index );

			if( it_current_find != m_currentMap.end() )
			{
				m_values[ _index ] = _value;
				return;
			}

			std::size_t valuesize = m_values.size();
			if( valuesize <= _index )
			{
				m_values.resize( _index + 1 );

				for( std::size_t 
					it = valuesize,
					it_end = _index; 
				it != it_end; 
				++it )
				{
					m_free.insert( it );
				}
			}
			else
			{
				m_free.erase( _index );
			}

			std::size_t currentpos = m_current.size();
			m_currentMap.insert( std::make_pair( _index, currentpos ) );
			m_current.push_back( _index );

			m_values[ _index ] = _value;
		}

		std::size_t insert( const TValue & _value )
		{
			std::size_t pos = prepare();

			m_values[ pos ] = _value;

			return pos;
		}

		iterator erase( iterator _it )
		{
			std::size_t index = *_it;

			std::size_t refpos = std::distance( m_current.begin(), _it );

			m_currentMap.erase( index );

			return erase( index, refpos );
		}

		iterator erase( std::size_t _index )
		{
			TMapReference::iterator it_found = m_currentMap.find( _index );

			if( it_found == m_currentMap.end() )
			{
				throw;
			}

			std::size_t refpos = it_found->second;

			m_currentMap.erase( it_found );

			return erase( _index, refpos );
		}

	protected:
		iterator erase( std::size_t _index, std::size_t _refpos )
		{
			m_values[ _index ] = TValue();

			m_free.insert( _index );

			std::size_t backpos = m_current.back();
			m_current.pop_back();

			if( _refpos == m_current.size() )
			{
				return m_current.end();
			}

			TMapReference::iterator it_refresh_found = m_currentMap.find( backpos );

			it_refresh_found->second = _refpos;
			m_current[_refpos] = backpos;

			return m_current.begin() + _refpos;
		}

	protected:
		TVectorReference m_current;

		TMapReference m_currentMap;
		TSetReference m_free;

		TVectorValues m_values;
	};
}