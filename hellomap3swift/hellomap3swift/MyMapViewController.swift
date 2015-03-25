import UIKit
import GLKit

// NOTE: NTMapView is imported through 'bridging header' (hellomap3swift-Bridging-Header.h)
class MyMapViewController: GLKViewController {
    
    override func loadView() {
        // The initial step: register your license.
        // You can get your free/commercial license from: http://developer.nutiteq.com
        // The license string used here is intended only for Nutiteq demos and WILL NOT WORK with other apps!
        NTMapView.registerLicense("XTUN3Q0ZBd2NtcmFxbUJtT1h4QnlIZ2F2ZXR0Mi9TY2JBaFJoZDNtTjUvSjJLay9aNUdSVjdnMnJwVXduQnc9PQoKcHJvZHVjdHM9c2RrLWlvcy0zLiosc2RrLWFuZHJvaWQtMy4qCnBhY2thZ2VOYW1lPWNvbS5udXRpdGVxLioKYnVuZGxlSWRlbnRpZmllcj1jb20ubnV0aXRlcS4qCndhdGVybWFyaz1ldmFsdWF0aW9uCnVzZXJLZXk9MTVjZDkxMzEwNzJkNmRmNjhiOGE1NGZlZGE1YjA0OTYK")
        
        super.loadView();
    }

	override func viewDidLoad() {
		super.viewDidLoad()
        
        // GLKViewController-specific parameters for smoother animations
        resumeOnDidBecomeActive = false
        preferredFramesPerSecond = 60
        
        let mapView = view as NTMapView
		
		// Set the base projection, that will be used for most MapView, MapEventListener and Options methods
		let proj = NTEPSG3857()
		mapView.getOptions().setBaseProjection(proj) // EPSG3857 is actually the default base projection, so this is actually not needed
		
		// General options
		mapView.getOptions().setRotatable(true) // make map rotatable (this is actually the default)
		mapView.getOptions().setTileThreadPoolSize(2) // use 2 threads to download tiles
		
		// Set initial location and other parameters, don't animate
		mapView.setFocusPos(proj.fromWgs84(NTMapPos(x:24.650415, y:59.428773)), durationSeconds:0)
		mapView.setZoom(14, durationSeconds:0)
		mapView.setRotation(0, durationSeconds:0)
		
		// Create online vector tile layer, use style asset embedded in the project
		let vectorTileLayer = NTNutiteqOnlineVectorTileLayer(styleAssetName:"osmbright.zip")
		
		// Add vector tile layer
		mapView.getLayers().add(vectorTileLayer)
		
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
		mapView.getLayers().add(vectorLayer)
	}
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated);
        
        // GLKViewController-specific, do on-demand rendering instead of constant redrawing
        // This is VERY IMPORTANT as it stops battery drain when nothing changes on the screen!
        paused = true;
    }

	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}


}

