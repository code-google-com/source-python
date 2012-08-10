# ../_libs/core/__init__.py


# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Engine
from Source import Shared
from Source import Cvar


# =================================================================
# Globals
# =================================================================
EngineServer = Engine.GetEngine()
CvarServer = Cvar.GetCvar()


# =============================================================================
# >> CLASSES
# =============================================================================
class ServerVar(object):
    '''ConVar wrapper to provide easy access to cvars.'''
    
    def __init__(self, *args):
        '''Called when a server-var is initilized.'''
        # Only one argument?
        if len(args) == 1:
            
            # Make sure first argument is a string
            name = str(args[0])
            
            # Try to find an existing instance of the cvar
            self.ConVar = CvarServer.FindVar(name)
            
            # If we could not find an existing instance, we need to create one
            if not self.ConVar:
                self.ConVar = Cvar.ConVar(name, '0', 0, name)
        
        # Multiple arguments
        else:    
            # Default types taken by the ConVar constructor
            default_types = (str, str, int, str, bool, float, bool, float)
            
            # Convert argument tuple into a list
            args = list(args)
            
            # Convert every argument into it's proper type
            for i in range(len(args)):
                args[i] = default_types[i](args[i])
            
            # Create the new ConVar using the constructor
            self.ConVar = Cvar.ConVar(*args)             
            
    def __getattr__(self, name):
        '''Runs missing attributes and methods against ConVar instance'''
        return getattr(self.ConVar, name)       
    
    def __str__(self):
        '''Returns string value of ConVar instance.'''
        return str(self.ConVar.GetString())
    
    def __float__(self):
        '''Returns float value of ConVar instance.'''
        return float(self.ConVar.GetFloat())
    
    def __int__(self):
        '''Returns int value of ConVar instance.'''
        return int(self.ConVar.GetInt())
    
    def __nonzero__(self):
        '''Returns bool value of ConVar instance.'''
        return bool(self.ConVar.GetBool())
        
    def __repr__(self):
        '''Returns string value of ConVar instance.'''
        return str(self.ConVar.GetString())

    def Set(self, cvarValue):
        '''Sets the value of the ConVar instance based on the input type.'''
        
        # Set value as int
        if type(cvarValue) == int:
            self.ConVar.SetInt(cvarValue)
        
        # Set value as float
        elif type(cvarValue) == float:
            self.ConVar.SetFloat(cvarValue)
        
        # Set value as bool
        elif type(cvarValue) == bool:
            self.ConVar.SetInt(int(cvarValue))
        
        # Set value as string
        else:
            self.ConVar.SetString(cvarValue)
        
    def MakePublic(self):
        '''Sets the notify flag for the cvar.'''
        self.ConVar.AddFlags(1<<8)
     

                
            
      
         
            
        