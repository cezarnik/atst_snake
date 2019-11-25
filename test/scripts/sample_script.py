from pynput.keyboard import Key, Controller
import time

def press_n(keyboard, key, n_times, delay=0.2):
    for i in range(n_times):
        keyboard.press(key)
        keyboard.release(key)
        time.sleep(delay)

def launch_game(keyboard):
    keyboard.type('nsnake\n')
    time.sleep(0.2)

def exit_game(keyboard): # call anywhere
    press_n(keyboard, 'q', 1)

def go_to_main_menu_param(keyboard, param):
    possible_params = {'arcade_mode':0, 
                        'level_select':1, 
                        'game_settings':2,
                        'gui_options':3,
                        'controls':4,
                        'help':5,
                        'quit':6}
    assert param in possible_params
    press_n(keyboard, Key.page_up, 1)
    press_n(keyboard, Key.down, possible_params[param])
    press_n(keyboard, Key.enter, 1)


def go_to_settings_param(keyboard, param): # should be in settings
    possible_params = {'back':0,
            'starting_speed':1, 
            'fruits':2, 
            'teleport':3, 
            'random_walls':4, 
            'maze_size':5, 
            'scroll_delay':6, 
            'scroll_up':7, 
            'scroll_down':8, 
            'scroll_left':9, 
            'scroll_right':10, 
            'erase_high_scores':11}
    assert param in possible_params
    press_n(keyboard, Key.page_up, 1)
    press_n(keyboard, Key.down, possible_params[param])


def change_settings_param(keyboard, command : list):
    if len(command)!=1:
        return
    val = int(command[0])
    press_n(keyboard, Key.left, 100, 0.01) # kostyl
    press_n(keyboard, Key.right, val - 1, 0.01)


def manage_settings(keyboard, command : list):
    if len(command)==0:
        return
    go_to_settings_param(keyboard, command[0])
    if command[0]=='back':
        press_n(keyboard, Key.enter, 1)
        return
    elif command[0]=='erase_high_scores':
        press_n(keyboard, Key.right, 1)
        press_n(keyboard, Key.enter, 1)
    change_settings_param(keyboard, command[1:])


def process_command(keyboard, command): # main_menu:param or settings:[param:value]
    if len(command)==0:
        return
    command = command.split(':')
    if command[0] == 'game_settings':
        manage_settings(keyboard, command[1:])
    elif command[0] == 'main_menu':
        go_to_main_menu_param(keyboard, command[1])

def test(keyboard, commands): # main menu
    launch_game(keyboard)
    for command in commands:
        process_command(keyboard, command)
    exit_game(keyboard)

if __name__ == '__main__':

    keyboard = Controller()  
    launch_game(keyboard)
    process_command(keyboard, 'main_menu:game_settings')
    process_command(keyboard, 'game_settings:starting_speed:7')
    process_command(keyboard, 'game_settings:fruits:27')
    process_command(keyboard, 'game_settings:erase_high_scores')

#press_n(keyboard, Key.down, 1)
