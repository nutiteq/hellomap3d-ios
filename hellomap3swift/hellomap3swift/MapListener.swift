//
//  MapListener.swift
//  hellomap3swift
//
//  Created by Jaak Laineste on 25/05/15.
//  Copyright (c) 2015 Nutiteq. All rights reserved.
//

class MapListener: NTMapEventListener {
  
  var mapView: NTMapView?
  
  convenience init(mapView_: NTMapView){
    self.init()
    self.mapView = mapView_
  }

  
  // Map is moved, called also during move, with every small (single pixel) movement
  override func onMapMoved(){
    NTLog.debug("map moved");
  }

  // Map element is clicked. Can have many elements under same point
  override func onVectorElementClicked(vectorElementsClickInfo: NTVectorElementsClickInfo){
    NTLog.debug("clicked " + vectorElementsClickInfo.getVectorElementClickInfos().get(0).getVectorElement().description)
  }

  // Map is clicked outside any vector element.
  override func onMapClicked(mapClickInfo: NTMapClickInfo!) {
    
    if (mapClickInfo.getClickType() == NTClickType._CLICK_TYPE_DOUBLE)
    {
      NTLog.debug("Double map click!")
      self.mapView?.zoom(1.5, durationSeconds: 0.3)
    }
    
  }
  
}
