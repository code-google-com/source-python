# ../_libs/commands/manager.py


# =============================================================================
# >> CLASSES
# =============================================================================
class _CommandRegistry(object):
    '''Base registry class used to store commands in a dictionary'''

    def __init__(self):
        '''Create the commands dictionary for this instance'''
        self._commands = dict()


class _CommandList(list):
    '''Base list class used to store a list of callbacks for a command'''

    def __init__(self, name):
        '''Get the instance of the command'''
        self._command = self._get_command_instance(name)

    def append(self, item):
        '''Override append to add the instance's callback to
            the command if it is not currently registered'''

        # Is the list empty?
        if not self:

            # Add the list's callback to the command's callback list
            self._command.AddToEnd(self._command_called)

        # Is the item already in the list?
        if not item in self:

            # Add the item to the list
            super(_CommandList, self).append(item)

    def remove(self, item):
        '''Override remove to remove the instance's callback from
            the command if there are no longer any items in the list'''

        # Is the item in the list?
        if not item in self:

            # If not, no need to remove it
            return

        # Remove the item from the list
        super(_CommandList, self).remove(item)

        # Are there any callbacks in the list?
        if not self:

            # If not, remove the list's callback
            # from the command's callback list
            self._command.Remove(self._command_called)

    def _command_called(self, *args):
        '''Method used to call all callbacks in the list'''

        # Set the starting return value
        return_val = True

        # Loop through the callbacks in the list
        for callback in self:

            # Call the callback
            return_type = callback(*args)

            # Get the updated return value
            return_val = return_val and (
                return_type is None or bool(return_type))

        # Should the "CONTINUE" value be returned?
        if return_val:

            # Return the "CONTINUE" value
            return self._ContinueValue

        # Return the "BLOCK" value
        return self._BlockValue
