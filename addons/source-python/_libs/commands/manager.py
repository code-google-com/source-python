# ../_libs/commands/manager.py


# =============================================================================
# >> CLASSES
# =============================================================================
class _BaseCommandRegistry(dict):
    def RegisterCommand(self, name, callback, description, *args):
        # Is the command already registered?
        if name in self:
            raise
        self[name] = _RegistryClass(name, callback, description, *args)

    def UnregisterCommand(self, name, callback):
        # Is the command registered?
        if not name in self:
            raise
        # Is the given callback the correct callback?
        if callback != self[name].callback:
            raise
        self[name]._UnregisterCommand()
        del self[name]


class _PlayerCommand(object):
    def __init__(self, name, callback, description,
      auth_level=None, auth_capability=None, unauth_callback=None):
        self.name = name
        self.callback = callback
        self.auth_level = auth_level
        self.auth_capability = auth_capability
        self.unauth_callback = unauth_callback
        self._SourceRegistryClass.RegisterCommand(
            self.name, self._Callback, description)

    def _Callback(self, userid, args):
        # Is the player authorized?
        if not <something>:
            # Is there an unauth callback?
            if callable(self.unauth_callback):
                self.unauth_callback(userid, self.name, args)
        else:
            self.callback(userid, self.name, args)


class _ServerCommand(object):
    def __init__(self, name, callback, description):
        self.name = name
        self.callback = callback
        SourceServerCommand.RegisterCommand(
            self.name, self._Callback, description)

    def _Callback(self, userid, args):
        self.callback(userid, self.name, args)


class _ClientCommand(_PlayerCommand):
    _SourceRegistryClass = SourceClientCommand


class _SayCommand(_PlayerCommand):
    _SourceRegistryClass = SourceSayCommand


class _ClientCommandRegistry(_BaseCommandRegistry):
    _RegistryClass = _ClientCommand

ClientCommandRegistry = _ClientCommandRegistry()


class _SayCommandRegistry(_BaseCommandRegistry):
    _RegistryClass = _SayCommand

SayCommandRegistry = _SayCommandRegistry()


class _ServerCommandRegistry(_BaseCommandRegistry):
    _RegistryClass = _ServerCommand

ServerCommandRegistry = _ServerCommandRegistry()
