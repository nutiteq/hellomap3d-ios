import UIKit

// NOTE: NTMapViewController is imported through 'bridging header' (hellomap3swift-Bridging-Header.h)
class MyMapViewController: NTMapViewController {

	override func viewDidLoad() {
		// The initial step: register your license. This must be done before using MapView and before calling super.viewDidLoad()!
		// You can get your free/commercial license from: http://developer.nutiteq.com
		// The license string used here is intended only for Nutiteq demos and WILL NOT WORK with other apps!
		NTMapViewController.RegisterLicense("XTUN3Q0ZBd2NtcmFxbUJtT1h4QnlIZ2F2ZXR0Mi9TY2JBaFJoZDNtTjUvSjJLay9aNUdSVjdnMnJwVXduQnc9PQoKcHJvZHVjdHM9c2RrLWlvcy0zLiosc2RrLWFuZHJvaWQtMy4qCnBhY2thZ2VOYW1lPWNvbS5udXRpdGVxLioKYnVuZGxlSWRlbnRpZmllcj1jb20ubnV0aXRlcS4qCndhdGVybWFyaz1ldmFsdWF0aW9uCnVzZXJLZXk9MTVjZDkxMzEwNzJkNmRmNjhiOGE1NGZlZGE1YjA0OTYK")

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
		
		// Create online vector tile layer, use style asset embedded in the project
		let vectorTileLayer = NTNutiteqOnlineVectorTileLayer(styleAssetName:"osmbright.zip")
		
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

