#ifndef BILLBOARDSORTER_H_
#define BILLBOARDSORTER_H_

#include <memory>
#include <vector>

namespace Nuti {

class Billboard;
class BillboardDrawData;
class ViewState;

class BillboardSorter{
public:
	BillboardSorter();
	virtual ~BillboardSorter();

	void addBillboard(const std::shared_ptr<Billboard>& billboard);

	void sort(const ViewState& viewState);

	const std::vector<std::shared_ptr<Billboard> >& getSortedBillboards() const;

	void clear();

private:
	bool distanceComparator(const std::shared_ptr<Billboard>& billboard1, const std::shared_ptr<Billboard>& billboard2) const;

	std::vector<std::shared_ptr<Billboard> > _billboards;

	bool _sort3D;

};

}

#endif
