local HotUpdate = class("HotUpdate", cc.load("mvc").ViewBase)

function HotUpdate:onCreate()
    self:initAssetsManager()
end

function HotUpdate:initAssetsManager()
    local _am = cc.AssetsManagerEx:create("version/project.manifest", cc.FileUtils:getInstance():getWritablePath().."update")
    _am:retain()

    if not _am:getLocalManifest():isLoaded() then
        print("Fail to update assets, step skipped.")
    else
        local function onUpdateEvent(event)
            local eventCode = event:getEventCode()
            if eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_NO_LOCAL_MANIFEST then
                
            elseif  eventCode == cc.EventAssetsManagerEx.EventCode.UPDATE_PROGRESSION then

            elseif eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_DOWNLOAD_MANIFEST or eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_PARSE_MANIFEST then

            elseif eventCode == cc.EventAssetsManagerEx.EventCode.ALREADY_UP_TO_DATE or eventCode == cc.EventAssetsManagerEx.EventCode.UPDATE_FINISHED then
                self:getApp():enterScene("MainScene")
            elseif eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_UPDATING then

            end
        end

        local _listener = cc.EventListenerAssetsManagerEx:create(_am,onUpdateEvent)
        cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(_listener, 1)
        _am:update()
    end
end

return HotUpdate