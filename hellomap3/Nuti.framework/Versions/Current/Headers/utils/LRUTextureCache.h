#ifndef LRUTEXTURECACHE_H_
#define LRUTEXTURECACHE_H_

#include "graphics/Bitmap.h"
#include "graphics/Texture.h"
#include "utils/Log.h"

#include <cmath>
#include <list>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Nuti {
    
namespace CacheResult {
    enum CacheResult {
        CACHE_RESULT_DOESNT_EXIST,
        CACHE_RESULT_EXISTS_NOT_READY,
        CACHE_RESULT_EXISTS};
};

class Bitmap;

template <typename T>
class LRUTextureCache {
public:
	class CacheKeyInfo {
	public:
		CacheKeyInfo(T id, int sizeInBytes, bool genMipmaps, bool repeat);

		T getId() const;
		int getSizeInBytes() const;
		bool getGenMipmaps() const;
		bool getRepeat() const;

	private:
		T _id;
		int _sizeInBytes;
		bool _genMipmaps;
		bool _repeat;

	};

	LRUTextureCache();
	LRUTextureCache(unsigned int capacityInBytes);
	virtual ~LRUTextureCache();
    
	unsigned int getCapacity() const;
	void setCapacity(unsigned int capacityInBytes);
    
    unsigned int getUncreatedTextureCount() const;

	int createAndDeleteTextures(int maxCreateCount);

	void recreateAllTextures();

    CacheResult::CacheResult exists(const T& id);
    CacheResult::CacheResult existsNoMod(const T& id) const;
    
	const Texture* get(const T& id);
	const Texture* getNoMod(const T& id) const;
    std::list<CacheKeyInfo> getKeyInfos() const;

	void invalidate(const T& id);
    void invalidateAll();
    bool isValid(const T& id) const;
    
	void remove(const T& id, bool destroyTexture);
	void removeAll(bool destroyTextures);
    
    void store(const T& id, const std::shared_ptr<Bitmap>& bitmap, bool genMipmaps, bool repeat);
    void store(const T& id, const std::shared_ptr<Texture>& texture);

private:
	struct CacheElement {
        CacheElement();
		CacheElement(T id, const std::shared_ptr<Bitmap>& bitmap, bool genMipmaps, bool repeat);
        CacheElement(T id, const std::shared_ptr<Texture>& texture);

		T _id;

		std::shared_ptr<Bitmap> _bitmap;
		int _sizeInBytes;

		std::shared_ptr<Texture> _texture;

        bool _genMipmaps;
		bool _repeat;
	};

	typedef std::list<CacheElement> CacheElementList;
	typedef std::unordered_map<T, typename CacheElementList::iterator> CacheElementItMap;
    typedef std::unordered_set<T> KeySet;
    
	void removeOldestElements();

	static const float MIPMAP_SIZE_MULTIPLIER;

	unsigned int _capacityInBytes;
	unsigned int _sizeInBytes;

	CacheElementList _lruElements;
	CacheElementItMap _mappedElements;
	CacheElementList _addedElements;
    CacheElementList _removedElements;
    KeySet _invalidatedElements;

	mutable std::mutex _mutex;
};

template <typename T>
LRUTextureCache<T>::CacheKeyInfo::CacheKeyInfo(T id, int sizeInBytes, bool genMipmaps, bool repeat) :
	_id(id),
	_sizeInBytes(sizeInBytes),
	_genMipmaps(genMipmaps),
	_repeat(repeat)
{
}

template <typename T>
T LRUTextureCache<T>::CacheKeyInfo::getId() const {
	return _id;
}

template <typename T>
int LRUTextureCache<T>::CacheKeyInfo::getSizeInBytes() const {
	return _sizeInBytes;
}

template <typename T>
bool LRUTextureCache<T>::CacheKeyInfo::getGenMipmaps() const {
	return _genMipmaps;
}

template <typename T>
bool LRUTextureCache<T>::CacheKeyInfo::getRepeat() const {
	return _repeat;
}

template <typename T>
LRUTextureCache<T>::LRUTextureCache() :
	_capacityInBytes(0),
	_sizeInBytes(0),
	_lruElements(),
	_mappedElements(),
	_addedElements(),
    _removedElements(),
    _invalidatedElements(),
	_mutex()
{
}

template <typename T>
LRUTextureCache<T>::LRUTextureCache(unsigned int capacityInBytes) :
	_capacityInBytes(capacityInBytes),
	_sizeInBytes(0),
	_lruElements(),
	_mappedElements(),
	_addedElements(),
    _removedElements(),
    _invalidatedElements(),
	_mutex()
{
}

template <typename T>
LRUTextureCache<T>::~LRUTextureCache() {
}

template <typename T>
unsigned int LRUTextureCache<T>::getCapacity() const {
	std::lock_guard<std::mutex> lock(_mutex);
	return _capacityInBytes;
}

template <typename T>
void LRUTextureCache<T>::setCapacity(unsigned int capacityInBytes) {
	std::lock_guard<std::mutex> lock(_mutex);
	_capacityInBytes = capacityInBytes;
}
    
template <typename T>
unsigned int LRUTextureCache<T>::getUncreatedTextureCount() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _addedElements.size();
}

template <typename T>
int LRUTextureCache<T>::createAndDeleteTextures(int maxCreateCount) {
	std::lock_guard<std::mutex> lock(_mutex);

	// Load some bitmaps in the creation queue as opengl textures
	int createdCount = 0;
	for (typename CacheElementList::iterator it = _addedElements.begin(); it != _addedElements.end();) {
		CacheElement element = *it;

		// Create the texture
		element._texture.reset(new Texture(*element._bitmap, element._genMipmaps, element._repeat));
		element._bitmap.reset();

		// Move element from addedElements to lruElements
        it = _addedElements.erase(it);
        typename CacheElementItMap::iterator it2 = _mappedElements.find(element._id);
        if (it2 != _mappedElements.end()) {
            // If the element already exists in the map as a texture
            
            // Subtract the old size
            const CacheElement& oldElement = *it2->second;
            _sizeInBytes -= oldElement._sizeInBytes;
            
            // Add the old element to the remove que
            _removedElements.push_back(oldElement);
            
            // Add new element to the end of the que
            _lruElements.erase(it2->second);
            _lruElements.push_back(element);
            it2->second = --_lruElements.end();
        } else {
            // If the element does not exist in the map as a texture, add it as a last element
            _lruElements.push_back(element);
            _mappedElements[element._id] = --_lruElements.end();
        }

		_sizeInBytes += element._sizeInBytes;

		removeOldestElements();

		createdCount++;
		if (createdCount >= maxCreateCount) {
            break;
		}
	}

    for (CacheElement& element : _removedElements) {
        // Free the texture
		element._texture->unload();
		element._texture.reset();
    }
    _removedElements.clear();

	return createdCount;
}

template <typename T>
CacheResult::CacheResult LRUTextureCache<T>::exists(const T& id) {
	std::lock_guard<std::mutex> lock(_mutex);

	// Check if the tile is cached, move the tile to the front of the cache
	typename CacheElementItMap::const_iterator it = _mappedElements.find(id);
	if (it == _mappedElements.end()) {
		// If tile is not in the cache map check the creation queue
		typename CacheElementList::const_iterator it2;
		for (it2 = _addedElements.begin(); it2 != _addedElements.end(); ++it2) {
            const CacheElement& element = *it2;
			if (element._id == id) {
				return CacheResult::CACHE_RESULT_EXISTS_NOT_READY;
			}
		}
		return CacheResult::CACHE_RESULT_DOESNT_EXIST;
	} else {
		// Move the element to the front of the cache list
		CacheElement element(*it->second);
        _lruElements.erase(it->second);
        _lruElements.push_back(element);

		// Update the iterator in the map
		_mappedElements[id] = --_lruElements.end();
		return CacheResult::CACHE_RESULT_EXISTS;
	}
}

template <typename T>
CacheResult::CacheResult LRUTextureCache<T>::existsNoMod(const T& id) const {
	std::lock_guard<std::mutex> lock(_mutex);

	// Check if the tile is cached, move the tile to the front of the cache
	typename CacheElementItMap::const_iterator it = _mappedElements.find(id);
	if (it == _mappedElements.end()) {
		// If tile is not in the cache map check the creation queue
		typename CacheElementList::const_iterator it2;
		for (it2 = _addedElements.begin(); it2 != _addedElements.end(); ++it2) {
            const CacheElement& element = *it2;
			if (element._id == id) {
				return CacheResult::CACHE_RESULT_EXISTS_NOT_READY;
			}
		}
		return CacheResult::CACHE_RESULT_DOESNT_EXIST;
	} else {
		return CacheResult::CACHE_RESULT_EXISTS;
	}
}

template <typename T>
const Texture* LRUTextureCache<T>::get(const T& id) {
	std::lock_guard<std::mutex> lock(_mutex);

	// Return the texture, while modifying the cache order
	typename CacheElementItMap::const_iterator it = _mappedElements.find(id);
	if (it == _mappedElements.end()) {
		return nullptr;
	} else {
        // Move the element to the front of the cache list
        CacheElement element(*it->second);
        _lruElements.erase(it->second);
        _lruElements.push_back(element);

		// Update the iterator in the map
		_mappedElements[id] = --_lruElements.end();

		return _lruElements.back()._texture.get();
	}
}

template <typename T>
const Texture* LRUTextureCache<T>::getNoMod(const T& id) const {
	std::lock_guard<std::mutex> lock(_mutex);

	// Return the tile texture, without modifying the cache order
	typename CacheElementItMap::const_iterator it = _mappedElements.find(id);
	if (it == _mappedElements.end()) {
		return nullptr;
	} else {
		CacheElement& element = *it->second;
		return element._texture.get();
	}
}
    
template <typename T>
std::list<typename LRUTextureCache<T>::CacheKeyInfo> LRUTextureCache<T>::getKeyInfos() const {
    std::list<CacheKeyInfo> keyInfos;
    for (auto it = _lruElements.begin(); it != _lruElements.end(); ++it) {
    	const CacheElement& element = *it;
    	keyInfos.emplace_back(element._id, element._sizeInBytes, element._genMipmaps, element._repeat);
    }
    return keyInfos;
}

template <typename T>
void LRUTextureCache<T>::invalidate(const T& id) {
    std::lock_guard<std::mutex> lock(_mutex);

    _invalidatedElements.insert(id);
}

template <typename T>
void LRUTextureCache<T>::invalidateAll() {
    std::lock_guard<std::mutex> lock(_mutex);

    for (const CacheElement& element : _lruElements) {
        _invalidatedElements.insert(element._id);
    }
    
    for (const CacheElement& element : _addedElements) {
        _invalidatedElements.insert(element._id);
    }
}

template <typename T>
bool LRUTextureCache<T>::isValid(const T& id) const {
    std::lock_guard<std::mutex> lock(_mutex);

    if (_invalidatedElements.find(id) == _invalidatedElements.end()) {
        return true;
    }
    return false;
}

template <typename T>
void LRUTextureCache<T>::remove(const T& id, bool destroyTexture) {
    std::lock_guard<std::mutex> lock(_mutex);

    typename CacheElementItMap::const_iterator it = _mappedElements.find(id);
	if (it == _mappedElements.end()) {
		typename CacheElementList::iterator it2;
		for (it2 = _addedElements.begin(); it2 != _addedElements.end(); ++it2) {
            const CacheElement& element = *it2;
			if (element._id == id) {
                _invalidatedElements.erase(element._id);
				_addedElements.erase(it2);
                return;
			}
		}
	} else {
		CacheElement& element = *it->second;

        if (destroyTexture) {
            // Add the element to deletion map
            _removedElements.push_back(element);
        }

        // Reduce the size
		_sizeInBytes -= element._sizeInBytes;

		// Remove the element from cache
        _invalidatedElements.erase(element._id);
		_lruElements.erase(it->second);
		_mappedElements.erase(it);
    }
}

template <typename T>
void LRUTextureCache<T>::removeAll(bool destroyTextures) {
    std::lock_guard<std::mutex> lock(_mutex);

    if (destroyTextures) {
		for (typename CacheElementList::iterator it = _lruElements.begin(); it !=  _lruElements.end(); ++it) {
			CacheElement element = *it;

			// Add the element to deletion map
			_removedElements.push_back(element);
		}
    }
    _lruElements.clear();
	_mappedElements.clear();
    _addedElements.clear();
    _invalidatedElements.clear();
    _sizeInBytes = 0;
}

template <typename T>
void LRUTextureCache<T>::store(const T& id, const std::shared_ptr<Bitmap>& bitmap, bool genMipmaps, bool repeat) {
	std::lock_guard<std::mutex> lock(_mutex);
    typename CacheElementList::iterator it;
    for (it = _addedElements.begin(); it != _addedElements.end(); ++it) {
        CacheElement& element = *it;
        if (element._id == id) {
            element._bitmap = bitmap;
            element._genMipmaps = genMipmaps;
            element._repeat = repeat;
            _invalidatedElements.erase(element._id);
            return;
        }
    }

	_addedElements.push_back(CacheElement(id, bitmap, genMipmaps, repeat));
    _invalidatedElements.erase(id);
}
    
template <typename T>
void LRUTextureCache<T>::store(const T& id, const std::shared_ptr<Texture>& texture) {
    std::lock_guard<std::mutex> lock(_mutex);
    // If the element already exists, but has not yet been loaded as a texture, remove it from the added que
    typename CacheElementList::iterator it;
    for (it = _addedElements.begin(); it != _addedElements.end(); ++it) {
        const CacheElement& element = *it;
        if (element._id == id) {
            _addedElements.erase(it);
            break;
        }
    }
    
    // Check if the element already exists
    typename CacheElementItMap::iterator it2 = _mappedElements.find(id);
	if (it2 != _mappedElements.end()) {
        // If the element already exists in the map as a texture
        
        // Subtract the old size
        const CacheElement& element = *it2->second;
        _sizeInBytes -= element._sizeInBytes;
        
        // Add the old element to the remove que
        _removedElements.push_back(element);
        
        // Add new element to the end of the que
        _lruElements.erase(it2->second);
        _lruElements.push_back(CacheElement(id, texture));
        it2->second = --_lruElements.end();
    } else {
        // If the element does not exist in the map as a texture, add it as a last element
        _lruElements.push_back(CacheElement(id, texture));
        _mappedElements[id] = --_lruElements.end();
    }
    _sizeInBytes += texture->getSize();

    _invalidatedElements.erase(id);
    
    removeOldestElements();
}

template <typename T>
LRUTextureCache<T>::CacheElement::CacheElement() :
		_id(),
		_bitmap(),
		_sizeInBytes(0),
		_texture(),
        _genMipmaps(false),
		_repeat(false)
{
}

template <typename T>
LRUTextureCache<T>::CacheElement::CacheElement(T id, const std::shared_ptr<Bitmap>& bitmap, bool genMipmaps, bool repeat) :
		_id(id),
		_bitmap(bitmap),
		_sizeInBytes(static_cast<int>(std::ceil(_bitmap->getWidth() * _bitmap->getHeight()
                                                * _bitmap->getBytesPerPixel() * (genMipmaps ? MIPMAP_SIZE_MULTIPLIER : 1)))),
		_texture(),
        _genMipmaps(genMipmaps),
		_repeat(repeat)
{
}
    
template <typename T>
LRUTextureCache<T>::CacheElement::CacheElement(T id, const std::shared_ptr<Texture>& texture) :
    _id(id),
    _bitmap(),
    _sizeInBytes(texture->getSize()),
    _texture(texture),
    _genMipmaps(texture->isMipmaps()),
    _repeat(texture->isRepeat())
{
}

template <typename T>
void LRUTextureCache<T>::removeOldestElements() {
	// Add oldest entries to the eviction map, until the cache is within the size limit
	for (typename CacheElementList::iterator it = _lruElements.begin(); it !=  _lruElements.end();) {
		if (_sizeInBytes < _capacityInBytes) {
			break;
		}
		CacheElement& element = *it;

        // Add the element to deletion map
        _removedElements.push_back(element);

        // Reduce the size
		_sizeInBytes -= element._sizeInBytes;

		// Remove the element from cache
        _invalidatedElements.erase(element._id);
		typename CacheElementItMap::iterator it2 = _mappedElements.find(element._id);
		it = _lruElements.erase(it2->second);
		_mappedElements.erase(it2);
	}
}

template <typename T>
const float LRUTextureCache<T>::MIPMAP_SIZE_MULTIPLIER = 1.33f;
    
}

#endif
