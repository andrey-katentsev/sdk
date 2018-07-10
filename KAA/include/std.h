//
// File: std.h
// Description: C++ STD library helpers
// Created: May 19, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

namespace KAA
{
	/*template <class T>
	typename T::mapped_type& GetValue(T& container, const typename T::key_type& key)
	{
		const typename T::iterator i = container.find(key);
		return container.end() == i ? throw L"no mapped data" : i->second;
	}*/

	template <class T>
	typename const T::mapped_type& GetValue(const T& container, const typename T::key_type& key)
	{
		const typename T::const_iterator i = container.find(key);
		if(container.end() == i)
			throw L"no mapped data";
		else
			return i->second;
		//return ( container.end() == i ? throw(L"no mapped data") : i->second );
	}

	template <class T>
	typename const T::mapped_type& GetValue(const T& container, const typename T::key_type& key, bool& initialized, void (*initializer)(void))
	{
		if(initialized)
				return GetValue(container, key);
		else
		{
			(*initializer)();
			initialized = true;
			return GetValue(container, key);
		}
	}
}
