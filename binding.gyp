{
  "targets": [
    {
      "target_name": "fullbowody",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/register.cpp",
        "./src/json/json11.cpp",
        "./src/common/common.cpp",
        "./src/Engine.cpp",

        "./src/extensions/Extension.cpp",
        "./src/extensions/ExtensionServer.cpp",
        "./src/extensions/Network_WIN.cpp",

        "./src/cameras/Camera.cpp",
        "./src/cameras/CameraManager.cpp",
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "<(module_root_dir)/src/include"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      "conditions": [
        ['OS == "win"',
          {
            "link_settings": {
                "libraries": [
                  '-lopencv_core460',
                  '-lopencv_imgproc460',
                  '-lopencv_imgcodecs460',
                  '-lopencv_calib3d460',
                  '-lopencv_aruco460',
                  '-lopencv_features2d460',
                  '-lopencv_objdetect460',
                  '-lopencv_video460',
                  '-lopencv_videoio460',
                  '-lopencv_highgui460',
                  '-lopencv_flann460',
                  '-lopencv_ml460',
                ],
                "library_dirs": [
                  "<(module_root_dir)/src/lib"
                ]
            }
          }
        ]
      ]
    }
  ]
}