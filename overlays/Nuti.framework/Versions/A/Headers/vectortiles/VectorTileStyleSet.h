#ifndef VECTORTILESTYLESET_H_
#define VECTORTILESTYLESET_H_

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace Nuti {

/**
 * Style set for vector tiles. Style set is read-only.
 */
class VectorTileStyleSet {
public:
	// TODO: comments
	VectorTileStyleSet(const std::shared_ptr<std::vector<unsigned char> >& data);
	virtual ~VectorTileStyleSet();

	// TODO: getRootElementName?
	std::vector<std::string> getElementNames() const;
	std::shared_ptr<std::vector<unsigned char> > getElement(const std::string& name) const;

private:
	std::map<std::string, std::shared_ptr<std::vector<unsigned char> > > _elementMap;
};

}

#endif
