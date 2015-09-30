require "Dusk/Object"

local IEventDispatcher = Dusk.Class(Dusk.Object, function(self, ptr)
	Dusk.Object.init(self, ptr)
end)

function IEventDispatcher:AddEventListener(eventId, callback)
	dusk_ievent_dispatcher_add_event_listener(self.dusk_ptr, eventId, callback)
end

function IEventDispatcher:RemoveEventListener(eventId, callback)
	dusk_ievent_dispatcher_remove_event_listener(self.dusk_ptr, eventId, callback)
end

Dusk.IEventDispatcher = IEventDispatcher
