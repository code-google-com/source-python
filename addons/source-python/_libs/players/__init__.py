# ../_libs/players/__init__.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   OS
from os import path

#   configparser
from configparser import RawConfigParser

# Source.Python Imports
from Source import Engine
from Source import Entity
from Source import Player
from core import GAME_NAME


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the prop definitions file directory
prop_defs_dir = path.join(path.dirname(path.abspath(__file__)), '_definitions')

# Get the prop definitions file name complete with path
prop_defs_file = path.normpath(prop_defs_dir + '/%s.ini' % GAME_NAME)

# RawConfigParser
prop_ini = RawConfigParser()

# Read the Parser
prop_ini.read(prop_defs_file)


# =============================================================================
# >> CLASSES
# =============================================================================
class EasyPlayer(object):
    '''EasyPlayer class wrapper for providing easier access to players.'''
    
    def __init__(self, *args, **kwargs):
        '''
            Class constructor, takes the following keyword inputs:
                userid (str/int)
                    use: EasyPlayer(userid=123)
                index  (str/int)
                    use: EasyPlayer(index=123)
                player (Source.Player)
                    use: EasyPlayer(player=PlayerInstance)
                steamid (str)
                    use: EasyPlayer(steamid='STEAM_0:1:5244720')
                    
            A single argument may also be issued only in the form of a userid.
                EasyPlayer(123)              
        '''
        
        # Tuple of keywords accepted by the constructor
        allowed_keywords = ('userid', 'index', 'player', 'steamid')
        
        # Were both a keyword and argument provided?
        if args and kwargs:
            
            # Raise error
            raise SyntaxError('Expected either argument OR keyword ' +
                'argument, got both.')
        
        # Was more than 1 argument provided?
        if len(args) > 1:
            
            # Raise error
            raise SyntaxError('Expected 1 argument, got %d.' % len(args))
        
        # Was more than 1 keyword argument provided?
        if len(kwargs) > 1:
            
            # Raise error
            raise SyntaxError('Expected 1 keyword argument, instead ' +
                'got %d.' % len(kwargs))
        
        # Was an argument supplied instead of a keyword?
        if args:
            
            # Only userid is allowed as an argument
            keyword = 'userid'
            
            # The value of the userid is the same as the provided argument
            value = args[0]
        
        # Keyword was supplied intead of argument
        else:
            
            # Keyword and Value pulled from kwargs
            keyword, value = kwargs.popitem()
            
            # Is the provided keyword valid?
            if keyword not in allowed_keywords:
                
                # Raise error
                raise KeyError('"%s" is not a valid keyword.' % keyword)
        
        # Is the keyword equal to 'userid'?
        if keyword == 'userid':
            
            # Get the Player instance from a userid
            self.Player = Player.PlayerOfUserid(int(value))
        
        # Is the keyword equal to 'index'?
        elif keyword == 'index':
            
            # Get the Player instance from an index
            self.Player = Player.PlayerOfIndex(int(value))
        
        # Is the keyword equal to 'player'?
        elif keyword == 'player':
            
            # Use provided instance
            self.Player = value
        
        # Is the keyword 'steamid'?
        else:
            
            # Loop through the player list
            for player in Player.Players():
                
                # Does this steamid match the one provided?
                if player.GetNetworkIDString() == value:
                    
                    # Use this Player instance
                    self.Player = player
                    
                    # Break the loop
                    break
            
            # If the loop was not broken (no matches)
            else:
                
                # Raise error
                raise ValueError('"%s" is not a recognized steamid.')
            
        # Get the Entity 
        self.Entity = Player.EdictOfPlayer(self.Player)
        
    def __getattr__(self, name):
        '''
            Runs missing attributes (methods) against the Player/Entity 
			instances.
        '''
        
        # Is the attribute defined in the the ini file?
        if name in prop_ini.sections():
            
            # Entity property type
            prop_type = prop_ini.get(name, 'type')
            
            # Entity prop
            prop = prop_ini.get(name, 'prop')
            
            # Is the type equal to int?
            if prop_type == 'int':
                
                # Return a int
                return self.Entity.GetPropInt(prop)
                
            # Is the type equal to str?
            if prop_type == 'str':
                
                # Return a str
                return self.Entity.GetPropString(prop)
                
            # Is the type equal to float?
            if prop_type == 'float':
                
                # Return a float
                return self.Entity.GetPropFloat(prop)
                
            # Is the type equal to vector?
            if prop_type == 'vector':
                
                # Return a prop
                return self.Entity.GetPropVector(prop)                
            
            # Is the type equal to VectorXY?
            if prop_type == 'vectorxy':
                
                # Return a vectorXY
                return self.Entity.GetPropVectorXY(prop)           
            
            # Is the type equal to long?
            if prop_type == 'long':
                
                # Return a long
                return self.Entity.GetPropLong(prop)
                           
            # Raise an error if the type is not defined or invalid
            raise TypeError('Invalid prop type "%s"' % section_type)

        # Does the Player instance have this attribute?
        if hasattr(self.Player, name):
            
            # Return from Player
            return getattr(self.Player, name)
            
        # Does the Edict instance have this attribute?
        if hasattr(self.Entity, name):
            
            # Return from Entity
            return getattr(self.Entity, name)
            
        # Raise an error because neither Player or Edict has this attribute
        raise AttributeError
               
    def __setattr__(self, name, value):
        '''Sets a dictionary value or an entity prop value'''
            
        # Is the value a entity property?
        if name in prop_ini.sections():
            
            # Get the prop type
            prop_type = prop_ini.get(name, 'type')
            
            # Get the prop
            prop = prop_ini.get(name, 'prop') 
            
            # Is the type equal to int?
            if prop_type == 'int':
                
                # Set the int
                self.Entity.SetPropInt(prop, int(value))
                
            # Is the type equal to str?
            elif prop_type == 'str':
                
                # Set the str
                self.Entity.SetPropString(prop, str(value))
                
            # Is the type equal to float?
            elif prop_type == 'float':
                
                # Set the float
                self.Entity.SetPropFloat(prop, float(value))
                
            # Is the type equal to vector?
            elif prop_type == 'vector':
                
                # Set the prop
                self.Entity.SetPropVector(prop, value)                
            
            # Is the type equal to VectorXY?
            elif prop_type == 'vectorxy':
                
                # Set the vectorXY
                self.Entity.SetPropVectorXY(prop, value)            
            
            # Is the type equal to long?
            elif prop_type == 'long':
                
                # Set the long
                self.Entity.SetPropLong(prop, long(value))
                           
            # Invalid type specified in file
            else:
                
                # Raise error
                raise TypeError('Invalid defined type "%s"' % section_type)
                
        # Set the attribute using the default method
        else:
        
            # Set the attribute
            object.__setattr__(self, name, value)
            
    @property
    def name(self):
        '''Returns the player's name'''
        return self.Player.GetName()
        
    @property
    def userid(self):
        '''Returns the player's UserID'''
        return self.Player.GetUserID()
        
    @property
    def index(self):
        '''Returns the index for the player'''
        return Engine.IndexOfEdict(self.Player)

    @property
    def steamid(self):
        '''Returns the player's SteamID'''
        return self.Player.GetNetworkIDString()
    
    @property
    def connected(self):
        '''Returns if this player slot is actually valid'''
        return self.Player.IsConnected()
        
    @property
    def in_vehicle(self):
        '''Returns true if the player is in a vehicle'''
        return self.Player.IsInAVehicle()
        
    @property
    def last_input(self):
        '''Returns the last user input from this player'''
        return self.Player.GetLastUserCommand()
        

# =============================================================================
# >> FUNCTIONS
# =============================================================================
def DumpDefinitions():
	'''
		Dumps all property definitions from the appropriate ini file into
		console.
	'''
	
	# Dictionary from config
	dic_dump = prop_ini._sections
	
	# Print header
	print('')	
	print('#'*42)
	print('# DUMPING PROPERTY DEFINITIONS FOR %s' % GAME_NAME.upper())
	print('#'*42)
	print('#')
	
	# Loop through the sections
	for section in dic_dump:
	
		# Print the section name
		print('# > %s' % section)
		
		# Loop through the items in the section
		for item in dic_dump[section]:
		
			# Print the item name and value
			print('# >>> %s: %s' % (item, dic_dump[section][item]))

	# Print the footer
	print('#')
	print(' END '.center(42, '#'))
	print('')
        
                                      