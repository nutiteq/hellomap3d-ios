import UIKit

// NOTE: NTMapViewController is imported through 'bridging header' (hellomap3swift-Bridging-Header.h)
class MyMapViewController: NTMapViewController {

	override func viewDidLoad() {
		super.viewDidLoad()
		
		// Set the base projection, that will be used for most MapView, MapEventListener and Options methods
		let proj = NTEPSG3857()
		getOptions().setBaseProjection(proj) // EPSG3857 is actually the default base projection, so this is actually not needed
		
		// General options
		getOptions().setRotatable(true) // make map rotatable (this is actually the default)
		getOptions().setTileThreadPoolSize(2) // use 2 threads to download tiles
		
		// Set initial location and other parameters, don't animate
		setFocusPos(proj.fromWgs84(NTMapPos(x:24.650415, y:59.428773)), durationSeconds:0)
		setZoom(14, durationSeconds:0)
		setRotation(0, durationSeconds:0)
		
		// Create online vector tile layer, connect to with demo key and use style asset embedded in the project
		let vectorTileLayer = NTNutiteqOnlineVectorTileLayer(apiKey:"15cd9131072d6df68b8a54feda5b0496", styleAssetName:"osmbright.zip")
		
		// Add vector tile layer
		getLayers().add(vectorTileLayer)
		
		// Load bitmaps for custom markers
		let markerImage = UIImage(named:"marker.png")
		let markerBitmap = NTBitmapUtils.createBitmapFromUIImage(markerImage)
		
		// Create a marker style, use it for both markers, because they should look the same
		let markerStyleBuilder = NTMarkerStyleBuilder()
		markerStyleBuilder.setBitmap(markerBitmap)
		markerStyleBuilder.setSize(30)
		let sharedMarkerStyle = markerStyleBuilder.buildStyle()
		
		// Initialize a local vector data source
		let vectorDataSource = NTLocalVectorDataSource(projection:proj)
		
		// Create marker, add it to the data source
		let pos = proj.fromWgs84(NTMapPos(x:24.646469, y:59.426939)) // Tallinn
		let marker = NTMarker(pos:pos, style:sharedMarkerStyle)
		vectorDataSource.add(marker)
		
		// Initialize a vector layer with the previous data source
		let vectorLayer = NTVectorLayer(dataSource:vectorDataSource)
		
		// Add the previous vector layer to the map
		getLayers().add(vectorLayer)
	}

	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}


}

