#ifndef RASTERTILEBITMAP_H_
#define RASTERTILEBITMAP_H_

#include "graphics/Bitmap.h"

#include <memory>
#include <vector>

namespace Nuti {

/**
 * A wrapper class for bitmaps representing raster map tiles.
 */
class RasterTileBitmap {
public:
    /**
     * Constructs a RasterTileBitmap object from an uncompressed bitmap.
     * @param bitmap The source bitmap for this raster tile bitmap.
     */
	RasterTileBitmap(const std::shared_ptr<Bitmap>& bitmap);
    /**
     * Constructs a RasterTileBitmap object from a compressed image.
     * @param bitmap The source compressed image for this raster tile bitmap.
     */
	RasterTileBitmap(const std::shared_ptr<std::vector<unsigned char> >& compressed);
	virtual ~RasterTileBitmap();

    /**
     * Returns the source bitmap.
     * @return The source bitmap.
     */
	std::shared_ptr<Bitmap> getBitmap();
    /**
     * Returns this raster tile bitmap as a compressed byte vector.
     * @return The compressed bitmap as a byte vector.
     */
	std::shared_ptr<std::vector<unsigned char> > getCompressed();

private:
	std::shared_ptr<Bitmap> _bitmap;
	std::shared_ptr<std::vector<unsigned char> > _compressed;
    
};

}

#endif
