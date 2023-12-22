# sfeMovie2

sfeMovie2 is a fork of sfeMovie https://github.com/Yalir/sfeMovie
It is intended to play videos in SFML applications.
Used in DGEngine.core.

## Changes from sfeMovie

* Add open from streams (SFML class sf::InputStream)
* ffmpeg not included (works with whatever version of ffmpeg cmake detects)
* Removed subtitle support
* Static and dynamic linking to ffmpeg (#define SFEMOVIE_DYNAMIC_FFMPEG 0/1)
* Upgraded to work with ffmpeg 4, 5 and 6

## Known issues

* Some videos don't play audio (diablo 2 videos)
* Fails to decode some videos (h265 full HD videos)

Feel free to make a PR to fix these issues.

## FFMpeg library version numbers

When built with dynamic linking, sfeMovie will try to load the following libraries (.dll or .so)

### 4.x

* avcodec-58
* avdevice-58
* avfilter-7
* avformat-58
* avutil-56
* postproc-55
* swresample-3
* swscale-5

### 5.x

* avcodec-59
* avdevice-59
* avfilter-8
* avformat-59
* avutil-57
* postproc-56
* swresample-4
* swscale-6

### 6.x

* avcodec-60
* avdevice-60
* avfilter-9
* avformat-60
* avutil-58
* postproc-57
* swresample-4
* swscale-7
