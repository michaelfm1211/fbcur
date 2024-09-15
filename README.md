# fbcur

fbcur is a small linux framebuffer program to handle mouse movements to draw a
cursor. Mouse clicks are not tracked and the cursor isn't designed to integrate
with any other programs (if you want that, use a window system like X or
Wayland). The fbcur cursor is likely only useful if you want to have a dot to
direct attention on your screen.

There are two versions of fbcur. They are nearly identical but use different
linux APIs:
- `fbcur`: Uses the mousedev interface. This is the reccomended version to use.
    It should work with both mice and touchpads.
- `fbcur_ev`: Uses the evdev interface. Although linux encourages this API over
    mousedev, it is more complicated. As a result, `fbcur_ev` does not support
    trackpad devices, but regular mice should work fine. To tell `fbcur_ev`
    which device to track input from, you need to find the `/dev/input/eventX`
    device for your mouse. You can find this by reading
    `/proc/bus/input/devices`. Unless your kernel was compiled without mousedev
    support, you should use `fbcur` instead.

fbcur takes two command line arguments: the device file of the framebuffer and
the device file of the input device to track. If using `fbcur`, the second
argument is optional (but is required for `fbcur_ev`). The follow invokation
will work on most programs:
```
fbcur /dev/fb0
```
Here is an example of specifying an input device:
```
fbcur /dev/fb0 /dev/input/mouse0
```
To use `fbcur_ev`, replace `fbcur` with `fbcur_ev` and pass an event device.
For example:
```
fbcur /dev/fb0 /dev/input/event2
```
