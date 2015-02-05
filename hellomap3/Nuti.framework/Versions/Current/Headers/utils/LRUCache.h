/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_LRUCACHE_H_
#define _NUTI_LRUCACHE_H_

#include <deque>
#include <list>
#include <mutex>
#include <chrono>
#include <unordered_map>
#include <unordered_set>

namespace Nuti {

    template <typename K, typename V>
    class LRUCache {
    public:
        LRUCache();
        LRUCache(unsigned int capacity);
        virtual ~LRUCache();
    
        unsigned int getCapacity() const;
        void setCapacity(unsigned int capacity);
    
        bool exists(const K& id);
        bool existsNoMod(const K& id) const;
        const V get(const K& id);
        const V getNoMod(const K& id) const;
        bool get(const K& id, V& value);
        bool getNoMod(const K& id, V& value) const;
    
		void invalidate(const K& id, std::chrono::system_clock::time_point expirationTime = std::chrono::system_clock::now());
        void invalidateAll();
        bool isValid(const K& id) const;
        
        void remove(const K& id);
        void removeAll();
        
        void store(const K& id, const V& data);
        void store(const K& id, const V& data, unsigned int size);
    
    private:
        struct CacheElement {
            CacheElement(const K& id, const V& data, unsigned int size);
            K _id;
            V _data;
            unsigned int _size;
        };
    
        typedef std::list<CacheElement> CacheElementList;
        typedef std::unordered_map<K, typename CacheElementList::iterator> CacheElementItMap;
        typedef std::unordered_map<K, std::chrono::system_clock::time_point> CacheExpirationMap;
    
        void removeOldestElements();
    
        unsigned int _capacity;
        unsigned int _size;
    
        CacheElementList _lruElements;
        CacheElementItMap _mappedElements;
        CacheExpirationMap _invalidatedElements;
    
        mutable std::mutex _mutex;
    };
    
    template <typename K, typename V>
    LRUCache<K, V>::LRUCache() :
        _capacity(0),
        _size(0),
        _lruElements(),
        _mappedElements(),
        _invalidatedElements(),
        _mutex()
    {
    }
    
    template <typename K, typename V>
    LRUCache<K, V>::LRUCache(unsigned int capacity) :
        _capacity(capacity),
        _size(0),
        _lruElements(),
        _mappedElements(),
        _invalidatedElements(),
        _mutex()
    {
    }
    
    template <typename K, typename V>
    LRUCache<K, V>::~LRUCache() {
    }
    
    template <typename K, typename V>
    unsigned int LRUCache<K, V>::getCapacity() const {
        std::lock_guard<std::mutex> lock(_mutex);
        return _capacity;
    }
    
    template <typename K, typename V>
    void LRUCache<K, V>::setCapacity(unsigned int capacity) {
        std::lock_guard<std::mutex> lock(_mutex);
        _capacity = capacity;
    }
    
    template <typename K, typename V>
    bool LRUCache<K, V>::exists(const K& id) {
        std::lock_guard<std::mutex> lock(_mutex);
    
        typename CacheElementItMap::const_iterator it = _mappedElements.find(id);
        if (it == _mappedElements.end()) {
            return false;
        } else {
            // Move the element to the back of the cache list
            CacheElement element(*it->second);
            _lruElements.erase(it->second);
            _lruElements.push_back(element);
    
            // Update the iterator in the map
            _mappedElements[id] = --_lruElements.end();
    
            return true;
        }
    }
    
    template <typename K, typename V>
    bool LRUCache<K, V>::existsNoMod(const K& id) const {
        std::lock_guard<std::mutex> lock(_mutex);
    
        typename CacheElementItMap::const_iterator it = _mappedElements.find(id);
        return it != _mappedElements.end();
    }
    
    template <typename K, typename V>
    const V LRUCache<K, V>::get(const K& id) {
        std::lock_guard<std::mutex> lock(_mutex);
    
        typename CacheElementItMap::const_iterator it = _mappedElements.find(id);
        if (it == _mappedElements.end()) {
            return V();
        } else {
            // Move the element to the back of the cache list
            CacheElement element(*it->second);
            _lruElements.erase(it->second);
            _lruElements.push_back(element);
    
            // Update the iterator in the map
            _mappedElements[id] = --_lruElements.end();
            return element._data;
        }
    }
    
    template <typename K, typename V>
    const V LRUCache<K, V>::getNoMod(const K& id) const {
        std::lock_guard<std::mutex> lock(_mutex);
    
        typename CacheElementItMap::const_iterator it = _mappedElements.find(id);
        if (it == _mappedElements.end()) {
            return V();
        } else {
            CacheElement& element = *it->second;
            return element._data;
        }
    }
    
    template <typename K, typename V>
    bool LRUCache<K, V>::get(const K& id, V& value) {
        std::lock_guard<std::mutex> lock(_mutex);
            
        typename CacheElementItMap::const_iterator it = _mappedElements.find(id);
        if (it == _mappedElements.end()) {
            return false;
        } else {
            // Move the element to the back of the cache list
            CacheElement element(*it->second);
            _lruElements.erase(it->second);
            _lruElements.push_back(element);
                
            // Update the iterator in the map
            _mappedElements[id] = --_lruElements.end();
            value = element._data;
            return true;
        }
    }
    
    template <typename K, typename V>
    bool LRUCache<K, V>::getNoMod(const K& id, V& value) const {
        std::lock_guard<std::mutex> lock(_mutex);
            
        typename CacheElementItMap::const_iterator it = _mappedElements.find(id);
        if (it == _mappedElements.end()) {
            return false;
        } else {
            CacheElement& element = *it->second;
            value = element._data;
            return true;
        }
    }
        
    
    template <typename K, typename V>
	void LRUCache<K, V>::invalidate(const K& id, std::chrono::system_clock::time_point expirationTime) {
        std::lock_guard<std::mutex> lock(_mutex);
    
		_invalidatedElements[id] = expirationTime;
    }
    
    template <typename K, typename V>
    void LRUCache<K, V>::invalidateAll() {
        std::lock_guard<std::mutex> lock(_mutex);
		
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        for (const CacheElement& element : _lruElements) {
            _invalidatedElements[element._id] = now;
        }
    }
    
    template <typename K, typename V>
    bool LRUCache<K, V>::isValid(const K& id) const {
        std::lock_guard<std::mutex> lock(_mutex);
		
		auto it = _invalidatedElements.find(id);
        if (it != _invalidatedElements.end()) {
            return it->second > std::chrono::system_clock::now();
        }
        return true;
    }
    
    template <typename K, typename V>
    void LRUCache<K, V>::remove(const K& id) {
        // If found remove the element from cache
        std::lock_guard<std::mutex> lock(_mutex);
    
        typename CacheElementItMap::iterator it = _mappedElements.find(id);
        if (it == _mappedElements.end()) {
            return;
        }
        
        const CacheElement& element = *it->second;
        _size -= element._size;
    
        _lruElements.erase(it->second);
        _mappedElements.erase(it);
        _invalidatedElements.erase(id);
    }
    
    template <typename K, typename V>
    void LRUCache<K, V>::removeAll() {
        std::lock_guard<std::mutex> lock(_mutex);
        _lruElements.clear();
        _mappedElements.clear();
        _invalidatedElements.clear();
        _size = 0;
    }
        
    template <typename K, typename V>
    void LRUCache<K, V>::store(const K& id, const V& data) {
        store(id, data, 1);
    }
        
    template <typename K, typename V>
    void LRUCache<K, V>::store(const K& id, const V& data, unsigned int size) {
        std::lock_guard<std::mutex> lock(_mutex);
        
        typename CacheElementItMap::iterator it = _mappedElements.find(id);
        if (it != _mappedElements.end()) {
            CacheElement& element = *it->second;
            _size -= element._size;
            _lruElements.erase(it->second);
            _lruElements.push_back(CacheElement(id, data, size));
            it->second = --_lruElements.end();
        } else {
            _lruElements.push_back(CacheElement(id, data, size));
            _mappedElements[id] = --_lruElements.end();
        }
        
        _size += size;
        _invalidatedElements.erase(id);
        
        removeOldestElements();
    }
    
    template <typename K, typename V>
    LRUCache<K, V>::CacheElement::CacheElement(const K& id, const V& data, unsigned int size) :
        _id(id),
        _data(data),
        _size(size)
    {
    }
    
    template <typename K, typename V>
    void LRUCache<K, V>::removeOldestElements() {
        // Add oldest entries to the eviction map, until the cache is within the size limit
        typename CacheElementList::iterator it;
        for (it = _lruElements.begin(); it !=  _lruElements.end(); ) {
            if (_size < _capacity) {
                break;
            }
            CacheElement& element = *it;
            _size -= element._size;
    
            // Remove the cache element from cache
            typename CacheElementItMap::iterator it2 = _mappedElements.find(element._id);
            it = _lruElements.erase(it2->second);
            _mappedElements.erase(it2);
            _invalidatedElements.erase(element._id);
        }
    }
        
}

#endif
