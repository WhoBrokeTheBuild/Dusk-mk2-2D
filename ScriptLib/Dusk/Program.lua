require "Dusk/Events"

local Program = Dusk.Class(Dusk.EventDispatcher, function(self, ptr)
	Dusk.EventDispatcher.init(self, ptr)
end)

function Program:Exit()
	dusk_program_exit(self.dusk_ptr);
end

Program.EvtUpdate = 1
Program.EvtRender = 2
Program.EvtExit   = 3

Dusk.Program = Program

dusk_program = Dusk.Program( dusk_get_program() )
Dusk.GetProgram = function()
	return dusk_program
end
