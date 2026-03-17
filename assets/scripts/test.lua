local script = {}

function script:OnUpdate(dt)
 
    local entity = self.self_entity
    entity.transform.rotation = entity.transform.rotation + 1
    entity.transform.position.x = entity.transform.position.x + 1

end


return script
