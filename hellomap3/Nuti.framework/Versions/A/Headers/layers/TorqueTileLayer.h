#include <memory>

#include "layers/TileLayer.h"

namespace Nuti {
    class TorqueTileDecoder;

    class TorqueTileLayer : public TileLayer {
    public:
        TorqueTileLayer(const std::shared_ptr<TileDataSource>& dataSource, const std::shared_ptr<TorqueTileDecoder>& decoder);

        int getFrameCount() const;
        int getCurrentFrame() const;
        void setCurrentFrame(int frame);

        std::shared_ptr<TorqueTileDecoder> getDecoder() const;
    };

}
