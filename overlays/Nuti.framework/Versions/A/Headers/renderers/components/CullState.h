#ifndef CULLSTATE_H_
#define CULLSTATE_H_

#include "core/MapEnvelope.h"
#include "graphics/Frustum.h"
#include "graphics/MapTileQuadTreeNode.h"
#include "graphics/ViewState.h"

#include <memory>
#include <vector>

namespace Nuti {

/**
 * View specific state determined by the culling process. This includes 
 * convex envelope of the visible area, view frustum, tiles and camera state.
 */
class CullState {
public:
    /** 
     * Constructs a CullState object from an envelope, visible and preloading frustums, a preloading camera
     * position and a viewstate.
     * @param envelope The envelope.
     * @param preloadingFrustum The preloading frustum.
     * @param preloadingCameraPos The preloading camera position.
     * @param viewState The view state.
     */
    CullState(const MapEnvelope& envelope, const Frustum& preloadingFrustum,
              const MapPos& preloadingCameraPos, const ViewState& viewState);
	virtual ~CullState();

    /**
     * Returns an envelope for the visible area.
     * @return The envelope for the visible area in the internal coordiante system.
     */
	const MapEnvelope& getEnvelope() const;
    /**
     * Returns a frustum for the area that is not visible, but should still be drawn.
     * @return The frustum for the preloading area in the internal coordiante system.
     */
    const Frustum& getPreloadingFrustum() const;
    
    /**
     * Returns a modified camera pos, that was used for calculating the preloading frustum.
     * @return The modified preloading camera position in the internal coordinate system.
     */
    const MapPos& getPreloadingCameraPos() const;

    /**
     * Returns a view state.
     * @return The view state.
     */
	const ViewState& getViewState() const;

private:
	MapEnvelope _envelope;
    
    Frustum _preloadingFrustum;
    
    MapPos _preloadingCameraPos;

	ViewState _viewState;
};

}

#endif
