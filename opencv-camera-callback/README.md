# Dual camera viewer

![alt tag](screenshot.png)
![alt tag](front.jpg)

## Required packages

```
sudo apt install libopencv-dev
sudo apt-get install qt6-base-dev
```

## Demo program

```
cmake .
make
./cameras-viewer
```

Note that the only FourCC image formats which work on the Rock5 are GREY and NV12 for
B&W and colour respectively.

## ROCK 5 camera colour correction

The camera callback applies a lightweight grey-world colour correction to
three-channel frames before they are sent to the viewer.

This compensates for the strong green colour cast observed with the Raspberry Pi
Camera V2 modules on ROCK 5 when the ISP/AWB processing is not active.

## Further reading

See https://github.com/berndporr/opencv-camera-callback for in depth discussion about
V4L and its media pipelines.
