from pynput.keyboard import Key, Controller
import time

def press_n(keyboard, key, n_times):
    for i in range(n_times):
        keyboard.press(key)
        keyboard.release(key)
        time.sleep(0.2)

def launch_game(keyboard):
    keyboard.type('nsnake\n')
    time.sleep(0.2)

def play_arcade(keyboard):
    press_n(keyboard, Key.enter, 1)

def game_settings(keyboard):
    press_n(keyboard, Key.down, 2)
    press_n(keyboard, Key.enter, 1)

if __name__ == '__main__':

    keyboard = Controller()  
    launch_game(keyboard)
    game_settings(keyboard)
#press_n(keyboard, Key.down, 1)
