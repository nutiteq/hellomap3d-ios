//
//  ViewController.swift
//  hellomap3d-ios-swift
//
//  Created by oooits72 on 09/10/14.
//  Copyright (c) 2014 ooo its. All rights reserved.
//

import UIKit

class MapController: NTMapViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        
        let rasterdDataSource = NTHTTPRasterTileDataSource(minZoom: 0, maxZoom: 24, baseURL: "http://api.tiles.mapbox.com/v3/nutiteq.map-j6a1wkx0/{zoom}/{x}/{y}.png")
        
        // Initialize a raster layer with the data source, and add it to the MapView
        let rasterLayer = NTRasterTileLayer(dataSource: rasterdDataSource)
        getLayers().add(rasterLayer)
        
        let mapProj = getOptions().getBaseProjection()
        
        let vectorDataSource = NTUnculledVectorDataSource(projection: mapProj)
        
        let pos = mapProj.fromWgs84(NTMapPos(x: 24.651488, y: 59.423581))
        
        let ballonStyleBuilder = NTBalloonPopupStyleBuilder()
        ballonStyleBuilder.setPlacementPriority(10)
        
        let testPopUp = NTBalloonPopup(pos: pos, style: ballonStyleBuilder.buildStyle(), title: "en: test", desc: "ru: тест")
        vectorDataSource.add(testPopUp)
        
        let vectorLayer = NTVectorLayer(dataSource: vectorDataSource)
        
        getLayers().add(vectorLayer)
        
        setZoom(14, durationSeconds: 0.0)
        setFocusPos(pos, durationSeconds: 0.0)
    }
}

