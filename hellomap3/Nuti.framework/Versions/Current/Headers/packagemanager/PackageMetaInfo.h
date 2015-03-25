/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_PACKAGEMETAINFO_H_
#define _NUTI_PACKAGEMETAINFO_H_

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <cstdint>

namespace rapidjson {
	class CrtAllocator;
	template <typename BaseAllocator> class MemoryPoolAllocator;
	template<typename CharType> struct UTF8;
	template <typename Encoding, typename Allocator> class GenericValue;
	typedef GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator> > Value;
}

namespace Nuti {
    namespace PackageMetaInfoType {
        /**
         * Meta info type.
         */
        enum PackageMetaInfoType {
            /**
             * Null element.
             */
            PACKAGE_META_INFO_TYPE_NULL,
            /**
             * String element.
             */
            PACKAGE_META_INFO_TYPE_STRING,
            /**
             * Boolean element.
             */
            PACKAGE_META_INFO_TYPE_BOOL,
            /**
             * Integer element.
             */
            PACKAGE_META_INFO_TYPE_INTEGER,
            /**
             * Double-precision floating point element.
             */
            PACKAGE_META_INFO_TYPE_DOUBLE,
            /**
             * Array element.
             */
            PACKAGE_META_INFO_TYPE_ARRAY,
            /**
             * Map (dictionary) element.
             */
            PACKAGE_META_INFO_TYPE_MAP
        };
    }
    
	/**
	 * Package meta info element. Can contain JSON-style structured data, including objects and arrays.
	 */
	class PackageMetaInfo {
	public:
		/**
		 * Constructs a new PackageMetaInfo object from existing JSON value.
		 * @param jsonValue The JSON representation to use as a base for this meta info element. The value is reset after construction.
		 */
		explicit PackageMetaInfo(const std::string& jsonValue);

		/**
		 * Constructs a new PackageMetaInfo object from existing RapidJSON value.
		 * @param value The RapidJSON object to use as a base for this meta info element. The value is reset after construction.
		 */
		explicit PackageMetaInfo(const rapidjson::Value& value);

		/**
		 * Returns the underlying JSON value.
		 * @return The value of the element.
		 */
		const std::string& getJsonValue() const { return _jsonValue; }

		/**
		 * Returns the type of this meta info element.
		 * @return The type of this element.
		 */
		PackageMetaInfoType::PackageMetaInfoType getType() const;

		/**
		 * Returns the string value of this element.
		 * @return The string value of the element. If the element is not string, empty string will be returned.
		 */
		std::string getString() const;
		/**
		 * Returns the boolean value of this element.
		 * @return The boolean value of the element. If the element is not boolean, false will be returned.
		 */
		bool getBool() const;
		/**
		 * Returns the integer value of this element.
		 * @return The integer value of the element. If the element is not integer, 0 will be returned.
		 */
		long long getLong() const;
		/**
		 * Returns the floating point value of this element.
		 * @return The floating point value of the element. If the element is integer, it will be converted to floating point. Otherwise 0.0 is be returned.
		 */
		double getDouble() const;

		/**
		 * Returns the number of elements in the array.
		 * @return The number of elements in the array if the element is of array type. Otherwise 0 is returned.
		 */
		int getArraySize() const;
		/**
		 * Returns the element of array at specified position.
		 * @param idx The index of the array element to return (starting from 0).
		 * @return The array element at specified position or null if the element does not exist.
		 */
		std::shared_ptr<PackageMetaInfo> getArrayElement(int idx) const;

		/**
		 * Returns all the keys in the map.
		 * @return The list containing all the keys of the map if the element is of map type. Otherwise empty list is returned.
		 */
		std::vector<std::string> getMapKeys() const;
		/**
		 * Returns the element of map with the specified key.
		 * @param key The key of the map element to return.
		 * @return The map element with the specified key or null if the element does not exist.
		 */
		std::shared_ptr<PackageMetaInfo> getMapElement(const std::string& key) const;

	private:
		std::string _jsonValue;
		std::shared_ptr<rapidjson::Value> _value;
	};

}

#endif
