#ifndef MAPTILEQUADTREENODE_H_
#define MAPTILEQUADTREENODE_H_

#include "core/MapBounds.h"
#include "core/MapPos.h"
#include "core/MapTile.h"

#include <memory>

namespace Nuti {

namespace QuadTreeRootType {
	enum QuadTreeRootType {LEFT = -1, CENTER = 0, RIGHT = 1};
}

namespace QuadTreeNodeType {
	enum QuadTreeNodeType {ROOT = 0, TOP_LEFT = 0, TOP_RIGHT = 1, BOTTOM_LEFT = 2, BOTTOM_RIGHT = 3};
}

class MapTileQuadTreeNode : public MapTile {
public:
	MapTileQuadTreeNode(int x, int y, int zoom, int frameNr);
	MapTileQuadTreeNode(QuadTreeRootType::QuadTreeRootType rootType, int frameNr);
	MapTileQuadTreeNode(const MapTileQuadTreeNode& parent, QuadTreeNodeType::QuadTreeNodeType nodeType);
	virtual ~MapTileQuadTreeNode();

	void setFrameNr(int frameNr);

	const MapPos& getCenter() const;
	const MapBounds& getTileBounds() const;

	double getDistanceFromCamera() const;
	void setDistanceFromCamera(double distance);

	float getRadius() const;

    const MapTileQuadTreeNode* getTopLeftChild() const;
	MapTileQuadTreeNode* getTopLeftChild();
	void setTopLeftChild(const std::shared_ptr<MapTileQuadTreeNode>& topLeftChild);
    const MapTileQuadTreeNode* getTopRightChild() const;
	MapTileQuadTreeNode* getTopRightChild();
	void setTopRightChild(const std::shared_ptr<MapTileQuadTreeNode>& topRightChild);
    const MapTileQuadTreeNode* getBottomRightChild() const;
	MapTileQuadTreeNode* getBottomRightChild();
	void setBottomRightChild(const std::shared_ptr<MapTileQuadTreeNode>& bottomRightChild);
    const MapTileQuadTreeNode* getBottomLeftChild() const;
	MapTileQuadTreeNode* getBottomLeftChild();
	void setBottomLeftChild(const std::shared_ptr<MapTileQuadTreeNode>& bottomLeftChild);

	const MapTileQuadTreeNode* getParent() const;

private:
	static int GetChildX(int parentX, QuadTreeNodeType::QuadTreeNodeType childType);
	static int GetChildY(int parentY, QuadTreeNodeType::QuadTreeNodeType childType);

	float _size;
	float _radius;
	MapPos _center;
	MapBounds _tileBounds;

	double _distanceFromCamera;

	std::shared_ptr<MapTileQuadTreeNode> _topLeftChild;
	std::shared_ptr<MapTileQuadTreeNode> _topRightChild;
	std::shared_ptr<MapTileQuadTreeNode> _bottomRightChild;
	std::shared_ptr<MapTileQuadTreeNode> _bottomLeftChild;

	const MapTileQuadTreeNode* _parent;
};

}

#endif
