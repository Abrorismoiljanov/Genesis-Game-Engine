local script = {}


function script:OnCreate(entity, dt)
end

function script:OnUpdate(entity, dt)

    local speed = 100.0;

    if Input.IsKeyDown(KEY_W) then
        Log("W key down!")
        entity.transform.position.y = entity.transform.position.y + speed * dt
    end
    if Input.IsKeyDown(KEY_S) then
        Log("S key down!")
        entity.transform.position.y = entity.transform.position.y - speed * dt
    end
    if Input.IsKeyDown(KEY_A) then
        Log("A key down!")
        entity.transform.position.x = entity.transform.position.x - speed * dt
    end
    if Input.IsKeyDown(KEY_D) then
        Log("D key down!")
        entity.transform.position.x = entity.transform.position.x + speed * dt
    end
end


return script
