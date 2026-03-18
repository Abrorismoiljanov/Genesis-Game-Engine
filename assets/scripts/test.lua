local script = {}

local speed = 200.0

function script:OnUpdate(entity, dt)
    if Input.IsKeyDown(KEY_W) then
        entity.transform.position.y = entity.transform.position.y + speed * dt
    end
    if Input.IsKeyDown(KEY_S) then
        entity.transform.position.y = entity.transform.position.y - speed * dt
    end
    if Input.IsKeyDown(KEY_D) then
        if entity.transform.scale.x < 0 then
            entity.transform.scale.x = -entity.transform.scale.x
        end
        entity.transform.position.x = entity.transform.position.x + speed * dt
    end
    if Input.IsKeyDown(KEY_A) then
        if entity.transform.scale.x > 0 then
            entity.transform.scale.x = -entity.transform.scale.x
        end
        
        entity.transform.position.x = entity.transform.position.x - speed * dt
    end
    if Input.IsKeyPressed(KEY_SPACE) then
        entity.transform.rotation = entity.transform.rotation + 180
    end
end


return script
