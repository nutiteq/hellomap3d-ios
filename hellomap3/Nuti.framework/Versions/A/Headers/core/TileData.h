/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_TILEDATA_H_
#define _NUTI_TILEDATA_H_

#include <memory>
#include <vector>
#include <mutex>
#include <chrono>

namespace Nuti {
    
    /**
     * A wrapper class for tile data.
     */
    class TileData {
    public:
        /**
         * Constructs a TileData object from a data blob.
         * @param data The source tile data.
         */
		TileData(const std::shared_ptr<std::vector<unsigned char> >& data);
		virtual ~TileData();
		
		/**
		 * Returns the maximum age of the tile data, tile data will expire after that point.
		 * @return Tile data maximum age in milliseconds, or -1 if the data does not expire.
		 */
		long long getMaxAge() const;
		
		/**
		 * Sets the maximum age of tile data, tile data will expire after that point.
		 * @param maxAge Tile data maximum age in milliseconds, or -1 if the data does not expire.
		 */
		void setMaxAge(long long age);
        
        /**
         * Returns true if the tile should be replaced with parent tile.
         * @return True if the tile should be replaced with parent. False otherwise.
         */
        bool isReplaceWithParent() const;
        
        /**
         * Set the parent replacement flag.
         * @param flag True when the tile should be replaced with the parent, false otherwise.
         */
        void setReplaceWithParent(bool flag);
		
        /**
         * Returns tile data as a byte vector.
         * @return Tile data as a byte vector.
         */
		std::shared_ptr<std::vector<unsigned char> > getData() const;
		
    private:
        std::shared_ptr<std::vector<unsigned char> > _data;
		std::shared_ptr<std::chrono::steady_clock::time_point> _expirationTime;
        bool _replaceWithParent;
		mutable std::mutex _mutex;
    };

}

#endif
