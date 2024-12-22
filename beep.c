#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/fs.h>
#include <linux/keyboard.h>
#include <linux/notifier.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/io.h>

static struct notifier_block keyboard_notifier;
static int w_counter = 0;

extern void kd_mksound(unsigned int hz, unsigned int ticks); // This is the PC speaker tone function

static int keyboard_callback(struct notifier_block *nb, unsigned long action, void *data)
{
    struct keyboard_notifier_param *param = (struct keyboard_notifier_param *)data;

    if (param->down) {
        // If the key 'w' is pressed
        if (param->value == KEY_W) {
            w_counter++;
            printk(KERN_INFO "Pressed 'w', count = %d\n", w_counter);
	    kd_mksound(440, 500);
            
            // Trigger the beep every time 'w' is pressed
            if (w_counter == 5) {
                printk(KERN_INFO "Beep triggered after 5 'w' presses\n");

                // Generate a beep sound using kd_mksound (frequency 440 Hz for 500 ms)
                kd_mksound(440, 500);  // 440Hz frequency, 500ms duration

                w_counter = 0;  // Reset the counter
            }
        }
    }
    return NOTIFY_OK;
}

static int __init beep_module_init(void)
{
    printk(KERN_INFO "Beep module loaded\n");

    // Register the keyboard notifier
    keyboard_notifier.notifier_call = keyboard_callback;
    return register_keyboard_notifier(&keyboard_notifier);
}

static void __exit beep_module_exit(void)
{
    unregister_keyboard_notifier(&keyboard_notifier);
    printk(KERN_INFO "Beep module unloaded\n");
}

module_init(beep_module_init);
module_exit(beep_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vladyslav Yavorskyi");
MODULE_DESCRIPTION("A simple module to generate beeps from the PC speaker");

