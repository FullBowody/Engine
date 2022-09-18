{
  "targets": [
    {
      "target_name": "fullbowody",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/register.cpp",
        "./src/json/json11.cpp",
        "./src/common/Promise.cpp",

        "./src/extensions/Extension.cpp",
        "./src/extensions/ExtensionServer.cpp",
        "./src/extensions/Network_WIN.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}