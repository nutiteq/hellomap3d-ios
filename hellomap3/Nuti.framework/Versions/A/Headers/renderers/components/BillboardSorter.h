/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_BILLBOARDSORTER_H_
#define _NUTI_BILLBOARDSORTER_H_

#include <memory>
#include <vector>

namespace Nuti {
    class BillboardDrawData;
    class ViewState;
    
    class BillboardSorter {
    public:
        BillboardSorter();
        virtual ~BillboardSorter();
    
        void clear();
    
        void add(const std::shared_ptr<BillboardDrawData>& drawData);
    
        void sort(const ViewState& viewState);
    
        const std::vector<std::shared_ptr<BillboardDrawData> >& getSortedBillboardDrawDatas() const;
    
    private:
        bool distanceComparator(const std::shared_ptr<BillboardDrawData>& drawData1, const std::shared_ptr<BillboardDrawData>& drawData2) const;
    
        std::vector<std::shared_ptr<BillboardDrawData> > _billboardDrawDatas;
    
        bool _sort3D;
    };
    
}

#endif
