/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_BILLBOARDPLACEMENTWORKER_H_
#define _NUTI_BILLBOARDPLACEMENTWORKER_H_

#include "components/ThreadWorker.h"
#include "core/MapEnvelope.h"
#include "utils/KDTreeSpatialIndex.h"

#include <condition_variable>
#include <memory>
#include <mutex>

namespace Nuti {
    class Billboard;
    class BillboardDrawData;
    class MapRenderer;
    
    class BillboardPlacementWorker : public ThreadWorker {
    public:
        BillboardPlacementWorker();
        virtual ~BillboardPlacementWorker();
        
        void setComponents(const std::weak_ptr<MapRenderer>& mapRenderer, const std::shared_ptr<BillboardPlacementWorker>& worker);
        
        void init(int delayTime);
        
        void stop();
    
        void operator()();
    
    private:
        void run();
        
        bool calculateBillboardPlacement();
        
        bool overlapComparator(const std::shared_ptr<Billboard>& billboard1, const std::shared_ptr<Billboard>& billboard2) const;
        
        volatile bool _stop;
        
        KDTreeSpatialIndex<MapEnvelope> _kdTree;
        
        bool _sort3D;
    
        std::chrono::time_point<std::chrono::system_clock> _wakeupTime;
        
        std::weak_ptr<MapRenderer> _mapRenderer;
        std::shared_ptr<BillboardPlacementWorker> _worker;
    
        std::condition_variable _condition;
        mutable std::mutex _mutex;
    };
    
}

#endif
