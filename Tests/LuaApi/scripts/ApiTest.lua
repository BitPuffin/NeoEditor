
dofile("luaunit.lua") 

strout = ""

-- Not perfect but good enough
function compare_float(float1, float2)
    return math.abs((float1-float2)/float2) < 0.00001
end

function compare_vec(vec1, vec2)
    local vec2choose = vec1
    local othervec = vec2
    if #vec1 > #vec2 then
        vec2choose = vec2
        othervec = vec1
    end
    
    for i = 1, #vec2choose, 1 do
        assertEquals(compare_float(vec2choose[i], othervec[i]), true)
    end
end

function testMeshLoading()
    local object = loadMesh("meshs/box.mesh")
    assertEquals(getName(object), "Entity0")
    assertEquals(loadMesh("DoesNotExist"), nil)   

    translate(object, {500,500,500}) -- Move the box out of the way 
end

function testLight()
    local object = createLight()
    assertEquals(getName(object), "Light0")
    
    setLightColor(object, {0.5,0.5,0.5})
    setLightRadius(object, 500)
    setLightIntensity(object, 0.7)
    setLightShadowQuality(object, 1024)
    setLightShadowBias(object, 2)
    setLightShadowBlur(object, 7)
    setLightSpotAngle(object, 30)
    setLightSpotExponent(object, 0.7)
    
    compare_vec(getLightColor(object), {0.5,0.5,0.5})
    assertEquals(getLightRadius(object), 500)
    assertEquals(compare_float(getLightIntensity(object), 0.7), true)
    assertEquals(getLightShadowQuality(object), 1024)
    assertEquals(getLightShadowBias(object), 2)
    assertEquals(getLightShadowBlur(object), 7)
    assertEquals(getLightSpotAngle(object), 30)
    assertEquals(compare_float(getLightSpotExponent(object), 0.7), true)
end

function testVec()
    local vector = vec3(15.3,18.5,19)
    compare_vec(vector, {15.3,18.5,19})

    vector = vec3(3,3,1) + vec3(5,5,9)
    compare_vec(vector, {8,8,10})
    
    vector = vec3(3,3,1) * vec3(5,5,9)
    compare_vec(vector, {15,15,9})
    
    vector = vec3(20,15,5) / vec3(5,5,5)
    compare_vec(vector, {4,3,1})
    
    assertEquals(compare_float(length({2,2,2}), 3.464101615), true)
    
    vector = normalize({15,17,20})
    assertEquals(length(vector), 1)
    
    assertEquals(compare_float(dot({2,5,1}, {7,3,4}), 33), true)
end

print = function(str) 
		if str == nil then 
			return 
		end 
		
		strout = strout .. str .. "\n"
	end

LuaUnit.run()

function button1Callback()
	local obj = getObject("Cube")
	rotate(obj, {1,0,0}, 15, "local")
end

function button2Callback()
	local light = getObject("Light")
	setLightIntensity(light, getLightIntensity(light) + 0.1)
end

function button3Callback()
	local light = getObject("Light")
	setLightIntensity(light, getLightIntensity(light) - 0.1)
	--clearGui(123)
end

function button4Callback()
	setLabel(label1, getLabel(input1))
end

enableGui(1)
mainCanvas = getMainCanvas()

setNormalBackground({0.5,0.5,0.5,0.3})
setHoverBackground({0.7,0.7,0.7,0.3})

button1 = createButton(15,15,250,30,"Rotate Cube", "button1Callback")
button2 = createButton(15,50,250,30,"More light", "button2Callback")
button3 = createButton(15,85,250,30, "Less light", "button3Callback")

label1 = createLabel(150, 15, 250, 30, "Test results:\n\n" .. strout)

input1 = createInput(15,130,250, 30, "This is an input", "")
--button4 = createButton(15,170,250,30, "Set label to text", "button4Callback")

resolution = getWindowScale()
ball = createSprite(resolution[1]/2, resolution[2]/2, 15, 15, "maps/neo-icon.png", "")
ballpos = getWidgetPosition(ball)
ballspeed = {2,-1}

paddlewidth = 25
paddleheight = 100

paddles =
{
{createSprite(15, 500, paddlewidth, paddleheight, "maps/paddle.png", ""), position = {resolution[1] - 32, resolution[2]/2}},
{createSprite(15, 500, paddlewidth, paddleheight, "maps/paddle.png", ""), position = {15, resolution[2]/2}} 
}

function updatePaddles()
	for i = 1, #paddles, 1 do
		setWidgetPosition(paddles[i][1], paddles[i].position)
	end
end

for i = 1, #paddles, 1 do
	addWidgetToCanvas(mainCanvas, paddles[i][1])
end

addWidgetToCanvas(mainCanvas, label1)
addWidgetToCanvas(mainCanvas, button1)
addWidgetToCanvas(mainCanvas, button2)
addWidgetToCanvas(mainCanvas, button3)
addWidgetToCanvas(mainCanvas, input1)

addWidgetToCanvas(mainCanvas, ball)

function onSceneUpdate()
	if isKeyPressed("S") and paddles[2].position[2] + paddleheight <= resolution[2] then
		paddles[2].position[2] = paddles[2].position[2] + 5
	end

	if isKeyPressed("W") and paddles[2].position[2] > 5 then
		paddles[2].position[2] = paddles[2].position[2] - 5
	end

	if isKeyPressed("UP") and paddles[1].position[2] > 5 then
		paddles[1].position[2] = paddles[1].position[2] - 5
	end

	if isKeyPressed("DOWN") and paddles[1].position[2] + paddleheight <= resolution[2] then
		paddles[1].position[2] = paddles[1].position[2] + 5
	end

	if ballpos[2] >= resolution[2] or ballpos[2] <= 0 then
		ballspeed[2] = -1*ballspeed[2]
	end

	for i = 1, #paddles, 1 do
		if ballpos[1] >= paddles[i].position[1] and ballpos[1] <= paddles[i].position[1] + paddlewidth 
			and ballpos[2] >= paddles[i].position[2] and ballpos[2] <= paddles[i].position[2] + paddleheight 
			then

			ballspeed[1] = -1*ballspeed[1]
		end
	end

	ballpos[1] = ballpos[1] + ballspeed[1]
	ballpos[2] = ballpos[2] + ballspeed[2]

	updatePaddles()	
	setWidgetPosition(ball, ballpos)
end

--quit()
