#ifndef VECTORTILEDATA_H_
#define VECTORTILEDATA_H_

#include <memory>
#include <vector>

namespace Nuti {

/**
 * A wrapper class for vector tile data.
 */
class VectorTileData {
public:
    /**
     * Constructs a VectorTileData object from a data blob.
     * @param data The source tile data.
     */
	VectorTileData(const std::shared_ptr<std::vector<unsigned char> >& data) : _data(data) { }
	virtual ~VectorTileData() { }

    /**
     * Returns tile data as a byte vector.
     * @return Tile data as a byte vector.
     */
	std::shared_ptr<std::vector<unsigned char> > getData() const { return _data; }

private:
	std::shared_ptr<std::vector<unsigned char> > _data;
    
};

}

#endif
