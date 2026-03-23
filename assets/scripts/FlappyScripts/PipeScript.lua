local script = {}


function script:OnCreate(entity, dt)
    entity.transform.position.y = math.random(-125, 125)
    self.speed = 100
end

function script:OnUpdate(entity, dt)
    entity.transform.position.x = entity.transform.position.x - self.speed * dt;    

    if entity.transform.position.x <= -500 then
        entity.transform.position.x = 500;
        entity.transform.position.y = math.random(-125, 125)
    end

end


return script
