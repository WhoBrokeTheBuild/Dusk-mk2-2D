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

Program.EVT_UPDATE	= 1;
Program.EVT_RENDER	= 2;
Program.EVT_EXIT	= 3;

Dusk.Program = Program
