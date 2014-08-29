 
setPluginName("DefaultInputAZERTY")
setPluginAuthor("Yannick Pflanzer")
setPluginLicense("")
setPluginDescription("Default input method using QZSD for french keyboards")
enableInputMethod("update_input")

function update_input()
    camera = getPerspectiveVue()
    translationSpeed = getTranslationSpeed()

    if isKeyPressed("Z") then
        translate(camera, {0,0,-1.0*translationSpeed}, "local")
        updateMatrix(camera)
    elseif isKeyPressed("S") then
        translate(camera, {0,0,1.0*translationSpeed}, "local")
        updateMatrix(camera)
    end
    
    if isKeyPressed("Q") then
        translate(camera, {-1.0*translationSpeed,0,0}, "local")
        updateMatrix(camera)
    elseif isKeyPressed("D") then
        translate(camera, {1.0*translationSpeed,0,0}, "local")
        updateMatrix(camera)
    end
    
    if isKeyPressed("E") then
        translate(camera, {0,1.0*translationSpeed,0}, "local")
        updateMatrix(camera)
    elseif isKeyPressed("C") then
        translate(camera, {0,-1.0*translationSpeed,0}, "local")
        updateMatrix(camera)
    end
end