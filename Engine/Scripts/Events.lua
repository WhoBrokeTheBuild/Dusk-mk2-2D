if not Dusk then Dusk = { } end
if not Dusk.Events then Dusk.Events = { } end

local IEventDispatcher = DuskClass(DuskObject, function(self, ptr)
	DuskObject.init(self, ptr)
end)

function IEventDispatcher:AddEventListener(eventId, callback)
	dusk_ievent_dispatcher_add_event_listener(self.dusk_ptr, eventId, callback)
end

function IEventDispatcher:RemoveEventListener()
	dusk_ievent_dispatcher_remove_event_listener(self.dusk_ptr, eventId, callback)
end

Dusk.Events.IEventDispatcher = IEventDispatcher
