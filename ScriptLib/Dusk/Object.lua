require "Dusk/Class"

if not Dusk then Dusk = { } end

local Object = Dusk.Class(function(self, ptr)
    self.dusk_ptr = ptr
end)

Dusk.Object = Object
