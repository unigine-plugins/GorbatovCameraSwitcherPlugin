# GorbatovCameraSwitcherPlugin

![image](https://store.unigine.com/api/media-files/1ee27ae6-bd20-60a6-b75b-eb64a4813099)

plugin for [store.unigine.com](https://store.unigine.com/add-on/1ee27adb-616f-62a8-a95c-cf0a3dbb4409/description)

The plugin allows switching between all existing cameras by pressing the `c` button.

This plugin works with float/double precision on windows/linux. 

## There are three ways to add this plugin to your application:

1. Add GorbatovCameraSwitcher in the `-extern_plugin` startup comand-line args. For example: -extern_plugin UnigineFbxImporter,GorbatovCameraSwitcher

2. Call the plugin from code by adding `Engine::get()->addPlugin("GorbatovCameraSwitcher");`

3. Add plugin's sources in your project build and call `Engine::get()->addPlugin(new CameraSwitcherPlugin());`


## how to rebuild
- copy this repo in your porject or install the package from assetstore
- use cmake to build. For example for debug-double use this commands
```
cmake -B ./build-debug-double -S source/plugins/Gorbatov/CameraSwitcher -DUNIGINE_DOUBLE=1 -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build-debug-double
```

