# FullBowody Engine

This repository contains the source code for the FullBowody Engine.
A program made to retreive some camera's video feed and create a fully 3D tracked body rig from it.

## Project informations
- This engine is fully written in [C++](https://en.wikipedia.org/wiki/C%2B%2B)
- The engine uses the [N-API](https://nodejs.org/api/n-api.html) interface to communicate with [Node.js](https://nodejs.org/en/)
- All the source code is compiled using [Node-GYP](https://www.npmjs.com/package/node-gyp) and [Python](https://www.python.org/)
- The [OpenCV](https://opencv.org/) library is used to handle camera-related features
- Google's [MediaPipe](https://mediapipe.dev/) library is used to handle the body tracking
- The NodeJS addon bridge is scripted in [TypeScript](https://www.typescriptlang.org/)

All the documentation about FullBowody's Engine can be found on [FullBowody's Website](https://furwaz.com/fullbowody)

## Setup projet
To setup the project, run
```bash
npm install
npm install -g node-gyp
```
Make sure you have a C++ compiler installed on your machine for Node-GYP to compile the addon.

The OpenCV library should also be included in the project.
- The folder at `/src/include` should contains the `opencv2` include folder
- The folder at `/src/lib` should contains all the opencv libraries
- The folder at `/src/bin` should contains all the opencv binaries

## Configure projet
To configure the project, simply run
```bash
node-gyp configure
```

## Build project
To build the addon, run
```bash
node-gyp build
```
The compiled addon will be located in the `/build/Release` folder. 

Next, to copy the OpenCV binaries into the addon's folder,
run the `setBins.bat` script on Windows (or `setBins.sh` on Linux)

---
Author : [FurWaz](https://github.com/furwaz)