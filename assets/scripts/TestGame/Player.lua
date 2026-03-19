local script = {}


function script:OnCreate(entity, dt)
end

function script:OnUpdate(entity, dt)

    local speed = 100.0;

    if Input.IsKeyDown(KEY_W) then
        entity.transform.position.y = entity.transform.position.y + speed * dt
    end
    if Input.IsKeyDown(KEY_S) then
        entity.transform.position.y = entity.transform.position.y - speed * dt
    end
    if Input.IsKeyDown(KEY_A) then
        entity.transform.position.x = entity.transform.position.x - speed * dt
    end
    if Input.IsKeyDown(KEY_D) then
        entity.transform.position.x = entity.transform.position.x + speed * dt
    end
end


return script
