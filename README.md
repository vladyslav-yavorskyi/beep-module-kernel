# Beep Module Kernel

This kernel module listens for the 'w' key press events and triggers a beep sound using the PC speaker after every 5 presses of the 'w' key. The module utilizes a keyboard notifier to detect key presses and invokes the `kd_mksound` function to generate a beep at 440Hz for 500ms.

## Features
- **Key Press Detection**: The module listens for the press of the 'w' key.
- **Beep Generation**: Generates a beep sound every 5 times the 'w' key is pressed.
- **PC Speaker**: Uses the `kd_mksound` function to produce the beep sound.

## Prerequisites
- **Linux Kernel**: This module is designed for use in the Linux kernel.
- **Kernel Development Tools**: Ensure that you have the necessary tools for building and loading kernel modules installed (e.g., `make`, `gcc`, `kernel-headers`).

## Installation
1. **Clone or Download the Code**:
   - Clone this repository or download the `beep_module.c` file to your system.

2. **Build the Module**:
   - Create a `Makefile` for building the kernel module, or use the following basic Makefile:

     ```
     obj-m += beep_module.o
     all:
         make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
     clean:
         make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
     ```

   - Run `make` to compile the kernel module.

3. **Load the Module**:
   - After compiling the module, load it into the kernel with:

     ```
     sudo insmod beep_module.ko
     ```

4. **Check the Logs**:
   - The module will log information whenever the 'w' key is pressed and every time the beep is triggered. To check the logs, use:

     ```
     dmesg | grep "Beep module"
     ```

5. **Unload the Module**:
   - To unload the module from the kernel, run:

     ```
     sudo rmmod beep_module
     ```

## How It Works
1. The module uses a keyboard notifier to listen for key press events.
2. When the 'w' key is pressed, the module increments a counter (`w_counter`).
3. After 5 presses, the module triggers a beep sound using the `kd_mksound` function, which generates a tone at 440Hz for 500ms.
4. The counter is reset to 0 after the beep is triggered, and the process repeats.

## License
This kernel module is released under the **GPL-2.0 License**.

## Author
- **Vladyslav Yavorskyi**

## Notes
- The module works on Linux systems with a kernel version that supports the `kd_mksound` function and keyboard notification.
- This module is designed to trigger beeps based on key presses in development or testing environments.
- Ensure you have the appropriate permissions to load/unload kernel modules and access `dmesg` output.

## Troubleshooting
- If the module is not responding to key presses, make sure that you have the necessary permissions and that the `kd_mksound` function is available in your environment.

