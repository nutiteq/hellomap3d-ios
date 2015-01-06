/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_TEXTURE_H_
#define _NUTI_TEXTURE_H_

#include "core/MapBounds.h"
#include "utils/GLES2.h"

namespace Nuti {
    class Bitmap;
    
    class Texture {
    public:
        Texture(const Bitmap& bitmap, bool genMipmaps, bool repeat);
        virtual ~Texture();
        
        void unload();
        
        bool isMipmaps() const;
        
        bool isRepeat() const;
        
        unsigned int getSize() const;
        
        const MapBounds& getTexCoordBounds() const;
        
        GLuint getTexId() const;
    
    private:
        static const int MAX_ANISOTROPY;
        
        static const float MIPMAP_SIZE_MULTIPLIER;
    
        void loadFromBitmap(const Bitmap& bitmap, bool genMipmaps, bool repeat);
        
        bool _mipmaps;
        
        bool _repeat;
        
        unsigned int _sizeInBytes;
        
        MapBounds _texCoordBounds;
    
        GLuint _texId;
    };
    
}

#endif
