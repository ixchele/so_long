from pynput import keyboard

def on_press(key):
    try:
        print(f"Touche pressée : {key.char} (KeyCode: {key.vk})")
    except AttributeError:
        print(f"Touche spéciale : {key} (KeyCode: {key.vk})")

with keyboard.Listener(on_press=on_press) as listener:
    listener.join()
