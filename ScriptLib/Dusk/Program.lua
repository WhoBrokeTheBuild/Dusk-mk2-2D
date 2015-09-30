require "Dusk/Events"

if not Dusk then Dusk = { } end

Dusk.GetProgram = function()
	return Dusk.Program( dusk_get_program() )
end

local Program = Dusk.Class(Dusk.IEventDispatcher, function(self, ptr)
	Dusk.IEventDispatcher.init(self, ptr)
end)

function Program:Exit()
	dusk_program_exit(self.dusk_ptr);
end

Program.EvtUpdate = 1;
Program.EvtRender = 2;
Program.EvtExit   = 3;

Dusk.Program = Program
