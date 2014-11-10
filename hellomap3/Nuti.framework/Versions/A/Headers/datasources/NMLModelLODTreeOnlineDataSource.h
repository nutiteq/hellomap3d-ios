#ifndef _NUTI_NMLMODELLODTREESQLITEDATASOURCE_H_
#define _NUTI_NMLMODELLODTREESQLITEDATASOURCE_H_

#include "NMLModelLODTreeDataSource.h"

namespace Nuti {

/**
 * Online NML LOD Tree data source. This data source needs special
 * online service and uses custom protocol.
 */
class NMLModelLODTreeOnlineDataSource : public NMLModelLODTreeDataSource {
public:
	/**
	 * Constructs a NMLModelLODTreeSqliteDataSource object.
	 * @param projection The projection for the database. Currently only EPSG3857 is supported.
	 * @param serviceUrl The service connection point.
	 */
	NMLModelLODTreeOnlineDataSource(const std::shared_ptr<Projection>& projection, const std::string& serviceUrl);
	virtual ~NMLModelLODTreeOnlineDataSource();

	virtual std::vector<MapTile> loadMapTiles(const std::shared_ptr<CullState>& cullState);
	virtual std::shared_ptr<NMLModelLODTree> loadModelLODTree(const MapTile& mapTile);
	virtual std::shared_ptr<nml::Mesh> loadMesh(long long meshId);
	virtual std::shared_ptr<nml::Texture> loadTexture(long long textureId, int level);

private:
	class DataInputStream {
	public:
		DataInputStream(const std::vector<unsigned char>& data);

		unsigned char readByte();
		int readInt();
		long long readLongLong();
		float readFloat();
		double readDouble();
		std::string readString();
		std::vector<unsigned char> readBytes(std::size_t count);
	
	private:
		const std::vector<unsigned char>& _data;
		size_t _offset;
	};

	static bool inflate(const std::vector<unsigned char>& in, std::vector<unsigned char>& out);

	std::string _serviceUrl;
};

}

#endif
