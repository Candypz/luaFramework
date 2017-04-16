local eventModule = {}

function eventModule:new(o)  
    o = o or {}  
    setmetatable(o,self)  
    self.__index = self  
    return o  
end

function eventModule:initData()
    self.eventList = {}
end

function eventModule:getInstance()  
    if self.instance == nil then  
        self.instance = self:new()
        self:initData()  
    end  
    return self.instance  
end    

function eventModule:registered(obj)
    if obj and obj:listenerMsg() then
        for k,v in pairs(obj:listenerMsg()) do
            if not self.eventList[v] then self.eventList[v] = {} end
            if self:theRepeat(self.eventList[v], obj) then --保证唯一性
                table.insert(self.eventList[v], obj)
            end
        end
    end
end

function eventModule:theRepeat(list, obj)
    for k,v in pairs(list) do
        if v == obj then
            return false
        end
    end
    return true
end

function eventModule:remove(obj)
    if obj then
        for k,v in pairs(self.eventList) do
            for j,p in pairs(v) do
                if p == obj then
                    table.remove(v, j)
                end
            end
        end
    end
end

function eventModule:distributed(eventNaem, data)
    local _tab = self.eventList[eventNaem]
    if _tab then
        for k,v in pairs(_tab) do
            if v then
                v:receiveMsg(eventNaem, data)
            end
        end
    end
end

return eventModule