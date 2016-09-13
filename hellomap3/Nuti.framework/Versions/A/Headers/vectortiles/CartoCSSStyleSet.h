/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CARTOCSSSTYLESET_H_
#define _NUTI_CARTOCSSSTYLESET_H_

#include <memory>
#include <string>
#include <vector>

namespace Nuti {
    class MBVectorTileStyleSet;

    /**
     * CartoCSS style definition for vector tiles.
     */
    class CartoCSSStyleSet {
    public:
        /**
         * Constructs a style from CartoCSS string.
         * @param cartoCSS The CartoCSS string defining point styling.
         */
        CartoCSSStyleSet(const std::string& cartoCSS);
        /**
         * Constructs a style from CartoCSS string and asset data.
         * @param cartoCSS The CartoCSS string defining point styling.
         * @param data Zipped assets that can be referenced from the CartoCSS.
         */
        CartoCSSStyleSet(const std::string& cartoCSS, const std::shared_ptr<std::vector<unsigned char> >& styleSetData);
        virtual ~CartoCSSStyleSet();

        /**
         * Returns the CartoCSS string used for the style.
         * @return The CartoCSS string used for the style.
         */
        const std::string& getCartoCSS() const;

        /**
         * Returns the style set data.
         * @return The style set data.
         */
        const std::shared_ptr<MBVectorTileStyleSet>& getStyleSetData() const;

    private:
        std::string _cartoCSS;
        std::shared_ptr<MBVectorTileStyleSet> _styleSetData;
    };

}

#endif
