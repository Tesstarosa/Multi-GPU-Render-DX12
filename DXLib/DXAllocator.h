#pragma once

#include "STLCustomAllocator.h"

class DXAllocator
{
	static LinearAllocationStrategy<> allocatorStrategy;
	
public:
	template<typename T>
	CustomAllocator<T> static GetAllocator()
	{
		CustomAllocator <T> allocator( allocatorStrategy );

		return allocator;
	}

	template<typename T>
	custom_vector<T> static CreateVector()
	{
		return custom_vector<T>(GetAllocator<T>());
	}

	template<typename T>
	custom_list<T> static CreateList()
	{
		return custom_list<T>{GetAllocator<T>()};
	}

	template<typename K, typename V>
	custom_map<K, V> static CreateMap()
	{
		return custom_map<K, V>(GetAllocator<std::pair<K, V>>());
	}

	template<typename K, typename V>
	custom_unordered_map<K, V> static CreateUnorderedMap()
	{
		return custom_unordered_map<K, V>(GetAllocator<std::pair<K, V>>());
	}

	template<typename T>
	custom_set<T> static CreateSet()
	{
		return custom_set<T>(GetAllocator<T>());
	}

	template<typename T>
	custom_unordered_set<T> static CreateUnorderedSet()
	{
		return custom_unordered_set<T>(GetAllocator<T>());
	}

	custom_string static CreateString()
	{
		return custom_string( GetAllocator<char>() );
	}

	custom_wstring static CreateWString()
	{
		return custom_wstring( GetAllocator<wchar_t>() );
	}

	
	template<typename T, typename... Args>
	custom_unique_ptr<T> make_custom_unique(Args&&... args)
	{
		return make_custom_unique<T>(GetAllocator<T>(), args);
	}
};

