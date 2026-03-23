local script = {}


function script:OnCreate(entity, dt)
    Log("Player was born")
end

function script:OnUpdate(entity, dt)
     
    speed = 100.0;
    col = GetComponent(entity, "Collision");

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

function script:OnTriggerEnter(entity, other)
    if other.name == "Portal to Test" then
        if Input.IsKeyPressed(KEY_E) then 
        entity.transform.position.x = other.transform.position.x + 17 
            ChangeScene("Test")
        end
    end
    if other.name == "Portal to Main" then
        if Input.IsKeyPressed(KEY_E) then
            ChangeScene("Main")
            entity.transform.position.x = other.transform.position.x + 17 
        end
    end
end

return script
