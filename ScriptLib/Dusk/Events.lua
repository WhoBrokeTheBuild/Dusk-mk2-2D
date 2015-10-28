require "Dusk/Object"

local EventDispatcher = Dusk.Class(Dusk.Object, function(self, ptr)
	Dusk.Object.init(self, ptr)
end)

function EventDispatcher:AddEventListener(eventId, callback)
	dusk_event_dispatcher_add_event_listener(self.dusk_ptr, eventId, callback)
end

function EventDispatcher:RemoveEventListener(eventId, callback)
	dusk_event_dispatcher_remove_event_listener(self.dusk_ptr, eventId, callback)
end

Dusk.EventDispatcher = EventDispatcher
