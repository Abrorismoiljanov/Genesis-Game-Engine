local script = {}

function script:OnCreate(entity, dt)
end

function script:OnUpdate(entity, dt)
    entity.transform.position.x = entity.transform.position.x - 150 * dt;
    if entity.transform.position.x <= -500 then
        entity.transform.position.x = 500;
    end
end


return script
