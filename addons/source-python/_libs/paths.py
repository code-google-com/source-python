import os

game_path = os.path.dirname(__file__).replace('\\', '/').rsplit('addons', 1)[0]
addon_path = os.path.join(game_path, 'addons', 'source-python')
cfg_path = os.path.join(game_path, 'cfg', 'source-python')
