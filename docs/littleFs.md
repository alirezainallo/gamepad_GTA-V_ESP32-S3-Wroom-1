add this to platformio.ini:

`board_build.filesystem = littlefs`

upload data files to littlefs:

`pio run --target uploadfs`
