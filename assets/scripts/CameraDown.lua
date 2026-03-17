local script = {}

function script:OnUpdate(entity, dt)
    entity.transform.rotation = entity.transform.rotation - 1
end


return script
