if not Dusk then Dusk = { } end

function Class(base, init, term)
	local c = { }

	if type(base) == 'function' then
		term = init
		init = base
		base = nil
	elseif type(base) == 'table' then
		for i, v in pairs(base) do
			c[i] = v;
		end
		c._base = base;
	end

	c.__index = c

	local mt = { }
	mt.__call = function(class_tbl, ...)
		local obj = { }
		setmetatable(obj, c)
		if init then
			init(obj, ...)
		else
			if base and base.init then
				base.init(obj, ...)
			end
		end
		return obj
	end
	mt.__gc = function(self)
		if term then
			term(self)
		else
			if base and base.term then
				base.term(self)
			end
		end
	end

	c.init = init
	c.term = term
	c.is_a = function(self, class_type)
		local m = getmetatable(self)
		while m do
			if m == class_type then
				return true
			end
			m = m._base
		end
		return false
	end

	setmetatable(c, mt)
	return c
end

Dusk.Class = Class
