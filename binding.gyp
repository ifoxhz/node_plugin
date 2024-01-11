{
  "targets": [
    {
      "target_name": "kpgen",
      "sources": ["kpgen.c"],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include\")",
        "./inc"
      ],
      "libraries": [
        "-L../lib",
        "-lkp_gen"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"],
      "ldflags": [
        "-Wl,-rpath,./",
        "-Wl,-rpath,./lib"
      ]
    }
  ]
}
