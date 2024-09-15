# fbcur

fbcur is a small linux framebuffer program to handle mouse movements to draw a
cursor. Mouse clicks are not tracked and the cursor isn't designed to integrate
with any other programs (if you want that, use a window system like X or
Wayland). The fbcur cursor is likely only useful if you want to have a dot to
direct attention on your screen.

There are two versions of fbcur. They are nearly identical but use different
linux APIs:
- `fbcur`: Uses the mousedev interface. This is the reccomended version to use.
    It should work with both mice and touchpads. If you have multiple of these
    devices, you can tell `fbcur` to use the `/dev/input/mice` device which
    will track all mice/touchpad input devices. If you would like `fbcur` to
    only track input from one mouse or touchpad device, specify the device with
    its `/dev/input/mouseX` device.
- `fbcur_ev`: Uses the evdev interface. Although linux encourages this API over
    mousedev, it is more complicated. As a result, `fbcur_ev` does not support
    trackpad devices, but regular mice should work fine. To tell `fbcur_ev`
    which device to track input from, you need to find the `/dev/input/eventX`
    device for your mouse. You can find this by reading
    `/proc/bus/input/devices`. Unless your kernel was compiled without mousedev
    support, you should use `fbcur` instead.

fbcur takes two command line arguments: the device file of the framebuffer and
the device file of the input device to track. Here is an example invokation
which will work on most systems:
```
fbcur /dev/fb0 /dev/input/mice
```
To use `fbcur_ev` instead, replace `fbcur` with `fbcur_ev` and
`/dev/input/mice` with your event device.
