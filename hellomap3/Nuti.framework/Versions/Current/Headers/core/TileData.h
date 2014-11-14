#ifndef TILEDATA_H_
#define TILEDATA_H_

#include <memory>
#include <vector>

namespace Nuti {
	
/**
 * A wrapper class for tile data.
 */
class TileData {
public:
	/**
	 * Constructs a VectorTileData object from a data blob.
	 * @param data The source tile data.
	 */
	TileData(const std::shared_ptr<std::vector<unsigned char> >& data) : _data(data) { }
	virtual ~TileData() { }
		
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
