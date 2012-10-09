# ../_libs/entities/entity.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Engine
#   Entities
from entities.properties import Properties


# =============================================================================
# >> CLASSES
# =============================================================================
class BaseEntity(dict):
    '''Class used to interact directly with entities'''

    def __new__(cls, index):
        '''Override the __new__ class method to verify the given index
            is of the correct entity type and add the index attribute'''

        # Get the given indexes edict
        edict = Engine.PEntityOfEntIndex(index)

        # Is the edict valid?
        if edict is None:

            # If not raise an error
            raise ValueError('Index "%s" is not a proper index' % index)

        # Verify that the given index is of the correct entity type
        if not cls._is_valid_index_for_entity_type(edict):

            # If not an index of the correct entity type, raise an error
            raise ValueError('Index "%s" is not appropriate type' % index)

        # Create the object
        self = dict.__new__(cls)

        # Add the base attributes as items in the dictionary
        self['index'] = index
        self['edict'] = edict
        self['_inis'] = list()

        # Return the instance
        return self

    def __init__(self, index):
        '''Override the __init__ method to add "entity" to the _inis list'''

        # Add "entity" to the entities list
        self._inis.append('entity')

    def __getattr__(self, attr):
        '''Finds if the attribute is valid and gets the appropriate value'''

        # Return the attribute's value, if it is found
        return self.get_value(attr)

    def get_value(self, item):
        '''Finds if the item is valid for the instance and returns its value'''

        # Is the item a member of the dictionary?
        if item in self:

            # Return the item
            return self[item]

        # Loop through all instances (used to get edict/IPlayerInfo attributes)
        for instance in self.instances:

            # Does the current instance contain the given attribute?
            if hasattr(instance, item):

                # Return the instance's value for the given attribute
                return getattr(instance, item)

        # Is the item a property of this entity?
        if item in self.properties:

            # Return the property's value
            return self.get_property(item)

        # If the item is not found, raise an error
        raise LookupError('Item "%s" not found' % item)

    def get_property(self, item):
        '''Gets the value of the given property'''

        # Get the property's prop
        prop = self.properties[item].prop

        # Get the property's type
        prop_type = self.properties[item].type

        # Is the property's type "int"?
        if prop_type == 'int':

            # Is the property a True/False property?
            if 'True' in self.properties[item]:

                # Return if the current value equals the "True" value
                return (
                    self.edict.GetPropInt(prop)
                    == self.properties[item]['True'])

            # Return the integer value of the property
            return self.edict.GetPropInt(prop)

        # Is the property's type "string"?
        if prop_type == 'string':

            # Return the string value of the propery
            return self.edict.GetPropString(prop)

        # Is the property's type "float"?
        if prop_type == 'float':

            # Return the float value of the property
            return self.edict.GetPropFloat(prop)

        # Is the property's type "vector"?
        if prop_type == 'vector':

            # Return the Vector instance of the property
            return self.edict.GetPropVector(prop)

        # Is the property's type "vectorxy"?
        if prop_type == 'vectorxy':

            # Return the VectorXY instance of the property
            return self.edict.GetPropVectorXY(prop)

        # Is the property's type "long"?
        if prop_type == 'long':

            # Return the long value of the property
            return self.edict.GetPropLong(prop)

        # If not a proper type, raise an error
        raise TypeError('Invalid property type "%s"' % prop_type)

    def __setattr__(self, attr, value):
        '''Finds if the attribute is value and sets its value'''

        # Set the attribute's value, if it is found
        self.set_value(attr, value)

    def set_value(self, item, values):
        '''Finds if the item is valid and sets its value'''

        # Loop through all instances
        # (used to set using edict/IPlayerInfo attributes)
        for instance in self.instances:

            # Does the current instance contain the given attribute?
            if hasattr(instance, item):

                # Get the attribute's instance and use it to set the value
                setattr(instance, item, values)

                # No need to go further
                return

        # Is the item a property of this entity?
        if item in self.properties:

            # Set the property's value
            self.set_property(item, values)

    def set_property(self, item, value):
        '''Sets the value of the given propery'''

        # Get the property's prop
        prop = self.properties[item].prop

        # Get the property's type
        prop_type = self.properties[item].type

        # Is the property's type "int"?
        if prop_type == 'int':

            # Is the property a True/False property?
            if 'True' in self.properties[item]:

                # Get the current value
                current = self.edict.GetPropInt(prop)

                # Does the current value equal the given value?
                if current == value:

                    # No need to set the value
                    return

                # Get the exact value to set the property to
                value = self.properties[item][str(bool(value))]

            # Set the property's integer value
            self.edict.SetPropInt(prop, value)

        # Is the property's type "string"?
        elif prop_type == 'string':

            # Set the property's string value
            self.edict.SetPropString(prop, value)

        # Is the property's type "float"?
        elif prop_type == 'float':

            # Set the property's float value
            self.edict.SetPropFloat(prop, value)

        # Is the property's type "vector"?
        elif prop_type == 'vector':

            # Set the property's Vector value
            self.edict.SetPropVector(prop, value)

        # Is the property's type "vectorxy"?
        elif prop_type == 'vectorxy':

            # Set the property's VectorXY value
            self.edict.SetPropVectorXY(prop, value)

        # Is the property's type "long"?
        elif prop_type == 'long':

            # Set the property's long value
            self.edict.SetPropLong(prop, value)

        # Is the item an improper type?
        else:

            # Raise an error
            raise TypeError('Invalid property type "%s"' % prop_type)

    def get_color(self):
        '''Returns a 4 part tuple (RGBA) for the entity's color'''

        # Get the render value
        value = self.render

        # Return a tuple with the RGBA values
        return (
            value & 0xff, (value & 0xff00) >> 8,
            (value & 0xff0000) >> 16, (value & 0xff000000) >> 24)

    def set_color(self, args):
        '''Sets the entity's color to the given RGBA values'''

        # Are the the correct number of arguments?
        if not len(args) in (3, 4):

            # Raise an error
            raise TypeError(
                'set_color() requires 3 or 4 ' +
                'arguments, %s were given' % len(args))

        # Get the RGB values
        red, green, blue = args[:3]

        # Get the value using the RGB values
        value = red + (green << 8) + (blue << 16)

        # Was an alpha value passed?
        if len(args) == 3:

            # Get the current alpha value
            alpha = (self.render & 0xff000000)

        # Otherwise
        else:

            # Get the 4th value passed
            alpha = args[3]

        # Add the alpha value to the RGB value
        value += alpha << 24

        # Set the rendermode
        self.rendermode = self.rendermode | 1

        # Set the renderfx
        self.renderfx = self.renderfx | 256

        # Set the entity's color
        self.render = value

    # Set the "color" property for BaseEntity
    color = property(get_color, set_color)

    @property
    def instances(self):
        '''Yields the entity's edict instance'''

        # Yield the edict instance
        yield self.edict

    @property
    def handle(self):
        '''Returns the entity's handle instance'''
        return self.edict.GetNetworkable().GetEntityHandle().GetRefEHandle()

    @property
    def classname(self):
        '''Returns the classname of the entity'''
        return self.edict.GetClassName()

    @property
    def properties(self):
        '''Returns all properties for all entities'''
        return Properties.get_entity_properties(self._inis)

    @classmethod
    def _is_valid_index_for_entity_type(cls, edict):
        '''Verifies that the given edict is of an entity'''

        # Return whether the given edict has a classname
        return edict.GetClassName()

    @classmethod
    def get_instance_from_edict(cls, edict):
        '''Returns a class instance for the given edict'''

        # Get the index of the given edict
        index = Engine.IndexOfEdict(edict)

        # Return an instance for the index
        return cls(index)
