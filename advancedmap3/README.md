
This is sample for Nutiteq SDK (http://www.nutiteq.com), demonstrating several key features.

## Features
1. Creating a map
   - set map location and zoom
   - setting some properties
2. Adding layers
   - Layers need Data Sources as actual data source
3. VectorTileLayer for vector-based base map
   - Online global source 
   - Offline file (Berlin sample) as another option
4. Various other layer types:
   - VectorLayer to add points, lines, polygons and markers to the map. Objects are added to backing Data Source.
   - RasterLayer for tile-based raster datasources
5. MapEventListener to get map events:
   - Click on map
   - Click on map object, including balloons and 3D objects
6. Adding Balloon Popopups "callouts" to the map
   - Some are added to the map and are always visible
   - Some are coming when you click on map, or some map object
7. Add 3D data to map
   - Two offline datasets: building in NMLDB (3D city) format, and simple 3D car in NML (3D model) format. You can reposition, rotate etc NML models via code easily.

## Running
The project requires Nutiteq SDK what you can get from the hellomap3 project. Just copy Nuti.framework folder to your application project. In your app folder run:

    cp -r ../Nuti.framework ./


The app works on iOS 7 or newer.

## Debugging

If you have crash and want to debug SDK side, then Download Nutiteq SDK debug build from https://www.nutiteq.com/owncloud/public.php?service=files&t=3841f64795ac883a38d868a119b4cc28 and extract the Nuti.framework.zip to the project's root folder.

