
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
    -- add background image
    display.newSprite("HelloWorld.png")
        :move(display.center)
        :addTo(self)

    -- add HelloWorld label
    -- cc.Label:createWithSystemFont("Hello World", "Arial", 40)
    --     :move(display.cx, display.cy + 200)
    --     :addTo(self)

    self:Distributed("eddddd", "ddddddd")
end

function MainScene:listenerMsg()
    return {
        "eddddd",
        "ddddd",
        "eddddd",
    }
end

function MainScene:receiveMsg(eventNaem, data)
    if eventNaem == "eddddd" then
        print(data)
    end
end

return MainScene
