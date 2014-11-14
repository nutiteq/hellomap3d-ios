#ifndef TEXTURECACHE_H_
#define TEXTURECACHE_H_

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

class Bitmap;

template <typename T>
class TextureCache {
public:
	TextureCache();
	virtual ~TextureCache();
    
    unsigned int getUncreatedTextureCount() const;

	int createAndDeleteTextures(int maxCreateCount);

    CacheResult::CacheResult exists(const T& id) const;
    
	const Texture* get(const T& id) const;
    std::unordered_set<T> getKeys() const;

	void invalidate(const T& id);
    void invalidateAll();
    bool isValid(const T& id) const;
    
	void remove(const T& id, bool destroyTexture);
	void removeAll(bool destroyTexture);
    
    void store(const T& id, const std::shared_ptr<Bitmap>& bitmap, bool genMipmaps, bool repeat);
    void store(const T& id, const std::shared_ptr<Texture>& texture);

private:
	struct CacheElement {
        CacheElement();
		CacheElement(T id, const std::shared_ptr<Bitmap>& bitmap, bool genMipmaps, bool repeat);
        CacheElement(T id, const std::shared_ptr<Texture>& texture);

		T _id;

		std::shared_ptr<Bitmap> _bitmap;
		std::shared_ptr<Texture> _texture;

        bool _genMipmaps;
		bool _repeat;
	};

	typedef std::list<CacheElement> CacheElementList;
    typedef std::unordered_map<T, CacheElement> CacheElementMap;
    typedef std::unordered_set<T> KeySet;
    
	void removeOldestElements();

	static const float MIPMAP_SIZE_MULTIPLIER;

	CacheElementMap _mappedElements;
	CacheElementList _addedElements;
    CacheElementList _removedElements;
    KeySet _invalidatedElements;

	mutable std::mutex _mutex;
};

template <typename T>
    TextureCache<T>::TextureCache() :
	_mappedElements(),
	_addedElements(),
    _removedElements(),
    _invalidatedElements(),
	_mutex()
{
}

template <typename T>
TextureCache<T>::~TextureCache() {
}
    
template <typename T>
unsigned int TextureCache<T>::getUncreatedTextureCount() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _addedElements.size();
}

template <typename T>
int TextureCache<T>::createAndDeleteTextures(int maxCreateCount) {
	std::lock_guard<std::mutex> lock(_mutex);

	// Load some bitmaps in the creation queue as opengl textures
	int createdCount = 0;
	for (typename CacheElementList::iterator it = _addedElements.begin(); it != _addedElements.end();) {
		CacheElement element = *it;

		// Create the texture
		element._texture.reset(new Texture(*element._bitmap, element._genMipmaps, element._repeat));
		element._bitmap.reset();

		// Move element from _addedElements to _mappedElements
        it = _addedElements.erase(it);
        typename CacheElementMap::iterator it2 = _mappedElements.find(element._id);
        if (it2 != _mappedElements.end()) {
            // If the element already exists in the map as a texture
            const CacheElement& oldElement = it2->second;
            
            // Add the old element to the remove que
            _removedElements.push_back(oldElement);
            
            // Add new element to the map
            it2->second = element;
        } else {
            // If the element does not exist in the map as a texture, add it
            _mappedElements[element._id] = element;
        }

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
CacheResult::CacheResult TextureCache<T>::exists(const T& id) const {
	std::lock_guard<std::mutex> lock(_mutex);

	// Check if the tile is cached, move the tile to the front of the cache
	typename CacheElementMap::const_iterator it = _mappedElements.find(id);
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
const Texture* TextureCache<T>::get(const T& id) const {
	std::lock_guard<std::mutex> lock(_mutex);

	// Return the tile texture, without modifying the cache order
	typename CacheElementMap::const_iterator it = _mappedElements.find(id);
	if (it == _mappedElements.end()) {
		return nullptr;
	} else {
		const CacheElement& element = it->second;
		return element._texture.get();
	}
}
    
template <typename T>
std::unordered_set<T> TextureCache<T>::getKeys() const {
    std::unordered_set<T> keys;
    for (typename CacheElementMap::const_iterator it = _mappedElements.begin(); it !=  _mappedElements.end(); ++it) {
        keys.insert(it->first);
    }
    return keys;
}

template <typename T>
void TextureCache<T>::invalidate(const T& id) {
    std::lock_guard<std::mutex> lock(_mutex);
    _invalidatedElements.insert(id);
}

template <typename T>
void TextureCache<T>::invalidateAll() {
    std::lock_guard<std::mutex> lock(_mutex);

    for (const auto& pair : _mappedElements) {
        const CacheElement& element = pair.second;
        _invalidatedElements.insert(element._id);
    }

    for (const CacheElement& element : _addedElements) {
        _invalidatedElements.insert(element._id);
    }
}

template <typename T>
bool TextureCache<T>::isValid(const T& id) const {
    std::lock_guard<std::mutex> lock(_mutex);

    if (_invalidatedElements.find(id) == _invalidatedElements.end()) {
        return true;
    }
    return false;
}

template <typename T>
void TextureCache<T>::remove(const T& id, bool destroyTexture) {
    std::lock_guard<std::mutex> lock(_mutex);

    typename CacheElementMap::const_iterator it = _mappedElements.find(id);
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
		const CacheElement& element = it->second;

        if (destroyTexture) {
            // Add the element to deletion map
            _removedElements.push_back(element);
        }

		// Remove the element from cache
        _invalidatedElements.erase(element._id);
		_mappedElements.erase(it);
    }
}

template <typename T>
void TextureCache<T>::removeAll(bool destroyTexture) {
    std::lock_guard<std::mutex> lock(_mutex);
    
    if (destroyTexture) {
		for (typename CacheElementMap::const_iterator it = _mappedElements.begin(); it !=  _mappedElements.end(); ++it) {
			const CacheElement& element = it->second;

			// Add the element to deletion map
			_removedElements.push_back(element);
		}
    }
   
	_mappedElements.clear();
    _addedElements.clear();
    _invalidatedElements.clear();
}

template <typename T>
void TextureCache<T>::store(const T& id, const std::shared_ptr<Bitmap>& bitmap, bool genMipmaps, bool repeat) {
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
void TextureCache<T>::store(const T& id, const std::shared_ptr<Texture>& texture) {
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
    
    // Check if the element already exists in the map
    typename CacheElementMap::iterator it2 = _mappedElements.find(id);
	if (it2 != _mappedElements.end()) {
        const CacheElement& element = it2->second;
        
        // Add the old element to deletion map
        _removedElements.push_back(element);
        
        // Add new element to the map
        it2->second = CacheElement(id, texture);
    } else {
        // If the element does not exist in the map as a texture, add it
        _mappedElements[id] = CacheElement(id, texture);
    }

    _invalidatedElements.erase(id);
}

template <typename T>
TextureCache<T>::CacheElement::CacheElement() :
		_id(),
		_bitmap(),
		_texture(),
        _genMipmaps(false),
		_repeat(false)
{
}

template <typename T>
TextureCache<T>::CacheElement::CacheElement(T id, const std::shared_ptr<Bitmap>& bitmap, bool genMipmaps, bool repeat) :
    _id(id),
    _bitmap(bitmap),
    _texture(),
    _genMipmaps(genMipmaps),
    _repeat(repeat)
{
}
    
template <typename T>
TextureCache<T>::CacheElement::CacheElement(T id, const std::shared_ptr<Texture>& texture) :
    _id(id),
    _bitmap(),
    _texture(texture),
    _genMipmaps(texture->isMipmaps()),
    _repeat(texture->isRepeat())
{
}

template <typename T>
const float TextureCache<T>::MIPMAP_SIZE_MULTIPLIER = 1.33f;
    
}

#endif
