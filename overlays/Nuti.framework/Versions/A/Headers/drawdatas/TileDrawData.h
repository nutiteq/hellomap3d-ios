#ifndef TILEDRAWDATA_H_
#define TILEDRAWDATA_H_

namespace Nuti {

class TileDrawData {
public:
	TileDrawData(long long tileId, bool preloadingTile);
	virtual ~TileDrawData();
    
    float getAlpha() const;
    void setAlpha(float alpha);
    
    bool isPreloadingTile() const;

	long long getTileId() const;

private:
    float _alpha;
    
    bool _preloadingTile;
    
	long long _tileId;

};

}

#endif
