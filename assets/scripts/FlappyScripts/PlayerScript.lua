local script = {}


function script:OnCreate(entity, dt)
    script.velocity = 0
    script.alive = true
    script.deathTimer = 1.5
end

function script:OnUpdate(entity, dt)
    local gravity = -300
    local flap = 200
  
    if script.alive then
  
        if Input.IsKeyPressed(KEY_SPACE) then
            self.velocity = flap
            self.alive = true
        end


        script.velocity = script.velocity + gravity * dt
        entity.transform.position.y = entity.transform.position.y + script.velocity * dt;
        if self.velocity > 0 then
            entity.transform.rotation = 20;
        end
        if self.velocity == 0 then
            entity.transform.rotation = 0;
        end
        if self.velocity < 0 then
            entity.transform.rotation = -20;
        end
    else
        
        script.deathTimer = script.deathTimer - dt
        if script.deathTimer < 0 then
            ResetGame()
        end
    end
end

function script:OnTriggerEnter(target, other)
    script.alive = false
end

return script
